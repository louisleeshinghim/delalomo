// For burning bootloader to ATMEGA64/128, an Arduino UNO can be used as ISP with these wiring
// UNO Pin D10 >>> ATMEGA64/128 Reset
// UNO Pin D11 >>> ATMEGA64/128 RX = PE0
// UNO Pin D12 >>> ATMEGA64/128 TX = PE1
// UNO Pin D13 >>> ATMEGA64/128 SCK = PB1

//////////////////////////////////////////////////////////////////////
// Include libraries                                                // 1064 bytes for this part
//////////////////////////////////////////////////////////////////////

#include <Arduino.h>                                                // Arduino library
#include <Streaming.h>                                              // Concatenation
#include <Wire.h>                                                   // I2C bus

//////////////////////////////////////////////////////////////////////
// Set up real-time clock                                           // This part is for real-time clock
//////////////////////////////////////////////////////////////////////

#include <DS3232RTC.h>                                              // Include RTC library
#define WAKE 20                                                     // Interrupt pin on INT2 for SQW wake-up
DS3232RTC ds3231;                                                   // Set up RTC object ds3231

tmElements_t firstlog_time;                                         // Define time structure

int alarmRing = 0;                                                  // Alarm flag is off at first
time_t tNow;                                                        // UNIX time now
time_t tAlarm;                                                      // UNIX time alarm
time_t tDelay;                                                      // UNIX time first delay
time_t tEnd;                                                        // UNIX time last logging 

time_t tInterval = 5;                                               // Logging interval in seconds
long logfreq;                                                       // Logging interval from SD card

long firstlog_a; long firstlog_b; long firstlog_c;                  // First log date
long firstlog_d; long firstlog_e; long firstlog_f;                  // First log time

//////////////////////////////////////////////////////////////////////
// Set up SD reader                                                 // This part is for SD reader
//////////////////////////////////////////////////////////////////////

#include <SPI.h>                                                    // Enable SPI bus
#include "SdFat.h"                                                  // Enable SD reader 

#define CS   8                                                      // Define CS pin
#define SCK  9                                                      // Define SCK pin
#define MOSI 10                                                     // Define MOSI pin
#define MISO 11                                                     // Define MISO pin
#define SD_FAT_TYPE 3                                               // SD card type 3 is a safe choice
#define SPI_CLOCK SD_SCK_MHZ(50)                                    // Set SPI clock speed to 50
#define SD_CONFIG SdSpiConfig(CS, DEDICATED_SPI, SPI_CLOCK)         // Use CS pin, dedicated SPI mode and clock rate

SdFs sd;                                                            // Name the SD card
FsFile delaylog;                                                    // txt.file for delay time containing a UNIX timestamp
FsFile sampfreq;                                                    // txt.file for sampling frequency
FsFile datafile;                                                    // txt.file for recording data

char line [16];                                                     // Characters read from SD card
char firstlog [16];                                                 // Characters of first logging from SD card
char end [16];                                                      // Characters of last logging from SD card
char *pEnd;                                                         // End of the characters from SD card 

//////////////////////////////////////////////////////////////////////
// Define pins                                                      // This part is for the pins
//////////////////////////////////////////////////////////////////////

#define RG1  21                                                     // Interrupt pin on INT3 for rain gauge 1
#define RG2  4                                                      // Interrupt pin on INT4 for rain gauge 2
#define RG3  5                                                      // Interrupt pin on INT5 for rain gauge 3
#define SCL  18                                                     // SCL pin
#define SDA  19                                                     // SDA pin
#define PSW 14                                                      // Power switch MOSFET pin 
#define LED 42                                                      // LED indicator pin

//////////////////////////////////////////////////////////////////////
// Set up i2C devices                                               // This part is for i2C devices
//////////////////////////////////////////////////////////////////////

#include <SensirionI2cSht4x.h>                                      // enable Sensirion SHT40
#include <BMx280I2C.h>                                              // enable BMP280
#include <ArtronShop_SPL06-001.h>                                   // enable SPL-06-001
#include <SparkFunMLX90614.h>                                       // enable MLX90614
#define TCAADDR 0x70                                                // Define TCA9548 at 0x70

SensirionI2cSht4x sht4x;                                            // SHT40
ArtronShop_SPL06_001 spl06(0x77, &Wire);                            // SPL06-001
BMx280I2C bmx280(0x76);                                             // BMP280
IRTherm mlx;                                                        // MLX90614

float temperature;                                                  // SHT40 temperature
float humidity;                                                     // SHT40 humidity
uint16_t error;                                                     // SHT40 error message




//////////////////////////////////////////////////////////////////////
// Set up analog multiplexer                                        // This part is for ADS1115
//////////////////////////////////////////////////////////////////////

#include <ADS1X15.h>                                                // ADS1115
ADS1115 ADS0(0x4B);                                                 // Define on-board ADS1115 at 0x4B as ADS0 
ADS1115 ADS1(0x48);                                                 // Define off-board ADS1115 at 0x48 as ADS1 
ADS1115 ADS2(0x49);                                                 // Define off-board ADS1115 at 0x49 as ADS2 
int16_t ads;                                                        // Voltage reading

//////////////////////////////////////////////////////////////////////
// Set up load cells                                                // This part is for load cells
//////////////////////////////////////////////////////////////////////

#define LCLK 35                                                     // Load cell clock pin
#define LOC1 37                                                     // Load cell 1 data pin
#define LOC2 39                                                     // Load cell 2 data pin
#define LOC3 41                                                     // Load cell 3 data pin

//////////////////////////////////////////////////////////////////////
// Set up rain gauges                                               // This part is for rain gauges
//////////////////////////////////////////////////////////////////////

#define RG1  21                                                     // Interrupt pin on INT3 for rain gauge 1
#define RG2  5                                                      // Interrupt pin on INT5 for rain gauge 2
#define RG3  4                                                      // Interrupt pin on INT4 for rain gauge 3

int Rain1 =  0;                                                     // Rain gauge 1 count
int Rain2 =  0;                                                     // Rain gauge 2 count
int Rain3 =  0;                                                     // Rain gauge 3 count

volatile bool RG1Tip = false;                                       // Rain gauge 1 tipping indicator 
volatile bool RG2Tip = false;                                       // Rain gauge 2 tipping indicator 
volatile bool RG3Tip = false;                                       // Rain gauge 3 tipping indicator 

unsigned long InterruptTime1;                                       // Rain gauge 1 interrupt time
unsigned long InterruptTime2;                                       // Rain gauge 2 interrupt time
unsigned long InterruptTime3;                                       // Rain gauge 3 interrupt time

unsigned long LastInterrupt1;                                       // Rain gauge 1 last interrupt time 
unsigned long LastInterrupt2;                                       // Rain gauge 2 last interrupt time
unsigned long LastInterrupt3;                                       // Rain gauge 3 last interrupt time

static unsigned long Debounce = 225;                                // Debounce threshold 





























//////////////////////////////////////////////////////////////////////
// Setup loop                                                       //
//////////////////////////////////////////////////////////////////////

void setup() {

//////////////////////////////////////////////////////////////////////
// Begin the peripherals                                            //
//////////////////////////////////////////////////////////////////////
powerOn(); 

Serial.begin(9600);                                                                               // Call serial monitor 
SPI.begin();                                                                                      // Begin SPI
Wire.begin(); delay(10);                                                                          // Begin i2C
ds3231.begin();                                                                                   // Begin RTC
sd.begin(SD_CONFIG);                                                                                 // Begin SD Card


////////////////////////////////////////////////////////////////////////////////////////////////////
// Read interval from SD card                                                                     //
////////////////////////////////////////////////////////////////////////////////////////////////////

sampfreq = sd.open("sampfreq.txt", FILE_READ);

sampfreq.seek(0*4); long logfreq = sampfreq.parseInt();                                           // Read month
tInterval = logfreq;                                                                              // Logging interval in seconds

sampfreq.close();

////////////////////////////////////////////////////////////////////////////////////////////////////
// Read delay from SD card                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////

delaylog = sd.open("humanlog.txt", FILE_READ); 

delaylog.seek(0*8); long firstlog_a = delaylog.parseInt() - 1970;                               // Read year
delaylog.seek(1*4); long firstlog_b = delaylog.parseInt();                                      // Read month
delaylog.seek(2*4); long firstlog_c = delaylog.parseInt();                                      // Read day
delaylog.seek(3*4); long firstlog_d = delaylog.parseInt();                                      // Read hour
delaylog.seek(4*4); long firstlog_e = delaylog.parseInt();                                      // Read minute
delaylog.seek(5*4); long firstlog_f = delaylog.parseInt();                                      // Read second

firstlog_time.Year = firstlog_a; 
firstlog_time.Month = firstlog_b;
firstlog_time.Day = firstlog_c;
firstlog_time.Hour = firstlog_d;
firstlog_time.Minute = firstlog_e;
firstlog_time.Second = firstlog_f;

tDelay = makeTime(firstlog_time);                                                               // Create UNIX delay timestamp

delaylog.close(); 

////////////////////////////////////////////////////////////////////////////////////////////////////
// Prepare for first logging                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////

ds3231.clearAlarm(DS3232RTC::ALARM_1);                                                            // Clear RTC Alarm 1 
ds3231.clearAlarm(DS3232RTC::ALARM_2);                                                            // Clear RTC Alarm 2 
ds3231.squareWave(DS3232RTC::SQWAVE_NONE);                                                        // Disable RTC SQW Interrupt

tNow = ds3231.get();                                                                              // Get current time

if(tDelay > (tNow + 5)) {
  tAlarm = tDelay;
  blinkLED(); blinkLED(); blinkLED(); blinkLED();
  }
else {
  tAlarm = tNow + tInterval;                                                                      // Set alarm time
  blinkLED();
  }

detachInterrupt(digitalPinToInterrupt(WAKE));                                                     // Detach SQW interrupt pin 
pinMode(WAKE, INPUT_PULLUP);                                                                      // Pull up SQW interrupt pin 
attachInterrupt(digitalPinToInterrupt(WAKE), alarmOn, FALLING);                                   // Set interrupt condition

ds3231.setAlarm(DS3232RTC::ALM1_MATCH_HOURS, second(tAlarm), minute(tAlarm), hour(tAlarm), 0);    // Set Alarm 1
ds3231.alarmInterrupt(DS3232RTC::ALARM_1, true);                                                  // Enable Alarm 1 interrupt
Wire.beginTransmission(0x68);                                                                     // Write DS3231 register
Wire.write(0x0E);                                                                                 // Access control register
Wire.write(0x5D);                                                                                 // Write 01011101 so BBSQW is 1
Wire.endTransmission();                                                                           // SQW on battery is enabled
delay(10);                                                                                        // Buffer after setting alarm

////////////////////////////////////////////////////////////////////////////////////////////////////
// Set up rain gauges                                                                             //
////////////////////////////////////////////////////////////////////////////////////////////////////

detachInterrupt(digitalPinToInterrupt(RG1));                                                      // Removes RG1 interrupt 
pinMode(RG1, INPUT_PULLUP);                                                                       // Pull up RG1 pin
attachInterrupt(digitalPinToInterrupt(RG1), RG1Flip, LOW);                                        // Attach RG1 interrupt

detachInterrupt(digitalPinToInterrupt(RG2));                                                      // Removes RG2 interrupt
pinMode(RG2, INPUT_PULLUP);                                                                       // Pull up RG2 pin
attachInterrupt(digitalPinToInterrupt(RG2), RG2Flip, LOW);                                        // Attach RG2 interrupt

detachInterrupt(digitalPinToInterrupt(RG3));                                                      // Removes RG3 interrupt
pinMode(RG3, INPUT_PULLUP);                                                                       // Pull up RG3 pin
attachInterrupt(digitalPinToInterrupt(RG3), RG3Flip, LOW);                                        // Attach RG3 interrupt

////////////////////////////////////////////////////////////////////////////////////////////////////
// Report successful setup                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////

Serial.print("Setup complete! ");                                                                 // Uncomment if not used
delay(25);                                                                                        // Buffer for serial printing

Serial.print("First logging: ");                                                                  // Uncomment if not used

Serial.print(year(tDelay)); Serial.print(":");                                                    // Print current time
Serial.print(month(tDelay)); Serial.print(":");                                                   // Print current time
Serial.print(day(tDelay)); Serial.print(":");                                                     // Print current time
Serial.print(hour(tDelay)); Serial.print(":");                                                    // Print current time
Serial.print(minute(tDelay)); Serial.print(":");                                                  // Print current time
Serial.print(second(tDelay)); Serial.print(": ");                                                 // Print current time
delay(25);                                                                                        // Buffer for serial printing

Serial.print("Interval: ");                                                                       // Uncomment if not used
Serial.println(tInterval);
delay(25);                                                                                        // Buffer for serial printing

SPI.end();                                                                                        // End SPI bus 
Wire.end();                                                                                       // End i2C bus 
Serial.end();                                                                                     // End serial monitor 
powerOff();                                                                                       // Turn off peripherals 
sleepMode(SLEEP_POWER_DOWN);                                                                      // Define sleep mode
sleep();                                                                                          // Sleep!
}













////////////////////////////////////////////////////////////////////////////////////////////////////
// Main loop                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

////////////////////////////////////////////////////////////////////////////////////////////////////
// If-loops for rain gauges                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

if(RG1Tip == true) {                                                                              // If-loop for rain gauge 1
  RG1Tip = false;
  InterruptTime1 = millis();
  if(labs(InterruptTime1 - LastInterrupt1) > Debounce) {
    Rain1 = Rain1 + 1;
    LastInterrupt1 = InterruptTime1;  
  }
  detachInterrupt(digitalPinToInterrupt(RG1));                                                    // Removes RG1 interrupt
  pinMode(RG1, INPUT_PULLUP);                                                                     // Pull up RG1 pin
  attachInterrupt(digitalPinToInterrupt(RG1), RG1Flip, LOW);                                      // Attach RG1 interrupt
}

if(RG2Tip == true) {                                                                              // If-loop for rain gauge 2
  RG2Tip = false;
  InterruptTime2 = millis();
  if(labs(InterruptTime2 - LastInterrupt2) > Debounce) {
    Rain2 = Rain2 + 1;
    LastInterrupt2 = InterruptTime2;  
  }
  detachInterrupt(digitalPinToInterrupt(RG2));                                                    // Removes RG2 interrupt
  pinMode(RG2, INPUT_PULLUP);                                                                     // Pull up RG2 pin
  attachInterrupt(digitalPinToInterrupt(RG2), RG2Flip, LOW);                                      // Attach RG2 interrupt
}

if(RG3Tip == true) {                                                                              // If-loop for rain gauge 3
  RG3Tip = false;
  InterruptTime3 = millis();
  if(labs(InterruptTime3 - LastInterrupt3) > Debounce) {
    Rain3 = Rain3 + 1;
    LastInterrupt3 = InterruptTime3;  
  }
  detachInterrupt(digitalPinToInterrupt(RG3));                                                    // Removes RG3 interrupt
  pinMode(RG3, INPUT_PULLUP);                                                                     // Pull up RG3 pin
  attachInterrupt(digitalPinToInterrupt(RG3), RG3Flip, LOW);                                      // Attach RG3 interrupt
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Log data                                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

if(alarmRing == 1) {                                                                              // Check alarm flag

powerOn();
Serial.begin(9600);                                                                               // Call serial monitor 
SPI.begin(); delay(5);                                                                            // Begin SPI
Wire.begin(); delay(5);                                                                           // Begin i2C

////////////////////////////////////////////////////////////////////////////////////////////////////
// Set next alarm                                                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

ds3231.begin();                                                                                   // Begin RTC
tNow = ds3231.get();                                                                              // Get current time
tAlarm = tNow + tInterval;                                                                        // Set alarm time

detachInterrupt(digitalPinToInterrupt(WAKE));                                                     // Detach SQW interrupt pin 
pinMode(WAKE, INPUT_PULLUP);                                                                      // Pull up SQW interrupt pin 
attachInterrupt(digitalPinToInterrupt(WAKE), alarmOn, FALLING);                                   // Set interrupt condition

ds3231.clearAlarm(DS3232RTC::ALARM_1); delay(5); alarmRing = 0;                                   // Clear Alarm 1 first
ds3231.setAlarm(DS3232RTC::ALM1_MATCH_HOURS, second(tAlarm), minute(tAlarm), hour(tAlarm), 0);    // Set Alarm 1
ds3231.alarmInterrupt(DS3232RTC::ALARM_1, true);                                                  // Enable Alarm 1 interrupt
Wire.beginTransmission(0x68); Wire.write(0x0E); Wire.write(0x5D); Wire.endTransmission();         // Enable SQW on battery

delay(10);                                                                                        // Buffer after setting alarm

////////////////////////////////////////////////////////////////////////////////////////////////////
// Log data on SD                                                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

sd.begin(SD_CONFIG);                                                                              // Configure SD card
datafile = sd.open("datafile.txt", O_WRITE | O_AT_END);                                           // Open datafile.txt

Serial.print(year(tNow)); Serial.print(",");                                                      // Print current time
Serial.print(month(tNow)); Serial.print(",");                                                     // Print current time
Serial.print(day(tNow)); Serial.print(",");                                                       // Print current time
Serial.print(hour(tNow)); Serial.print(",");                                                      // Print current time
Serial.print(minute(tNow)); Serial.print(",");                                                    // Print current time
Serial.print(second(tNow)); Serial.print(",");                                                    // Print current time

OnBoardADS();                                                                                     // Print on-board ADS

for (uint8_t j = 0; j < 8; j++) {                                                                 // Select 8 channels in turn
  TCA(j);                                                                                         // Select TCA9548A channel
  printMUX();                                                                                     // Print data from the channel 
  resetMUX();                                                                                     // Reset TCA9548A 
  }                                 

Serial.print(Rain1); Serial.print(",");                                                           // Print rain gauge 1 count
Serial.print(Rain2); Serial.print(",");                                                           // Print rain gauge 2 count
Serial.print(Rain3); Serial.print(",");                                                           // Print rain gauge 3 count

Rain1 = 0; Rain2 = 0; Rain3 = 0;                                                                  // Clear all rain gauge counts

Serial.print("\n");                                                                               // Write a new line
datafile.close();                                                                                 // Close datafile.txt

Serial.println("Logging complete!");                                                              // Signal logging completion
delay(25);                                                                                        // Buffer for serial printing
SPI.end();                                                                                        // End SPI bus 
Wire.end();                                                                                       // End i2C bus 
Serial.end();                                                                                     // End serial monitor 
powerOff();                                                                                       // Turn off peripherals 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// All codes end with sleep                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

sleepMode(SLEEP_POWER_DOWN);                                                                      // Define sleep mode
sleep();                                                                                          // Sleep!
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Loops for powering switching and alarm events                                                  //
////////////////////////////////////////////////////////////////////////////////////////////////////

void alarmOn() {                                                                                  // ISR for RTC SQW
  alarmRing = 1;                                                                                  // Raise alarm flag
  noSleep();                                                                                      // Exit sleep
  }

void powerOn() {
pinMode(PSW, OUTPUT); digitalWrite(PSW, LOW);                                                     // Turn on peripherals
pinMode(LED, OUTPUT); digitalWrite(LED, HIGH);                                                    // Turn on LED
delay(15);                                                                                        // Buffer for powering up 
}

void powerOff() {
pinMode(PSW, OUTPUT); digitalWrite(PSW, HIGH);                                                    // Turn off peripherals
pinMode(LED, OUTPUT); digitalWrite(LED, LOW);                                                     // Turn off LED
pinMode(SCL, INPUT); digitalWrite(SCL, LOW);                                                      // Force SCL pin LOW 
pinMode(SDA, INPUT); digitalWrite(SDA, LOW);                                                      // Force SDA pin LOW 
delay(15);                                                                                        // Buffer for powering down 
}

void blinkLED() {
digitalWrite(LED, HIGH); delay(250); 
digitalWrite(LED, LOW); delay(250); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Set up on-board ADS1115 with 0x4B address                                                      // 
////////////////////////////////////////////////////////////////////////////////////////////////////

void OnBoardADS() {
if(ADS0.begin()) {                                                                                // Check if ADS0 begins
   ADS0.setMode(1);                                                                               // Set single mode for ADS0
   ADS0.setGain(0);                                                                               // Set zero gain for ADS0
   ADS0.setDataRate(4);                                                                           // Set data rate for ADS0 
   delay(1);                                                                                      // Allow time to configure ADS0
  for (uint8_t ADSCHL = 0; ADSCHL < 4; ADSCHL++) {                                                // Define ADS0 for-loop 
    if(ADS0.isReady()) {                                                                          // Get ADS0 ready
      int16_t ads = ADS0.readADC(ADSCHL);                                                         // Store ADS0 reading into ads
      Serial.print(ads);                                                                        // Print ADS0 reading  
      if(ADSCHL == 3) { 
        Serial.print(",");
        } else {
        Serial.print(",");  
        }
      }                                                                                             
    }                                                                                               
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Set up off-board ADS1115 with 0x48 address                                                     // 
////////////////////////////////////////////////////////////////////////////////////////////////////

void OffBoardADS1() {
if(ADS1.begin()) {                                                                                // Check if ADS1 begins
   ADS1.setMode(1);                                                                               // Set single mode for ADS1
   ADS1.setGain(0);                                                                               // Set zero gain for ADS1
   ADS1.setDataRate(4);                                                                           // Set data rate for ADS1
   delay(1);                                                                                      // Allow time to configure ADS1
  for (uint8_t ADSCHL = 0; ADSCHL < 4; ADSCHL++) {                                                // Define ADS1 for-loop 
    if(ADS1.isReady()) {                                                                          // Get ADS1 ready
      int16_t ads = ADS1.readADC(ADSCHL);                                                         // Store ADS1 reading into ads
      Serial.print(ads);                                                                        // Print ADS1 reading  
      if(ADSCHL == 3) { 
        Serial.print(",");
        } else {
        Serial.print(",");  
        }
      }                                                                                             
    }                                                                                               
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Set up off-board ADS1115 with 0x49 address                                                     // 
////////////////////////////////////////////////////////////////////////////////////////////////////

void OffBoardADS2() {
if(ADS2.begin()) {                                                                                // Check if ADS2 begins
   ADS2.setMode(1);                                                                               // Set single mode for ADS2
   ADS2.setGain(0);                                                                               // Set zero gain for ADS2
   ADS2.setDataRate(4);                                                                           // Set data rate for ADS2 
   delay(1);                                                                                      // Allow time to configure ADS2
  for (uint8_t ADSCHL = 0; ADSCHL < 4; ADSCHL++) {                                                // Define ADS2 for-loop 
    if(ADS2.isReady()) {                                                                          // Get ADS2 ready
      int16_t ads = ADS2.readADC(ADSCHL);                                                         // Store ADS2 reading into ads
      Serial.print(ads);                                                                        // Print ADS2 reading  
      if(ADSCHL == 3) { 
        Serial.print(",");
        } else {
        Serial.print(",");  
        }
      }                                                                                             
    }                                                                                               
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Select TCA9548A channel                                                                        // 
////////////////////////////////////////////////////////////////////////////////////////////////////

void TCA(uint8_t i) {                                                                             
  Wire.beginTransmission(TCAADDR);                                                                // Select TCA9548A
  Wire.write(1 << i);                                                                             // Select MUX channel
  Wire.endTransmission();                                                                         // End wire transmission
  delay(1);                                                                                       // Insert buffer
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Reset TCA9548A and terminate all transmission                                                  // 
////////////////////////////////////////////////////////////////////////////////////////////////////

void resetMUX() {
  Wire.beginTransmission(TCAADDR);                                                                // Select TCA9548A
  Wire.write(0);                                                                                  // Send byte to TCA9548A
  Wire.endTransmission();                                                                         // End wire transmission
  delay(1);                                                                                       // Insert buffer
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Read SHT40, BMP280, MLX90614 from TCA9548A                                                     // 
////////////////////////////////////////////////////////////////////////////////////////////////////

void printMUX() {
  sht4x.begin(Wire, SHT40_I2C_ADDR_44);                                                           // Check for SHT40
  error = sht4x.measureHighPrecision(temperature, humidity);                                      // Error message
  if (error) { 
    delay(1);                                                                                     // Delay if no SHT40
  } else {
    Serial.print(temperature); Serial.print(",");                                             // Print temperature
    Serial.print(humidity); Serial.print(",");                                                // Print humidity
    delay(1);                                                                                     // Insert buffer
  } 

  if(bmx280.begin()) {                                                                            // Check for BMP280
    bmx280.measure();                                                                             // Measure pressure
    Serial.print(bmx280.getPressure()); Serial.print(",");                                    // Print pressure 
    delay(1);                                                                                     // Insert buffer 
  }

  if(spl06.begin()) {                                                                             // Check for SPL06-001
    spl06.measure();  
    Serial.print(spl06.pressure() * 0.01, 2); Serial.print(",");
  }

  if(mlx.begin(0x5A)) {                                                                           // Check for MLX90614
    mlx.setUnit(TEMP_C); mlx.read();                                                              // Read temperature in Celsius
    Serial.print(mlx.object(),2); Serial.print(",");                                          // Print temperature
    delay(1);                                                                                     // Insert buffer
  } 

  OffBoardADS1();                                                                                 // Check for ADS 0x48

  OffBoardADS2();                                                                                 // Check for ADS 0x49

  if(mlx.begin(0x5B)) {                                                                           // Check for MLX90614
    mlx.setUnit(TEMP_C); mlx.read();                                                              // Read temperature in Celsius
    Serial.print(mlx.object(),2); Serial.print(",");                                          // Print temperature
    delay(1);                                                                                     // Insert buffer
  } 

  if(mlx.begin(0x5C)) {                                                                           // Check for MLX90614
    mlx.setUnit(TEMP_C); mlx.read();                                                              // Read temperature in Celsius
    Serial.print(mlx.object(),2); Serial.print(",");                                          // Print temperature
    delay(1);                                                                                     // Insert buffer
  } 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ISR for tipping bucket rain gauges                                                             // 
////////////////////////////////////////////////////////////////////////////////////////////////////

void RG1Flip() { 
  RG1Tip = true;  
}
void RG2Flip() { 
  RG2Tip = true;  
}
void RG3Flip() { 
  RG3Tip = true;
}

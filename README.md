# Introduction

<p align="justify"> DE-LA-LO-MO is an Arduino-based datalogger. The full name is Delayable Latching Logging Module. It is a piece of free-and-open-source equipment for environmental monitoring. The target users are environmental scientists. This repository contains all the files needed for building and using DE-LA-LO-MO. The steps are as follows:</p>

- Send Gerber files to local manufacturers
- Buy required parts and tools
- Solder electronic parts and assemble accessories
- Install software and bootloader
- Upload sketches and configure data-logger parameters

# Table of Contents
- <a href = "https://github.com/louisleeshinghim/delalomo#hardware"> Hardware</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#tools"> Tools</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#bill-of-materials"> Bill of materials</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#main-board"> Main board</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#breakout-board"> Breakout board</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#other-hardware"> Other hardware</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#software"> Software</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#bootloader"> Bootloader</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#libraries"> Libraries</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#sketches"> Sketches</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#operation"> Operation</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#useful-links"> Useful links</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#more-about-the-project"> More about the project</a> <br/>

# Hardware 
<p align="justify">Let's gather all the materials on the bill of materials, BOM (<a href = "https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/billofmaterials.xlsx">download here</a>). Most parts are available on <a href = "https://www.digikey.com/"> DigiKey</a>. Therefore, the BOM includes the Digikey Part Number. <a href = "https://www.mouser.com/"> Mouser</a> is also good. The parts costed US$ 42 (~HK$ 326) in late 2024. To get the correct parts, please check the photographic guide in the directory Fabrication files. The following tools are needed.</p>

## Tools

| Tool | Description | 
| ---- | ----------- |
| Soldering iron | 305 °C is fine |
| Solder wire | 63:37 (tin:lead) is fine. Use higher temperature for lead-free wire |
| Solder flux | No-clean flux is better |
| A pair of tweezers | Any materials is fine. Anti-static stainless steel may be better |
| Soldering clamp stand | Optional. Those with adjustable grips are helpful |
| Isopropyl alcohol | 99% is preferred. 75% is fine. Wash PCB before and after soldering |
| Digital magnifier | USB-powered magnifier with screen |

## Bill of materials

<p align="justify">Let's gather the parts on the bill of materials, BOM (<a href = "https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/billofmaterials.xlsx">download here</a>). Most parts are available on <a href = "https://www.digikey.com/"> DigiKey</a>. Therefore, the BOM includes the Digikey Part Number. <a href = "https://www.mouser.com/"> Mouser</a> is also good. The parts costed US$ 42 (~HK$ 326) in late 2024. To get the correct parts, please check the photographic guide under the directory <a href = "https://github.com/louisleeshinghim/delalomo/tree/main/Fabrication%20files"> Fabrication files</a>. The following tools are needed.</p>

<details>
<summary>Click <b><i>here</i></b> to show the bill of materials </summary>
  
| Item | Model number | Footprint | Quantity | 
| ---- | ------------ | --------- | -------- |
| Microcontroller | ATMEGA128A-AU | TQFP-64 | 1 | 
| 8-channel I2C multiplexer | TCA9548APWR | TSSOP-24 | 1 | 
| Real-time clock | DS3231SN#T&R | SOIC-16 | 1 | 
| Quadruple bus buffer gate | SN74LVC125APWR | TSSOP14 | 1 | 
| I2C accelerator | LTC4311CSC6#TRPBF | SC-70 | 1 | 
| 16-bit analog-digital converter | ADS1115IDGSR | VSSOP-10 | 1 | 
| 10-volt Zener diode | ZM4740A-GS08 | LL-34 | 1 | 
| Logic-level, P-channel MOSFET | AO3401A | SOT-23 | 2 | 
| 3.3-volt regulator | AMS1117-3.3 | SOT-223 | 1 | 
| 5.0-volt regulator | MCP1702T-5002E/CB | SOT-23 | 1 | 
| 470 Ω | RC1206JR-07470RL | 1206 | 1 | 
| 3.3 KΩ | RC1206JR-073K3L | 1206 | 3 | 
| 4.7 KΩ | RC1206JR-074K7L | 1206 | 2 | 
| 10 KΩ | RC1206JR-0710KL | 1206 | 5 | 
| 47 KΩ | RC1206JR-0747KL | 1206 | 1 | 
| 100 KΩ | RC1206JR-07100KL | 1206 | 1 | 
| 1 MΩ | RC1206JR-071ML | 1206 | 1 | 
| 22 pF | CC1206JRNPO9BN220 | 1206 | 2 | 
| 0.1 μF | C1206C104K5RACTU | 1206 | 14 | 
| 10 μF | CC1206ZKY5V7BB106 | 1206 | 5 | 
| 16 MHz crystal | ATS16A | Through-hole | 1 | 
| 5 mm LED | LTL-4233 | Through-hole | 1 | 
| 6 mm × 6 mm, SPST tactile switch | 1825910-6 | Through-hole | 1 | 
| Push-in, eject-out MicroSD holder | MSD-4-A | N/A | 1 | 
| Vertical, CR2032-type holder | 1074 | N/A | 1 | 
| Dual, 18650-type holder | 114090053 | N/A | 1 | 
| 2-position, shrouded male header | 691321300002 | N/A | 1 | 
| 3-position, shrouded male header | 691321300003 | N/A | 7 | 
| 4-position, shrouded male header | 691321300004 | N/A | 11 | 
| 3-position, 1-row straight male | TS-103-T-A | N/A | 1 | 
| 6-position, 1-row angled male | PH1RA-06-UA | N/A | 1 | 
| 2-position, 1-row female socket | RS1-02-G | N/A | 2 | 
| 6-position, 1-row female socket | M20-7820642 | N/A | 1 | 
| 6-position, 2-row female socket | PPPC032LFBN-RC | N/A | 1 | 
| 20-AWG, 2-conductor cable | 30-00416 | N/A | 1 | 
| Custom-made board | See Gerber files | N/A | 1 | 
| 250 mm x 75 mm x 80 mm, IP65 box | XL-KT 250*80*70MM | N/A | 1 | 
| Self-adhesive, hook-and-loop fastener | HHB-0B | N/A | 1 | 
| M4 × 0.8, pan-head | 50M040070N008 | N/A | 2 | 
| M4 × 0.8, flat | 16M04090080 | N/A | 4 | 

</details>



DE-LA-LO-MO consists of two printed circuit boards (PCBs), a main board and a breakout board. Thus, there are two sets of files, each having a schematic, a PCB layout, and a Gerber file. The schematics and PCB layout were drawn and can be modified in <a href = "https://easyeda.com"> EasyEDA Standard Version</a>. Normally, the existing design of DE-LA-LO-MO can satisfy most user requirements. Users can simply send the two Gerber files to the local PCB manufacturer. 

- Main board Gerber file: <a href = "https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/delalomo_gerber.zip"> Click to download</a> </br>
- Breakout board Gerber file: <a href = "https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/delalomo_breakout_gerber.zip"> Click to download</a> </br>

A Gerber file stores the information for the physical production of PCB and stencil. Nearly all PCB manufacturers accept Gerber file. Here are the PCB specifications of DE-LA-LO-MO:
- FR4 material
- 1.6 mm board thickness
- HASL surface finish
- 1 ounce copper weight

Nonetheless, users can modify DE-LA-LO-MO according to their own needs. The steps are listed out in the <a href = "https://github.com/louisleeshinghim/delalomo/tree/main/Fabrication%20files"> Fabrication files</a> folder.


## Main board

<p align="justify"> Most passive components, e.g. resistors and capacitors, can be soldered with the aid of the component value on the PCB silkscreen. Properly orient the integrated circuits (IC) by matching the marking on the IC and that on the PCB silkscreen. In order to reduce soldering work, the solder pads of the unused pins on ATMEGA128A were removed. Don't worry, the remaining pins will hold the microcontroller in place. Also, match the cathode mark on the diode (negative side) to the cathode mark on the silkscreen. </p>

A normal digital magnifier is fine.


![Alt text](https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/schematic_delalomo.png?raw=true "Title")

## Breakout board

This breakout board is simply a MicroSD holder. The schematic is similar to MicroSD module except a little modification to the MISO line. See <a href = "https://forum.arduino.cc/t/arduino-nano-enc28j60-and-sd-card-reader/1000054/5"> this post</a> and <a href = "https://forum.arduino.cc/t/solved-sd-card-randomly-stops-working/330205"> this post</a>.

![Alt text](https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/schematic_delalomo_breakout.png?raw=true "Title")

The breakout board is positioned perpendicular to the main board via a six-pin header for the power, ground, and four-wire SPI lines.

All files related to this section can be found in the folder Fabrication file.

## Other hardware

In addition to the PCB-related parts, the followings are needed:
- USB mini cable:
- USB type-B cable
- Arduino UNO board
- FTDI breakout: 5V-compatible
- Six DuPont wires
- A computer:

# Software 

After PCB assembly, it is time to burn the bootloader and upload the sketches.

All programs were written in Arduino IDE Version 1.8.X. Download <a href = "https://www.arduino.cc/en/software"> here</a>. Arduino IDE Version 1.8.X is recommended, although newer IDE versions, e.g. 2.3.X, may work. 

## Bootloader

### Arduino core

Bootloader is a small piece of software that allows uploading of sketches onto the microcontroller. <a href = "https://github.com/MCUdude/MegaCore"> MegaCore</a> is a collection of codes required for the interfacing of ATMEGA128A. Connect your computer to the Internet and install MegaCore in Arduino IDE:
1. Open Arduino IDE 
2. Copy the following URL in Arduino IDE (<i>File > Preferences > Additional Boards Manager URL</i>)
```
https://mcudude.github.io/MegaCore/package_MCUdude_MegaCore_index.json
```
3. Click Install to use MegaCore (<i>Tools > Board > Boards Manager > MegaCore > Install</i>)

### Pin connection

<p align="justify"> Then, physical connection must be established between Arduino UNO and DE-LA-LO-MO via DuPont wires. Use high-quality DuPont wires. Broken wires often cause failure to burn bootloader. Caution should also be paid to wiring. Please follow the pin arrangement below and check the actual connection carefully. </p>

- Pin 10 -> RST
- Pin 11 -> RX
- Pin 12 -> TX
- Pin 13 -> SCK
- 5V -> VCC
- GND -> GND

### Burn bootloader

<p align="justify"> We are one step away from burning the bootloader into DE-LA-LO-MO. Turn the Arduino UNO as an In-circuit Serial Programmer (ISP) in Arduino IDE. The technical details are explained in an <a href = "https://support.arduino.cc/hc/en-us/articles/4841602539164-Burn-the-bootloader-on-UNO-Mega-and-classic-Nano-using-another-Arduino"> Arduino article </a>. However, for simplicity the following steps are used for DE-LA-LO-MO: </p>

1. Connect the Arduino UNO board to computer with USB type-B cable
2. Select the correct board (<i>Tools > Board > Arduino AVR Boards > Arduino Uno</i>)
3. Select the engaged COM port in Arduino IDE (<i>Tools > Port</i>)
4. Open the sketch (<i>File > Examples > 11.ArduinoISP > ArduinoISP</i>)
5. Upload the opened sketch to Arduino UNO (<i>Ctrl + U</i>) 
6. Turn Arduino UNO into a programmer (<i>Tools > Programmer > Arduino as ISP</i>)
7. Select microcontroller to be burnt (<i>Tools > Board > MegaCore > ATMEGA128 </i>)
8. Select under the <i>Tools</i> dropdown menu:
   - <i>Clock > External 16 MHz</i>
   - <i>BOD > BOD disabled</i>
   - <i>EEPROM > EEPROM not retained</i>
   - <i>Bootloader > Yes (UART0)</i>
9. BURN the bootloader! (<i>Tools > Burn Bootloader</i>)
10. Wait for the dialog <b>Done burning bootloader</b>



## Libraries

To install Arduino libraries, the preferred method is through Arduino IDE's Library Manager (<i>Tools > Manage Libraries</i>). Then, search for the libraries and click install. To install the libraries in this way, Internet connection is a prerequisite. The second method is to install libraries as downloaded zipped folders (<i>Sketch > Include Library > Add .ZIP Library</i>). Install the following libraries support the basic functions of DE-LA-LO-MO.

| Library | Description |
| ------- | ----------- |
| <a href = "https://github.com/RobTillaart/ADS1X15"> ADS1X15</a> | Read analog voltage on ADS1115 channel after channel |
| <a href = "https://github.com/JChristensen/DS3232RTC"> DS3232RTC</a> | Request current time and set alarm for data-logging events |
| <a href = "https://github.com/greiman/SdFat"> SdFat</a> | Read the text files on and save data to MicroSD |
| <a href = "https://github.com/janelia-arduino/Streaming"> Streaming</a> | Recognise the text in the .txt files on MicroSD |

Arduino libraries for different sensors are required to interface the sensors to DE-LA-LO-MO. At this moment, only microclimate sensors are involved. Communications are made over the I2C interface. Some sensor libraries are provided by the sensor manufacturers. The codes in the main sketch may require modification if libraries are updated. 

| Library | Description |
| ------- | ----------- |
| <a href = "https://github.com/ArtronShop/ArtronShop_SPL06-001"> ArtronShop_SPL06-001</a> | Read barometric pressure from Goertek SPL06-001 |
| <a href = "https://github.com/christandlg/BMx280MI"> BMx280MI</a> | Read barometric pressure from Bosch BMP280 |
| <a href = "https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library"> SparkFun MLX90614</a> | Read non-contact surface temperature from Melexis MLX90614 |
| <a href = "https://github.com/Sensirion/arduino-i2c-sht4x"> Sensirion I2C SHT4x</a> | Read air temperature & relative humidity from Sensirion SHT4X family sensors |

The following libraries do not need to be installed. They are bundled with every Arduino platform. Still, they have to be included at the beginning of the sketch. For DE-LA-LO-MO, the library <i>Wire</i> is important for communicating sensors, and <i>SPI</i> for MicroSD. Currently, no sensors are communicated to over the SPI interface.

| Library | Description |
| ------- | ----------- |
| <a href = "https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h"> Arduino</a> | Enable the basic functions in Arduino |
| <a href = "https://docs.arduino.cc/language-reference/en/functions/communication/wire/"> Wire</a> | Communicate with I2C devices, namely DS3231, ADS1115, TCA9548A, and I2C sensors |
| <a href = "https://docs.arduino.cc/language-reference/en/functions/communication/SPI/"> SPI</a> | Communicate with SPI devices, most importantly the MicroSD |

## Sketches

### Uploading a sketch

A sketch is a programme that is run by the microcontroller. Four sketches are used. The sketches are very long. Please click on the collapsed sections to expand the code blocks. Copy the whole sketch using the button on the top right and paste into Arduino IDE. 


Do not reverse the pins.

### I2C scanner

<p align="justify"> This sketch scans I2C devices by showing the address of discovered devices. Users can find DS3231SN (<i>0x68</i>), TCA9548A (<i>0x70</i>), ADS1115 (<i>0x4B</i>) on a DE-LA-LO-MO. If undetected, possible reasons may be faulty chip or bad soldering. This sketch is actually an adapter version of the I2C scanner from the <i>Wire</i> library. </p>

<details>
<summary>Click <b><i>here</i></b> to show the codes of the I2C scanner </summary>

```
#include <Wire.h>


void setup()
{
  pinMode(14, OUTPUT); digitalWrite(14, LOW);                                                     // Turn on i2C
  pinMode(42, OUTPUT); digitalWrite(42, HIGH);                                                    // Turn on LED
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}


void loop()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(2000);           // wait 2 seconds for next scan
}
```
</details>


### RTC setter 

<details>
<summary>Click <b><i>here</i></b> to show the codes of the RTC scanner </summary>

```
// Arduino DS3232RTC Library (https://github.com/JChristensen/DS3232RTC)
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch to display the date and time from a DS3231 or DS3232 RTC every second.
// Display the temperature once per minute. 
// The DS3231 does a temperature conversion once every 64 seconds.)
//
// Set the date and time by entering the following on the Arduino serial monitor:
//  year,month,day,hour,minute,second,
//
// Where
//  year can be two or four digits,
//  month is 1-12,
//  day is 1-31,
//  hour is 0-23, and
//  minute and second are 0-59.
//
// Entering the final comma delimiter (after "second") will avoid a
// one-second timeout and will allow the RTC to be set more accurately.
//
// No validity checking is done, invalid values or incomplete syntax
// in the input will result in an incorrect RTC setting.
// Jack Christensen 08Aug2013

#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>      // https://github.com/janelia-arduino/Streaming
#include <Wire.h>
DS3232RTC myRTC;

void setup()
{
    pinMode(14, OUTPUT); digitalWrite(14, LOW);                                                     // Turn on i2C
    pinMode(42, OUTPUT); digitalWrite(42, HIGH);                                                    // Turn on LED
    Wire.begin();

    Serial.begin(9600);
    Serial << F( "\n" __FILE__ "\n" __DATE__ " " __TIME__ "\n" );
    myRTC.begin();

    // setSyncProvider() causes the Time library to synchronize with the
    // external RTC by calling RTC.get() every five minutes by default.
    setSyncProvider(myRTC.get);
    Serial << F("RTC Sync");
    if (timeStatus() != timeSet) Serial << F(" FAIL!");
    Serial << endl;
}

void loop()
{
    static time_t tLast;
    time_t t;
    tmElements_t tm;

    // check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
    if (Serial.available() >= 12) {
        // note that the tmElements_t Year member is an offset from 1970,
        // but the RTC wants the last two digits of the calendar year.
        // use the convenience macros from the Time Library to do the conversions.
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000)
            Serial << F("Error: Year must be two digits or four digits!") << endl;
        else {
            if (y >= 1000)
                tm.Year = CalendarYrToTm(y);
            else    // (y < 100)
                tm.Year = y2kYearToTm(y);
            tm.Month = Serial.parseInt();
            tm.Day = Serial.parseInt();
            tm.Hour = Serial.parseInt();
            tm.Minute = Serial.parseInt();
            tm.Second = Serial.parseInt();
            t = makeTime(tm);
            myRTC.set(t);   // use the time_t value to ensure correct weekday is set
            setTime(t);
            Serial << F("RTC set to: ");
            printDateTime(t);
            Serial << endl;
            // dump any extraneous input
            while (Serial.available() > 0) Serial.read();
        }
    }

    t = now();
    if (t != tLast) {
        tLast = t;
        printDateTime(t);
        if (second(t) == 0) {
            float c = myRTC.temperature() / 4.;
            float f = c * 9. / 5. + 32.;
            Serial << F("  ") << c << F(" C  ") << f << F(" F");
        }
        Serial << endl;
    }
}

// print date and time to Serial
void printDateTime(time_t t)
{
    printDate(t); Serial << ' '; printTime(t);
}

// print time to Serial
void printTime(time_t t)
{
    printI00(hour(t), ':'); printI00(minute(t), ':'); printI00(second(t), ' ');
}

// print date to Serial
void printDate(time_t t)
{
    printI00(day(t), 0);
    Serial << monthShortStr(month(t)) << _DEC(year(t));
}

// Print an integer in "00" format (with leading zero),
// followed by a delimiter character to Serial.
// Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
    if (val < 10) Serial << '0'; Serial << _DEC(val);
    if (delim > 0) Serial << delim; return;
}
```
</details>


### Main sketch - Serial display

### Main sketch - Local data storage


# Operation


# Useful links

Digikey - https://www.digikey.com </br>
Mouser - https://www.mouser.com </br>
Arduino IDE - https://www.arduino.cc/en/software </br>
EasyEDA - https://easyeda.com </br>
MegaCore - https://github.com/MCUdude/MegaCore </br>

# More about the project

<p align="justify"> The development of DE-LA-LO-MO kicked off with a research project starting in 2022 and entitled <i>Pioneering environmental sensing technologies in microclimate research: evidence-based study of urban green infrastructures combatting urban heat island and climate change</i>. The developer, <a href = "https://orcid.org/0000-0001-7358-7875"> Louis, Lee Shing Him</a>, is the project's budget holder. Dating back to 2018, he had completed a microclimate monitoring project in Hong Kong. Later, his first application for a research funding failed. The failure came with a stinging comment, "excessively huge equipment cost". </p>

True, many researchers would unreservedly agree that monitoring equipment is expensive, and Louis is among them. He bought an Arduino kit and started experimenting, while writing a new project proposal. He has little to none knowledge on electronics and soldering, except the experience of putting together a few guitar stomp boxes. But he knew that breaking the cost barrier and bringing improvements in monitoring equipment can benefit many researchers. Datalogger, which is typically the heart of monitoring stations, became the starting point. And that is the story of DE-LA-LO-MO.

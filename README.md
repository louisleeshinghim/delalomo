# Introduction

<p align="justify"> DE-LA-LO-MO is an Arduino-based datalogger. The full name is Delayable Latching Logging Module. It is a piece of free-and-open-source equipment for environmental monitoring. The target users are environmental scientists. This repository contains all the files needed for building and using DE-LA-LO-MO. The steps are as follows:</p>

- Send Gerber files to local manufacturers
- Buy and solder electronic parts and accessories
- Install software and bootloader
- Upload sketches and configure data-logger parameters

# Table of Contents
- <a href = "https://github.com/louisleeshinghim/delalomo#hardware"> Hardware</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#main-board"> Main board</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#breakout-board"> Breakout board</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#software"> Software</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#bootloader"> Bootloader</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#libraries"> Libraries</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#useful-links"> Useful links</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#more-about-the-project"> More about the project</a> <br/>

# Hardware 
Let's gather all the materials based on the bill of materials (BOM). Most parts are available on <a href = "https://www.digikey.com/"> DigiKey</a>. Therefore, the BOM includes the Digikey Part Number. <a href = "https://www.mouser.com/"> Mouser</a> is also good. The parts costed US$ 42 (~HK$ 326) in late 2024. 

To get the correct parts, 

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

In order to reduce soldering work, the solder pads of the unused pins on ATMEGA128A were removed. Don't worry, there are still many pins to solder, and the microcontroller will not fall off. 

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
- FTDI breakout: 5V-compatible
- Six DuPont wires
- A computer:

# Software 

After PCB assembly, it is time to burn the bootloader and upload the sketches.

All programs were written in Arduino IDE Version 1.8.X. Download <a href = "https://www.arduino.cc/en/software"> here</a>. Arduino IDE Version 1.8.X is recommended, although newer IDE versions, e.g. 2.3.X, may work. 

## Bootloader

Bootloader is a small piece of software that allows uploading of sketches onto the microcontroller. <a href = "https://github.com/MCUdude/MegaCore"> MegaCore</a> is a collection of codes required for the interfacing of ATMEGA128A. Connect your computer to the Internet and install MegaCore in Arduino IDE:
1. Open Arduino IDE 
2. Copy the following URL in Arduino IDE (File > Preferences > Additional Boards Manager URL)
```https://mcudude.github.io/MegaCore/package_MCUdude_MegaCore_index.json```
3. Click Install to use MegaCore (Tools > Board > Boards Manager > MegaCore > Install)


Burning bootloader.
USB
Arduino UNO
Six Dupont wires

## Libraries

To install the libraries, please open Library Manager in Arduino IDE (Tools > Manage Libraries). Then, search for the following libraries and click install.

| Library | Description |
| ------- | ----------- |
| <a href = "https://github.com/RobTillaart/ADS1X15"> ADS1X15</a> | Read analog voltage on ADS1115 channel after channel |
| <a href = "https://github.com/JChristensen/DS3232RTC"> DS3232RTC</a> | Request current time and set alarm for data-logging events |
| <a href = "https://github.com/greiman/SdFat"> SdFat</a> | Read the text files on and save data to MicroSD |
| <a href = "https://github.com/janelia-arduino/Streaming"> Streaming</a> | Recognise the text in the .txt files on MicroSD |


Communications are made over the I2C interface. 

| Library | Description |
| ------- | ----------- |
| <a href = "https://github.com/ArtronShop/ArtronShop_SPL06-001"> ArtronShop_SPL06-001</a> | Read barometric pressure from Goertek SPL06-001 |
| <a href = "https://github.com/christandlg/BMx280MI"> BMx280MI</a> | Read barometric pressure from Bosch BMP280 |
| <a href = "https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library"> SparkFun MLX90614</a> | Read non-contact surface temperature from Melexis MLX90614 |
| <a href = "https://github.com/Sensirion/arduino-i2c-sht4x"> Sensirion I2C SHT4x</a> | Read air temperature & relative humidity from Sensirion SHT4X family sensors |

The following libraries do not need to be installed. They are bundled with every Arduino platform. Still, they have to be included at the beginning of the sketch.
| Library | Description |
| ------- | ----------- |
| <a href = "https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h"> Arduino</a> | Enable the basic functions in Arduino |
| <a href = "https://docs.arduino.cc/language-reference/en/functions/communication/wire/"> Wire</a> | Communicate with I2C devices, namely DS3231, ADS1115, TCA9548A, and an assortment of sensors |
| <a href = "https://docs.arduino.cc/language-reference/en/functions/communication/SPI/"> SPI</a> | Communicate with SPI devices, most importantly the MicroSD |

## Sketches
I2C checker
RTC
Main sketch


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

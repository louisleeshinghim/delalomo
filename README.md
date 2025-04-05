# Introduction

<p align="justify"> DE-LA-LO-MO is an Arduino-based datalogger. The full name is Delayable Latching Logging Module. It is a piece of free-and-open-source equipment for environmental monitoring. The target users are environmental scientists. This repository contains all the files needed for building and using DE-LA-LO-MO. </p>

# Table of Contents
- <a href = "https://github.com/louisleeshinghim/delalomo#hardware"> Hardware</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#main-board"> Main board</a> <br/>
  - <a href = "https://github.com/louisleeshinghim/delalomo#breakout-board"> Breakout board</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#software"> Software</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#useful-links"> Useful links</a> <br/>
- <a href = "https://github.com/louisleeshinghim/delalomo#more-about-the-project"> More about the project</a> <br/>

# Hardware 

Let's gather all the materials. With a bill of materials (BOM), buying the parts is similar to grocery shopping. Most parts are available on <a href = "https://www.digikey.com/"> DigiKey</a>. Therefore, the BOM includes the Digikey Part Number. <a href = "https://www.mouser.com/"> Mouser</a> is also good. The parts costed US$ 42 (~HK$ 326) in late 2024. 

To get the correct parts, 

DE-LA-LO-MO consists of two printed circuit boards (PCBs), a main board and a breakout board. Thus, there are two sets of files, each having a schematic, a PCB layout, and a Gerber file. The schematics and PCB layout were drawn in <a href = "https://easyeda.com"> EasyEDA Standard Version</a>. Normally, if the existing design of DE-LA-LO-MO satisfies the user requirements, the Gerber can be sent to the local PCB manufacturer. Nonetheless, if users need to modify the circuit, the following steps are recommended: 
1. Import the schematic file in EasyEDA under a new project folder (File > Open > EasyEDA)
2. Save the schematic with a user-defined title (File > Save > Save as New Project)
3. Import the corresponding PCB layout file (File > Open > EasyEDA)
4. Save the layout by choosing the same project title (File > Save > Save to Existing Project)
5. Make any necessary changes to the schematic and update the PCB (Alt + U)
6. Export to Gerber file (Fabrication > PCB Fabrication File > Yes, check DRC > Generate Gerber)
7. Send the freshly exported Gerber file to PCB manufacturer

A Gerber file stores the information for the physical production of PCB and stencil. Nearly all PCB manufacturers accept Gerber file. Here are the PCB specifications of DE-LA-LO-MO:
- FR4 material
- 1.6 mm board thickness
- HASL surface finish
- 1 ounce copper weight

## Main board

In order to reduce soldering work, the solder pads of the unused pins on ATMEGA128A were removed. Don't worry, there are still many pins to solder, and the microcontroller will not fall off. 

![Alt text](https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/schematic_delalomo.png?raw=true "Title")

## Breakout board

This breakout board is simply a MicroSD holder. The schematic is similar to MicroSD module except a little modification to the MISO line. See <a href = "https://forum.arduino.cc/t/arduino-nano-enc28j60-and-sd-card-reader/1000054/5"> this post</a> and <a href = "https://forum.arduino.cc/t/solved-sd-card-randomly-stops-working/330205"> this post</a>.

![Alt text](https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/schematic_delalomo_breakout.png?raw=true "Title")

The breakout board is positioned perpendicular to the main board via a six-pin header for the power, ground, and four-wire SPI lines.

All files related to this section can be found in the folder Fabrication file.

## Other hardware

In addition to the PCB-related parts, USB mini cable, USB to FTDI breakout, and of course a computer.

# Software 

After PCB assembly, it is time to burn the bootloader and upload the sketches.

All programs were written in Arduino IDE Version 1.8.X. Download <a href = "https://www.arduino.cc/en/software"> here</a>. Arduino IDE Version 1.8.X is recommended, although newer IDE versions, e.g. 2.3.X, may work.

MegaCore is a collection of codes required for the interfacing of ATMEGA128A. Check the repository <a href = "https://github.com/MCUdude/MegaCore"> here</a> if more information is needed. Connect your computer to the Internet and install it in Arduino IDE:
1. Open Arduino IDE 
2. Copy the following URL in Arduino IDE (File > Preferences > Additional Boards Manager URL)
```https://mcudude.github.io/MegaCore/package_MCUdude_MegaCore_index.json```
3. Click Install to use MegaCore (Tools > Board > Boards Manager > MegaCore > Install)


Arduino Libraries

Bootloader
I2C checker
RTC
Main sketch

# Useful links

Digikey - https://www.digikey.com </br>
Mouser - https://www.mouser.com </br>
Arduino IDE - https://www.arduino.cc/en/software </br>
EasyEDA - https://easyeda.com </br>
MegaCore - https://github.com/MCUdude/MegaCore </br>

# More about the project

<p align="justify"> The development of DE-LA-LO-MO kicked off with a research project starting in 2022 and entitled <i>Pioneering environmental sensing technologies in microclimate research: evidence-based study of urban green infrastructures combatting urban heat island and climate change</i>. The developer, <a href = "https://orcid.org/0000-0001-7358-7875"> Louis, Lee Shing Him</a>, is the project's budget holder. Dating back to 2018, he had completed a microclimate monitoring project in Hong Kong. Later, his first application for a research funding failed. The failure came with a stinging comment, "excessively huge equipment cost". </p>

True, many researchers would unreservedly agree that monitoring equipment is expensive, and Louis is among them. He bought an Arduino kit and started experimenting, while writing a new project proposal. He has little to none knowledge on electronics and soldering, except the experience of putting together a few guitar stomp boxes. But he knew that breaking the cost barrier and bringing improvements in monitoring equipment can benefit many researchers. Datalogger, which is typically the heart of monitoring stations, became the starting point. And that is the story of DE-LA-LO-MO.

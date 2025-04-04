# Introduction

DE-LA-LO-MO is an Arduino-based datalogger. The full name is Delayable Latching Logging Module. The abbreviation features the first syllable of each word in the full name. It is a piece of free-and-open-source equipment for environmental monitoring. The target users are environmental scientists. This repository contains all the files needed for building and using DE-LA-LO-MO. 

What can you find in this repository?

# Hardware 

Let's build DE-LA-LO-MO! The first step is to gather all the materials. The bill of materials (BOM) describes all the necessary parts. Most of them can be bought on <a href = "https://www.digikey.com/"> DigiKey</a>. Therefore, the Digikey Part Number has been included. Another convenient platform is <a href = "https://www.mouser.com/"> Mouser</a>. Just for reference, the material costs US$ 42 (~HK$ 326) in late 2024. 

To get the correct parts, 

DE-LA-LO-MO consists of two printed circuit boards (PCBs), a main board and a breakout board. Thus, there are two sets of files, each having a schematic, a PCB layout, and a Gerber file. The schematics and PCB layout were drawn in <a href = "https://easyeda.com"> EasyEDA Standard Version</a>. Normally, if the existing design of DE-LA-LO-MO satisfies the user requirements, the Gerber can be sent to the local PCB manufacturer. Nonetheless, if users need to modify the circuit, the following steps are recommended: 
1. Import the schematic file in EasyEDA under a new project folder (File > Open > EasyEDA)
2. Save the schematic with a user-defined title (File > Save > Save as New Project)
3. Import the corresponding PCB layout file (File > Open > EasyEDA)
4. Save the layout by choosing the same project title (File > Save > Save to Existing Project)
5. Make any necessary changes to the schematic and update the PCB (Alt + U)
6. Run the design rule checker (Design > Check DRC)
7. Export to Gerber file (Fabrication > PCB Fabrication File > Generate Gerber)
8. Send the freshly exported Gerber file to PCB manufacturer

A Gerber file stores the information for the physical production of PCB and stencil. Nearly all PCB manufacturers accept Gerber file. Here are the PCB specifications of DE-LA-LO-MO:
- FR4 material
- 1.6 mm board thickness
- HASL surface finish
- 1 ounce copper weight

## Main board

![Alt text](https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/schematic_delalomo.png?raw=true "Title")

## Breakout board

![Alt text](https://github.com/louisleeshinghim/delalomo/blob/main/Fabrication%20files/schematic_delalomo_breakout.png?raw=true "Title")

Schematic
Layout
Gerber

All files related to this section can be found in the folder Fabrication file.


# Software 

All programs were written in Arduino IDE Version 1.8.X (https://www.arduino.cc/en/software). Arduino IDE Version 1.8.X is recommended, although newer IDE versions, e.g. 2.3.X, may work.


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

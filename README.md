# Electronic_Load

The aim of this project is to design high power (around 200W) electronic load. It will be developed on STM32 uC. Whole repository will feature electronic schematic, PCB and code.

### Used external libralies
https://github.com/afiskon/stm32-ssd1306

### Current problems

I have encoutered two issues with my PCB design:
* Wrong D4 pinout, pins are mixed so diode does not conduct any current 
* Nucleo connectors are moved 2.54 mm to the side

Both will be fixed in another PCB revision.

### Differences between schematic and PCB

To ease further prototyping I made following changes:
* Instead of 4 1 Ohm resistor I used one 12 Ohm to lower the maximum current,
* Used only one NMOS, that is because the current will be lower now and if something breaks, it will be cheaper to replace,
* Shorted every potentiometer, they are supposed to be used for voltage compensation, but during this stage of prototyping they will be useless,
* In place of D4 I used random 1N4007 diode to keep reverse polarity protection,
* Removed eFuse, because it didn't work correctly (I hope Murphy didn't get it).

Changes may be obsereved on the photo below.

![Soldered PCB photo](/PCB_FILES/soldered_pcb.jpg)
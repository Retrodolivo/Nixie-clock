# Nixie-clock
## Description

<p align="center">
<img src="img/header_gif_small.gif" width="60%"></p>

A main feature of this kind of watches is a soft and warm glow of [nixie tubes](https://en.wikipedia.org/wiki/Nixie_tube). Nixie clocks are getting more and more popular nowadays. So I'll tell you about my nixie clock version.

### Features
* Time display (hh:mm) with the possibility of time setting via buttons.
* External temperature display. Showing on every minute for 3 seconds. Digital thermometer is 1-wire DS18b20.
* RGB backlight. Fixed colors changes via button on front panel. Brightness adjustment via potentiometer on back panel.

### Power
There are two ways of power supply designing: use of transformer or step-up converter. Transformer is a bulky solution. Also it's quite dangerous due to high voltage connector. So I decide to use a step-up converter based on popular MC34063 IC. 

<p align="center">
<img src="img/power_supply.jpeg" width="60%"></p>

This is classic scheme of impulse dc-dc converter. The key principle that energy is storing in inductor and capacitor at On-state of the switch. And realising at Off-state. Switch state is controlling by PWM controller(MC34063). Elements values was chosen experimentaly according to MC34063 datasheet. Input voltage is +9 volts AC which comes from external impulse power supply unit. For logic part supply I used an linear regulator LM3805 +5 volts output.

### Logic

<p align="center">
<img src="img/clock_block.jpeg" width="60%"></p>

Real time clock source is DS3231 IC. It's quite accurate RTC with an integrated temperaturecompensated crystal oscillator. I'm using it in every "clock" project.
Cathodes are controlling via K155ID1 high voltage decoder. Its output sets according input pins states in binary. Nixie tubes are switching dynamicly at ~500Hz.
Temperature sensing is performed by 1-wire digital thermometer DS18B20. Measurments are taken every min and displayed via tubes. 
ATmega8A is a main computing unit. It performs a connection of all device units together. It system clock source is 8MHz crystall resonator. Since all PWM pins were busy I decide to use ATtiny2313 to control color and brightness of RGB leds. Brightness is setting via potentiometer. So potential sensing is needed. As ATtiny2313 dont have internal ADC, we need an external ADC. I have a plenty of MCP3201 12-bit adc.

### Case
My workshop has been updated with a 3D printer. So to print a case of nixie clock is a great opportunity to test printer out. Modelling was performed at web CAD [OnShape](onshape.com). After a few tries, I made a good looking case for my nixie clock.

<p align="left">
<img src="img/onshape_case_assemble.gif" width="60%"></p>
<p align="right">
<img src="img/onshape_case_disassemble.gif" width="60%"></p>
### Let's test it out!

#### Time setting
#### Temperature display
#### Color changing







# Nixie-clock
## Description
<p align="center">
<img src="img/header_gif_small.gif" width="60%"></p>

A main feature of this kind of watches is a soft and warm glow of [nixie tubes](https://en.wikipedia.org/wiki/Nixie_tube). Nixie clocks are getting more and more popular nowadays. So I'll tell you about my nixie clock version.
### Feartures
* Time display (hh:mm) with the possibility of time setting via buttons.
* External temperature display. Showing on every minute for 3 seconds. Digital thermometer is 1-wire DS18b20.
* RGB backlight. Fixed colors changes via button on front panel. Brightness adjustment via potentiometer on back panel.
### Power
There are two ways of power supply designing: use of transformer or step-up converter. Transformer is a bulky solution. Also it's quite dangerous due to high voltage connector. So I decide to use a step-up converter based on popular MC34063 IC.
<p align="center">
<img src="img/power_supply.jpeg" width="60%"></p>
This is classic scheme of impulse converter. 

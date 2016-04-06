# bikesignal
bike signal with arduino

Arduino: SaintSmart UNO (yeah... I know)...
8x8 LED Matrix: 1588BS
Shift registers: 2x SN74HC595N
2 Buttons
Bunch of resistors

LED matrix has 2 rows of pins 
C for the matrix columns
R for the matrix rows

When matrix faced upside down,

top pins: 1R 4C 6C 4R 1C 2R 7C 8C

bottom pins: 3R 6R 5C 8R 3C 2C 7R 5R

Pins are connected to their respective shift register and bit i.e. 1R is on the row shift register, pin QA. 8C is on the column shift register, pin QH.

(refer to https://www.sparkfun.com/datasheets/IC/SN74HC595.pdf)

To light up a LED at coordinate (x, y), turn on the x pin and turn off the y pin i.e. To turn on LED (2,5), turn on 2R (pin QB on row SR) and 5C (QE on column SR)

With code supplied: 
- pressing the left button connected to arduino pin 2 will play a left arrow animation.
- pressing the right button connected to arduino pin 4 will play a right arrow animation.
- pressing both buttons will play the stop animation

TODO: connect a MPU-6050 accelerometer/gyroscope to play animations when at a certain angle.

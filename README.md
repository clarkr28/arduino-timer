# arduino-timer
Code for an Arduino timer using a 15-segment display

## Motivation

I wanted a timer that I could have on my desk at work.  I wanted to be able to set a timer for a certain number of minutes, and I wanted to be able to use it as a stopwatch.  When a timer expires, the LEDs do a little dance.  If the dial is rotated while the timer is running, the brightness of the LEDs are adjusted. 

## Display

A potientometer is used to set the number of minutes for the timer.  I didn't want to use the display as a standard number display.  Even though that would have been easy, I didn't want a display that would be flashing numbers in my face.  I wanted more of a progress bar.  Each digit in the display has 15 segments (15 little LEDs that can be individually turned on or off).  With 4 digits, we have 60 segments at our disposal, meaning we can show a 60 minute timer by turning on each segment and turning off one segment each minute.  I programmed the display to light up each segment in a spiraling pattern, both when counting up and counting down.  Below are some of the iterations that it took to get it right.  

First try - definitely wrong:

![buggy spiraling display](resources/wrong.gif)

Better, but doesn't spiral as well as it could:

![Better but doesn't spiral as well as it could](resources/kinda.gif)

Spiraling display:

![Spiraling display](resources/correct.gif)

And when a timer finishes, the display does a little dance!

![Spiraling display](resources/dance.gif)


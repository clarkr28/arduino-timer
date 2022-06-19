#include <Adafruit_DotStar.h>
#include "Adafruit_LEDBackpack.h"
#include <math.h>

#define NUMPIXELS 1
#define DATAPIN   7
#define CLOCKPIN  8
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

enum State { Waiting, Timing };

void setup() {
  // handle dotstar
  strip.begin();
  strip.show();
  // setup digit display
  alpha4.begin(0x70);
  alpha4.setBrightness(6);
  // setup button pin
  pinMode(4, INPUT_PULLDOWN);
}

void loop() {
  // put your main code here, to run repeatedly
  enum State state = Waiting;
  unsigned long startTime, timeDiff;
  int timeDiffSeconds, mins, hrs, dot;
  
  while(true) {
    switch(state) {
      case Waiting:
        if (digitalRead(4) == HIGH) {
          // switch to Timing
          startTime = millis();
          state = Timing;
        } else {
          alpha4.writeDigitAscii(0, '-');
          alpha4.writeDigitAscii(1, '-');
          alpha4.writeDigitAscii(2, '-');
          alpha4.writeDigitAscii(3, '-');
          alpha4.writeDisplay();
        }

        break;

      case Timing:
        timeDiff = millisCorrected(startTime) - startTime;
        timeDiffSeconds = floor(timeDiff / 1000);
        mins = floor(timeDiffSeconds / 60);
        mins = mins % 60;
        hrs = floor(timeDiffSeconds / (60 * 60)); 
        dot = (timeDiffSeconds % 60) >= 50;

        // seconds (zeros digit only)
        alpha4.writeDigitAscii(3, intToChar(timeDiffSeconds), dot);
        // minutes zeros digit
        alpha4.writeDigitAscii(2, intToChar(mins % 10));
        // minutes tens digit
        alpha4.writeDigitAscii(1, intToChar(floor(mins / 10)));
        // hours
        alpha4.writeDigitAscii(0, intToChar(hrs));
        alpha4.writeDisplay();

        if (mins == 59) {
          strip.setPixelColor(0, 0, 255, 255);
          strip.show();
        } else {
          strip.setPixelColor(0, 0, 0, 0);
          strip.show();
        }

        break;
    }
  }
}

// turns the int into a 0-9 char
static char intToChar(int number) {
  return (number % 10) + 48;
}

static unsigned long millisCorrected(unsigned long uStartTime) {
  long currTime,startTime; 
  double cf = 1566.052; // correction factor: ms to add per minute
  currTime = (long) millis();
  startTime = (long) uStartTime;
  
  if (startTime <= 0 || startTime > currTime) {
    return millis();
  }
  return (unsigned long) currTime + floor((( (double) currTime - startTime ) / 60000) * cf );
}

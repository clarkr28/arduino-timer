// 06/27 - add incrementing counter

#include <Adafruit_DotStar.h>
#include "Adafruit_LEDBackpack.h"
//#include <SPI.h> // apparantly don't use this for Trinket
#include <math.h>

#define NUMPIXELS 1
#define DATAPIN   7
#define CLOCKPIN  8
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

#define ANALOG_BUFFER_SIZE 8
struct AnalogBuffer {
  int loc;
  int buff[ANALOG_BUFFER_SIZE];
};

struct DisplayState {
  int digit[4];
  unsigned int duration;
};

static void updateDisplay(struct DisplayState *state) {
  for (int i=0; i < 4; i++) {
    alpha4.writeDigitRaw(i, state->digit[i]);
  }
  alpha4.writeDisplay();
}

int circleDanceLength = 6;
struct DisplayState circleDanceSequence[] = {
  { {0b000000000000001, 0b000000000000001, 
     0b000000000000001, 0b000000000000001}, 50 },
  { {0b000000000000010, 0b000000000000010, 
     0b000000000000010, 0b000000000000010}, 50 },
  { {0b000000000000100, 0b000000000000100, 
     0b000000000000100, 0b000000000000100}, 50 },
  { {0b000000000001000, 0b000000000001000, 
     0b000000000001000, 0b000000000001000}, 50 },
  { {0b000000000010000, 0b000000000010000, 
     0b000000000010000, 0b000000000010000}, 50 },
  { {0b000000000100000, 0b000000000100000, 
     0b000000000100000, 0b000000000100000}, 50 },
};

int figureEightDanceLength = 75;
struct DisplayState figureEightDanceSequence[] = {
  { {0b000000000000001, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000010, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000010000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000001000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000010000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000001000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000100, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000010000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000001000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000100000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 }, // end first loop
  { {0b000000000000001, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000001, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000010, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000010000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000001000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000010000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000001000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000100, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000010000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000001000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000100000, 
     0b000000000000000, 0b000000000000000}, 50 }, // end second loop
  { {0b000000000000000, 0b000000000000001, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000001, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000010, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000010000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000001000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000010000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000001000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000100, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000010000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000001000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000100000, 0b000000000000000}, 50 }, // end third loop
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000001, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000001}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000010}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000010000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000001000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000000010000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000000001000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000100}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000010000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000001000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000000100000}, 50 }, // end fourth loop
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000001}, 50 }, // 4 loop back
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000010}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000010000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000000, 0b000000001000000}, 50 },
  { {0b000000000000000, 0b000000000000000,        // 3 loop back
     0b000000010000000, 0b000000000000000}, 50 }, // 3 loop back
  { {0b000000000000000, 0b000000000000000, 
     0b000000001000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000100000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000001, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000010, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000010000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000001000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000010000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000001000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000000000100, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000010000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000000, 
     0b000000001000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000010000000,        // 2 loop back
     0b000000000000000, 0b000000000000000}, 50 }, 
  { {0b000000000000000, 0b000000001000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000100000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000001, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000010, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000010000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000001000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000010000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000001000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000000000100, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000010000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000000000, 0b000000001000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000010000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000001000000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
  { {0b000000000100000, 0b000000000000000, 
     0b000000000000000, 0b000000000000000}, 50 },
};



enum State { PickTime, Countdown, Paused, Dance, Countup };

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(1, INPUT_PULLDOWN);
  strip.begin();
  strip.show(); 
  alpha4.begin(0x70); 
  alpha4.setBrightness(2); 
  for (int i=0; i<=60; i++) {
    radialDisplay(i);
    delay(5);
  }
  for (int i=60; i>=0; i--) {
    radialDisplay(i);
    delay(5);
  }
}

void loop() {
  int dialInput, dialBase60, i, dialRemaining, dialSetPoint, brightness;
  int danceStateCount, stateTrip = 0;
  float dialPercent;
  long singleDigit = 0, startTime, finishTime, remainingTime, elapsedTime;
  unsigned long danceTimeStamp;
  struct AnalogBuffer analogBuffer;
  analogBuffer.loc = 0;
  for (int i = 0; i < ANALOG_BUFFER_SIZE; i++) {
    // initialize the buffer to empty
    analogBuffer.buff[i] = 0;
  }
  int danceLength = figureEightDanceLength;
  struct DisplayState *danceSequence = &figureEightDanceSequence[0]; 
  enum State state = PickTime;
 
  while(true) {
    dialInput = analogReadAvg(&analogBuffer);
    dialPercent = (float) (dialInput-4)  / (1023-10);
    dialBase60 = dialPercent * 60;
    digitalWrite(13, digitalRead(1) == HIGH);

    switch(state) {
      case PickTime:
        if (dialBase60 > 0 && digitalRead(4) == HIGH) {
          // switch to countdown
          dialSetPoint = dialBase60;
          startTime = (long) millis();
          finishTime = startTime + (1000 * dialBase60 * 60);
          stateTrip = 0;
          state = Countdown;
        } else {
          if (digitalRead(4) == HIGH) {
            stateTrip = 1;
          }
          if (stateTrip && digitalRead(4) == LOW) {
            stateTrip = 0;
            // switch to countup
            startTime = (long) millis();
            dialSetPoint = dialBase60;
            state = Countup;
          }
        }
        radialDisplay(dialBase60);
        break;
        
      case Countdown:
        // update timer and display
        remainingTime = finishTime - (long) millis();
        if (remainingTime > 0) {
          dialRemaining = ceil((float) dialSetPoint * remainingTime / (finishTime - startTime));
          radialDisplay(digitalRead(1) == LOW ? 0 : dialRemaining);
        } else {
          state = Dance;
          // initialize variables for next state
          danceStateCount = 0;
          danceTimeStamp = millis();
        }

        // update brightness
        if ( abs( ((float) dialSetPoint / 60) - dialPercent) > 0.02) {
          brightness = floor(dialPercent * 16);
          alpha4.setBrightness(brightness); 
        }
        break;
        
      case Dance:
        // stop dancing if button is pressed
        if (digitalRead(4) == HIGH) {
          stateTrip = 1;
        }
        if (stateTrip && digitalRead(4) == LOW) {
          state = PickTime;
          stateTrip = 0;
        }
        // update display count
        if (danceTimeStamp + danceSequence[danceStateCount].duration < millis()) {
          danceStateCount += 1;
          danceTimeStamp = millis();
          if (danceStateCount >= danceLength) {
            danceStateCount = 0;
          }
        }

        // update brightness
        if ( abs( ((float) dialSetPoint / 60) - dialPercent) > 0.02) {
          brightness = floor(dialPercent * 16);
          alpha4.setBrightness(brightness); 
        }

        // output display
        if (digitalRead(1) == HIGH) {
          updateDisplay(&danceSequence[danceStateCount]); 
        } else {
          radialDisplay(0);
        }
        break;

      case Countup:
        // stop counting if button is pressed
        if (digitalRead(4) == HIGH) {
          stateTrip = 1;
        }
        if (stateTrip && digitalRead(4) == LOW) {
          state = PickTime;
          stateTrip = 0;
        }

        // update display
        elapsedTime = ((long) millis()) - startTime;
        elapsedTime = elapsedTime / (1000 * 60);
        if (digitalRead(1) == HIGH) {
          radialDisplay((int) elapsedTime); 
        } else {
          radialDisplay(0);
        }

        // update brightness
        if ( abs( ((float) dialSetPoint / 60) - dialPercent) > 0.02) {
          brightness = floor(dialPercent * 16);
          alpha4.setBrightness(brightness); 
        }
        break;
        
    }
  }
}

static int analogReadAvg(struct AnalogBuffer *ab) {
  int total = 0;
  ab->buff[ab->loc] = analogRead(A3);
  ab->loc += 1;
  if (ab->loc >= ANALOG_BUFFER_SIZE) {
    ab->loc = 0;
  }
  for (int i=0; i < ANALOG_BUFFER_SIZE; i++) {
    total += ab->buff[i];
  }
  return ceil( (float) total / ANALOG_BUFFER_SIZE );
}

static void radialDisplay(int amount) {
  unsigned int digit;
  if (amount > 120) {
    amount = amount % 120;
  }
  if (amount <= 60) {
    // handle 0-60 (inclusive)
    for (int i = 0; i < 4; i++) {
      digit = 0;
      if (amount > 15) {
        digit = 0x7FFF;
      } else if (amount <= 0) {
        digit = 0;
      } else if (amount <= 6) {
        // handle 1-6
        digit = pow(2, amount) - 1;
      } else {
        // handle 7-15
        switch (amount) {
          case 7:
            digit = 0x023F; // add J
            break;
          case 8:
            digit = 0x063F; // add K 
            break;
          case 9:
            digit = 0x06BF; // add G2
            break;
          case 10:
            digit = 0x26BF; // add N
            break;
          case 11:
            digit = 0x36BF; // add M
            break;
          case 12:
            digit = 0x3EBF; // add L
            break;
          case 13:
            digit = 0x3EFF; // add G1
            break;
          case 14:
            digit = 0x3FFF; // add H
            break;
          default:
            digit = 0x7FFF; // add DP
        }
      }
      alpha4.writeDigitRaw(i, digit);
      amount -= 15;
    }
  } else {
    // handle amounts greater than 60
    amount -= 60;
    for (int i = 0; i < 4; i++) {
      digit = 0x7FFF;
      switch (amount) {
        case 1:
          digit ^= 0x0001; // A
          break;
        case 2:
          digit ^= 0x0002; // B
          break;
        case 3:
          digit ^= 0x0004; // C
          break;
        case 4:
          digit ^= 0x0008; // D
          break;
        case 5:
          digit ^= 0x0010; // E
          break;
        case 6:
          digit ^= 0x0020; // F
          break;
        case 7:
          digit ^= 0x0200; // I
          break;
        case 8:
          digit ^= 0x0400; // J
          break;
        case 9:
          digit ^= 0x0080; // G2
          break;
        case 10:
          digit ^= 0x2000; // M
          break;
        case 11:
          digit ^= 0x1000; // L
          break;
        case 12:
          digit ^= 0x0800; // K
          break;
        case 13:
          digit ^= 0x0040; // G1
          break;
        case 14:
          digit ^= 0x0100; // H
          break;
        case 15:
          digit ^= 0x4000; // N
          break;
      }
      alpha4.writeDigitRaw(i, digit);
      amount -= 15;
    }
  }
  alpha4.writeDisplay();
}

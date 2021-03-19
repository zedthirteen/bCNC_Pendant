// bCNC Pendant
// https://github.com/mprochnow/CNC-Engraver
// Original author: Martin J. Prochnow <email@martin-prochnow.de>
// Modifed by: D Field - add 4th axis, movement multipliers and LED
// License: CC BY-SA 4.0 (Attribution-ShareAlike 4.0 International, http://creativecommons.org/licenses/by-sa/4.0/)

//


#include <Keyboard.h>

// Leonardo pins
#define pinA  2         // grn
#define pinB  3         // wht

#define pinX  4         // yel
#define pinY  5         // yel/blk
#define pinZ  6         // brn
#define pin4  7         // brn/blk

#define pinX1   8       // gry
#define pinX10  9       // gry/blk
#define pinX100 10      // ora

// Comment out next line for Pro Micro
//#define LEONARDO

#ifdef LEONARDO
  #define pinLED 11
#else
  #define pinLED  14
#endif

#define debounceThreshold  100 // microseconds

volatile unsigned long debounceLast = 0;
volatile char step = 0;

volatile char stepRate = 0x00; // need to ensure step units are set before use

void setup() 
{
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  pinMode(pinX, INPUT_PULLUP);
  pinMode(pinY, INPUT_PULLUP);
  pinMode(pinZ, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pinX1, INPUT_PULLUP);
  pinMode(pinX10, INPUT_PULLUP);
  pinMode(pinX100, INPUT_PULLUP);
  
  pinMode(pinLED, OUTPUT);


  attachInterrupt(1, readEncoder, RISING);

  stepRate = 0x00; // not configured yet

  Keyboard.begin();
}

void loop() {

  static char currentStepRate = 0x00;

  // get the current step rate - perhaps dont need to do this every time?
  if(digitalRead(pinX1) == LOW)
  {
    currentStepRate = '1';
  }
  else if (digitalRead(pinX10) == LOW)
  {
    currentStepRate = '2';
  }
  else if(digitalRead(pinX100) == LOW)
  {
    currentStepRate = '3';
  }

  // Send the step rate if it has changed or not yet been set
  if((stepRate == 0x00) || (stepRate != currentStepRate))
  {
    Keyboard.press(currentStepRate);
    Keyboard.release(currentStepRate);
    stepRate = currentStepRate;
  }
  digitalWrite(pinLED, HIGH);
  if (step == -1) 
  {
    digitalWrite(pinLED, LOW);
    if (digitalRead(pinX) == LOW) 
    {
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.release(KEY_LEFT_ARROW);
    } 
    else if (digitalRead(pinY) == LOW) 
    {
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.release(KEY_DOWN_ARROW);
    } 
    else if (digitalRead(pinZ) == LOW) 
    {
      Keyboard.press(KEY_PAGE_DOWN);
      Keyboard.release(KEY_PAGE_DOWN);
    }

    step = 0;
    digitalWrite(pinLED, HIGH);
  } 
  else if (step == 1) 
  {
    digitalWrite(pinLED, LOW);
    if (digitalRead(pinX) == LOW) 
    {
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.release(KEY_RIGHT_ARROW);
    } 
    else if (digitalRead(pinY) == LOW) 
    {
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.release(KEY_UP_ARROW);
    } 
    else if (digitalRead(pinZ) == LOW) 
    {
      Keyboard.press(KEY_PAGE_UP);
      Keyboard.release(KEY_PAGE_UP);
    }
    step = 0;
    digitalWrite(pinLED, HIGH);
  }
}

void readEncoder() 
{
  if (micros() - debounceLast > debounceThreshold) 
  {
    debounceLast = micros();

    if (PIND & B00000010) 
    {
      if (PIND & B00000001) 
      {
        step = -1; // CCW
      }
      else 
      {
        step = 1; // CW
      }
    }
  }
}

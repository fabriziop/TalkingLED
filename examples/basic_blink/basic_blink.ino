/* .+

.context    : Talking LED library
.title      : basic example
.kind       : c++ source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Torino - Italy
.creation   : 15-12-2018
.copyright  : (c) 2018 Fabrizio Pollastri

.description

description
  Blink LED with two different sequences alternating each other.
  
.- */


#include <Arduino.h>

#include <TalkingLED.h>
TalkingLED TLED;

// LED blink sequences A and B (final zero is sequence terminator)
// A: on for 500 ms, off for 500 ms, blink @1Hz with 50% duty cycle.
uint16_t aSequence[3] = {500,500,0};
// B: on for 250 ms, off for 250 ms, twice.
uint16_t bSequence[7] = {250,250,250,250,0};


void setup() {

  // init Talking LED
  TLED.begin();

}


void loop() {

  // display 3 time sequence A
  TLED.sequence(aSequence);
  TLED.delay(2900);

  // display 2 time sequence B
  TLED.sequence(bSequence);
  TLED.delay(1900);

}

//// END

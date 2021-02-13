/* .+

.context    : Talking LED library
.title      : basic repeater example
.kind       : c++ source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Torino - Italy
.creation   : 13-Feb-2021
.copyright  : (c) 2021 Fabrizio Pollastri

.description
  Same example as basic_blink with repeater.
  Blink LED with two different sequences alternating each other.
  Blink also the repeater: LED signal is sent also to an output pin
  defined by the user, in this case pin #2. and repeater inversion is
  not requested (default).
  
.- */


#include <Arduino.h>

#include <TalkingLED.h>
TalkingLED TLED;

#define REPEATER_PIN 2

// LED blink sequences A and B (final zero is sequence terminator)
// A: on for 500 ms, off for 500 ms, blink @1Hz with 50% duty cycle.
uint16_t sequenceA[3] = {500,500,0};
// B: on for 250 ms, off for 250 ms, twice.
uint16_t sequenceB[5] = {250,250,250,250,0};


void setup() {

  // init Talking LED
  TLED.begin(LED_PIN,REPEATER_PIN);

}


void loop() {

  // display 3 time sequence A
  TLED.setSequence(sequenceA);
  TLED.delay(2900);

  // display 2 time sequence B
  TLED.setSequence(sequenceB);
  TLED.delay(1900);

}

/**** END ****/

/* .+

.context    : Talking LED library
.title      : message showcase example
.kind       : c++ source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Torino - Italy
.creation   : 20-12-2018
.copyright  : (c) 2018 Fabrizio Pollastri

.description

description
  Blink LED sequentially with all message sequences from code 1 to 19.
  
.- */


#include <Arduino.h>

#include <TalkingLED.h>
TalkingLED TLED;


void setup() {

  // init Talking LED
  TLED.begin();

}


void loop() {

  for (int m=1; m <= TLED_MESSAGE_CODE_MAX; m++) {
    TLED.message(m);
    TLED.waitEnd();
  }
}

//// END

/* .+

.context    : Talking LED library
.title      : byte display example
.kind       : c++ source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Torino - Italy
.creation   : 23-Mar-2020
.copyright  : (c) 2020 Fabrizio Pollastri

.description

  Blink LED to display sequentially all binary codes of one byte from code
  0x00 to 0xff .
  
.- */


#include <Arduino.h>

#include <TalkingLED.h>
TalkingLED TLED;


void setup() {

  // init Talking LED
  TLED.begin();

}


void loop() {

  for (int m=0; m < 256; m++) {
    TLED.setMessage(m,TLED_BYTE);
    TLED.waitEnd();
  }
}

/**** END ****/

/* .+

.context    : Talking LED library
.title      : nibble display example
.kind       : c++ source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Torino - Italy
.creation   : 27-Mar-2020
.copyright  : (c) 2020 Fabrizio Pollastri
.license    : GNU Lesser General Public License

.description

  Blink LED to display sequentially all binary codes of one nibble from code
  0x0 to 0xf .
  
.- */


#include <Arduino.h>

#include <TalkingLED.h>
TalkingLED TLED;


void setup() {

  // init Talking LED
  TLED.begin();

}


void loop() {

  for (int m=0; m < 16; m++) {
    TLED.setMessage(m);
    TLED.waitEnd();
  }
}

/**** END ****/

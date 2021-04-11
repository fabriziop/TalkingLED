/* .+

.context    : Talking LED library
.title      : morse display example
.kind       : c++ source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Torino - Italy
.creation   : 20-Dec-2018
.copyright  : (c) 2018 Fabrizio Pollastri
.license    : GNU Lesser General Public License

.description

  Blink LED sequentially with all morse-like encoding from code 1 to 19.
  
.- */


#include <Arduino.h>

#include <TalkingLED.h>
TalkingLED TLED;


void setup() {

  // init Talking LED
  TLED.begin();

}


void loop() {

  for (int m=1; m <= TLED_MORSE_CODE_MAX; m++) {
    TLED.setMessage(m,TLED_MORSE);
    TLED.waitEnd();
  }
}

/**** END ****/

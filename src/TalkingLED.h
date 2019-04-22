/* .+

.context    : Arduino Utility Libraries
.title      : Talking LED Library
.kind       : c++ include
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Revello - Italy
.creation   : 3-12-2018
.copyright  : (c) 2018 Fabrizio Pollastri

.- */


#ifndef TALKING_LED_H
#define TALKING_LED_H

#include "Arduino.h"

#define TLED_ON LOW
#define TLED_OFF HIGH

#define TLED_MESSAGE_CODE_MAX 19
#define TLED_LONG_BLINK_UNITS 4
#define TLED_LONG_BLINK_ON_TIME 600
#define TLED_LONG_BLINK_OFF_TIME 400
#define TLED_SHORT_BLINK_ON_TIME 200
#define TLED_SHORT_BLINK_OFF_TIME 200
#define TLED_MESSAGE_END_OFF_TIME 1000
#define TLED_DELAY_STEP 20


class TalkingLED {

 public:
  TalkingLED(void);
  boolean begin(uint8_t aLEDPin);
  boolean update(void);
  void delay(uint32_t aDelay);
  void set(uint8_t aLEDStatus);
  void waitEnd(void);
  boolean message(uint8_t aMessagedCode);
  boolean sequence(uint16_t *aSequence);
  void on(void);
  void off(void);

 private:
   uint8_t LEDPin;
   uint8_t LEDStatus;
   uint16_t messageSequence[28] =
     {50,50,50,50,50,500,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   uint8_t messageCode;
   uint8_t messageCodeCurrent;
   uint8_t i, j;
   uint16_t *sequence_;
   uint16_t *sequenceCurrent;
   uint32_t now;
   uint32_t nextChange;
   uint32_t delayEnd;
   boolean sequenceEnd;
   boolean _build_message_sequence(uint8_t aMessageCode);
};

#endif //  TALKING_LED_H

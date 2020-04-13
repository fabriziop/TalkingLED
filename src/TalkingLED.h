/* .+

.context    : Arduino Utility Libraries
.title      : Talking LED Library
.kind       : c++ include
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Revello - Italy
.creation   : 3-Dec-2018
.copyright  : (c) 2018 Fabrizio Pollastri

.- */


#ifndef TALKING_LED_H
#define TALKING_LED_H

#include <Arduino.h>

#ifdef __AVR__
  #define TLED_ON HIGH
  #define TLED_OFF LOW
  #define LED_PIN 13
#elif ESP8266
  #define TLED_ON LOW
  #define TLED_OFF HIGH
  #define LED_PIN 2
#else
  #error TalkingLED: unsupported processor.
#endif

#define TLED_MORSE_CODE_MAX 19
#define TLED_LONG_BLINK_UNITS 4
#define TLED_LONG_BLINK_ON_TIME 600
#define TLED_LONG_BLINK_OFF_TIME 400
#define TLED_SHORT_BLINK_ON_TIME 200
#define TLED_SHORT_BLINK_OFF_TIME 200
#define TLED_NIBBLE_OFF_TIME 600
#define TLED_MESSAGE_END_OFF_TIME 1000
#define TLED_DELAY_STEP 20

enum TalkingLEDMessageType {
  TLED_MORSE,
  TLED_BYTE,
  TLED_NIBBLE,
};


class TalkingLED {

 public:
  TalkingLED(void);
  bool begin();
  bool begin(uint8_t aLEDPin);
  bool update(void);
  void delay(uint32_t aDelay);
  void setLED(uint8_t aLEDStatus);
  bool isEnd(void);
  void waitEnd(void);
  bool setMessage(uint8_t aMessagedCode,
    enum TalkingLEDMessageType aMessageType = TLED_NIBBLE);
  bool setSequence(uint16_t *aSequence);
  void on(void);
  void off(void);

 private:
   uint8_t LEDPin;
   uint8_t LEDStatus;
   uint16_t messageSequence[28] =
     {50,50,50,50,50,500,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   uint8_t messageCodeNext;
   enum TalkingLEDMessageType messageTypeNext;
   uint8_t messageCodeCurrent;
   enum TalkingLEDMessageType messageTypeCurrent;
   uint16_t *sequenceNext;
   uint16_t *sequenceCurrent;
   uint16_t *sequence;
   uint32_t now;
   uint32_t changeTime;
   uint32_t delayEnd;
   bool sequenceEnd;
   bool _build_message_sequence();
};

#endif // TALKING_LED_H

/**** END ****/

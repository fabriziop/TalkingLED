==========================
TalkingLED Arduino Library
==========================

TalkingLED, LED blinking made easy.

TalkingLED allows to decouple blinking timings from application timings,
making application flow structure simpler.

LED blinking is the esiest way for an Arduino board to communicate. Status
codes, error codes, numbers, binary patterns can be displayed by realizing
more or less complex on/off timings. This on/off timings need to be implemented
by the application running on the Arduino board. Generally, LED blinking happens
for the most part of application run time: for example, to signal a normal
run condition. This means that LED blinking operations are tightly interleaved
with the application execution flow and timing, making it more complex.
TalkingLED can be used to reduce this complexity.


Features
========

* Data defined blink sequences
* Simple cooperative application/TalkingLED interaction model
* Small numbers (<20) morse-like encoding with intuitive blink sequences 
* Binary encoding with simple blink sequences for bytes and nibbles 
* No multithread needed
* No interrupts needed
* No external dependencies


Quick start
===========

Here is a typical structure of an Arduino application using TalkingLED.
The are three parts: TalkingLED init, blink sequence definition and blink
running.

.. code:: cpp

  // application code
  ...

  // instantiate the TalikingLED object TLED
  #include <TalkingLED.h>
  TalkingLED TLED;

  // define a LED blink sequence (zero is sequence terminator)
  // blink on for 500 ms, off for 500 ms, blink @1Hz with 50% duty cycle.
  uint16_t blinkSequence[3] = {500,500,0};

  // application code
  ...


  void setup() {

    // application code
    ...

    // init TalkingLED
    TLED.begin();
    TLED.setSequence(blinkSequence);

    // application code
    ...

  }


  void loop() {

    // application code
    ... 

    // somewhere in the application loop call TalkingLED update method.
    // The call frequency determines the precision of blink timing.
    // In this example, the blink sequence is 500 ms on and 500 ms off, so a 
    // call period of about 100 ms can be sufficient.
    TLED.update();

    // application code
    ... 

  }


| Frequently, applications need to perform a fixed time delay. This can be
  exploited with TalkingLED using its own delay method. TalkingLED delay
  method allows to perform both the requested delay and to update
  the LED blink status at the same time.
| The update method is called internally by delay method with a frequency
  defined by TLED_DELAY_STEP constant. So, the delay period amplitude
  do not influence the LED update frequency.

.. code:: cpp


  void loop() {

    // application code
    ... 

    // for example, if the applcation needs a delay of 1000 ms,
    // it can be implemented by a call to TalkingLED delay method.
    // This performs both the requested delay and update the LED blink
    // status at the same time.
    TLED.delay(1000);

    // application code
    ... 

  }


Blink sequence definition
=========================

Blink sequences are defined by arrays of unsigned 16 bits integers.
Each array element sets the period in milliseconds of a LED status.
Even index array elements sets the periods of LED on statuses, odd index
array elements set the periods of LED off statuses. The last element array
must be set to zero as sequence terminator. Since sequence elements are
unsigned 16 bits integers and zero value is used as terminator, the
allowable period value range from 1 to 65535 milliseconds. The status
sequence is applied to LED from first to last element cyclically, until
a new sequence is defined (calls to methods setSequence, setMessage) or
some TalkingLED methods (setLED) that stop the blink cycle are called.

.. code:: cpp

  // examples of blink sequence definitions

  // blink at 1 Hz with 50% duty cycle
  //                              on  off
  uint16_t example1Sequence[3] = {500,500,0};

  // on pulse train from 100 ms to 500 ms duration with 500 ms off separation
  //                               on  off on  off on  off on  off on  off
  uint16_t example2Sequence[11] = {100,500,200,500,300,500,400,500,500,500,0};


TalkingLED encoding
===================

TalkingLED has a builtin encoding capability using blink sequences computed
from given code number or from given binary data. Different types of
encoding are available: a morse-like encoding and a binary nibble or binary
byte encoding.


Morse-like encoding
-------------------

The morse-like encoding is able to display a message code
in the range 1 - 19. Each code is rendered by a blink sequence starting
with 3 very short LED on pulses (100 ms), followed by the message code
displayed with long (600 ms) and short (200 ms) on pulses and terminated
by 1 second LED off pause.
The message code is converted to long and short LED on pulses with the
following rules. Each short pulse correspond to 1 unit. Each long pulse
correspends to 4 units. The message code is the sum of all pulse units.
Long pulses are given first. The timing of the encoding scheme is selected
to be easily decoded by an unskilled human.

==== ==========================================
Encoding scheme: message code vs blink sequence
-----------------------------------------------
code blink sequence, on pulses
==== ==========================================
1    short
2    short short
3    short short short
4    long
5    long short
6    long short short
7    long short short short
8    long long
...        ...
18   long long long long short short
19   long long long long short short short
==== ==========================================


Binary byte encoding
--------------------

This type of encoding displays the content of a byte in binary form.
The byte content is rendered by a blink sequence starting with 3 short LED
pulses (100 ms), followed by 8 LED pulses, one for each bit: a long pulse
(600 ms) for one bits, a short pulse (200 ms) for zero bits. The sequence of
bit pulses goes from the most significant bit to the least significant bit.
Between the first 4 pulses and the last 4, there is a 600 ms interval.

========= ================================================
Encoding scheme: byte vs blink sequence
----------------------------------------------------------
byte      blink sequence, on pulses
========= ================================================
0000 0000 short short short short  short short short short
0000 0001 short short short short  short short short long
0000 0010 short short short short  short short long  short
   ...                          ...
1111 1110 long  long  long  long   long  long  long  short     
1111 1111 long  long  long  long   long  long  long  long     
========= ================================================


Binary nibble encoding
----------------------

This type of encoding displays the content of a nibble (4 bits) in binary form.
The encoding scheme is the same given for the binary byte, but only the 4
least significant bits of the byte are displayed.


Module reference
================

TalkingLED is implemented as a C++ class. A TalkingLED object needs to be
instantiated and associated to the LED to be blinked. This object has a
set of methods for managing the LED blink sequences.


Objects and methods
-------------------

**TalkingLED**

  This class embeds all LED blink status info.


bool **begin(** uint8_t **LEDPin)**

  This method sets the board pin connected to the LED to be blinked.

  **LEDPin**: number of pin connected to LED.

  Returns **true**.


bool **setMessage(** uint8_t **aMessageCode**,
enum TalkingLEDMessageType **aMessageType** = TLED_NIBBLE);

  This method sets the message code and the encoding type to be displayed.

  **aMessageCode**: message code number. If encoding type is TLED_MORSE,
  must be a number in the range 1-19. If encoding type is TLED_BYTE, the
  whole byte is encoded. If encoding type is TLED_NIBBLE, the 4 least
  significant bits are encoded.

  **aMessageType**: message encoding type, can be one of TLED_MORSE,
  TLED_BYTE, TLED_NIBBLE (default TLED_NIBBLE).

  Returns **false** when **aMessageCode** > 19 and **aMessageType** ==
  TLED_MORSE, or when **aMessageType** is not one of TLED_MORSE, TLED_BYTE,
  TLED_NIBBLE.
  Returns **true** otherwise.
 

bool **setSequence(** uint16_t * **aSequence)**

  This method sets the blink sequence to be displayed.

  **aSequence**: a pointer to the blink sequence array.

  Returns true.
 

bool **update(** void **)**

  This method updates the LED status (on or off) according to the current
  blink sequence/message.

  Returns **true** when LED status is changed.
  Returns **false** when LED status is not changed.


bool **isEnd(** void **)**

  This method checks for the end of the current cycle of the current
  sequence/message.

  Returns **true** if the current sequence/message cycle is terminated,
  otherwise returns **false**.


void **waitEnd(** void **)**

  This method waits until the end of the current cycle of the current
  sequence/message.


void **delay(** uint32_t **aDelay)**

  This method waits for the specified delay while calling frequently the
  update method.

  **aDelay**: wait delay in milliseconds.


void **setLED(** uint8_t **aLEDStatus)**

  This method force the LED to the given status. The current
  sequence/message cycle, if any, is immediately stopped.

  **aLEDStatus**: LED status to be forced: TLED_OFF for off, TLED_ON for on.


Examples
========

See the "examples" directory.


Installing
==========

By arduino IDE library manager or by unzipping TalkingLED.zip into
arduino libraries.


Contributing
============

Send wishes, comments, patches, etc. to mxgbot_a_t_gmail.com .


Copyright
=========

TalkingLED is authored by Fabrizio Pollastri <mxgbot_a_t_gmail.com>,
years 2018-2020, under the GNU Lesser General Public License version 3.

.. ==== END

==========================
TalkingLED Arduino Library
==========================

TalkingLED, LED blinking made easy.

TalkingLED allows to decouple blinking timings from application timings,
making application flow structure simpler.

LED blinking is the esiest way for an Arduino board to communicate. Several
messages can be sent by realizing more or less complex on/off timings. The
on/off timings need to be implemented by the application running on Arduino
board. Generally, LED blinking happens for the most part of application run
time: for example, to signal a normal run condition. This means that LED
blinking operation are tightly interleaved with application execution flow
and timing, making it more complex. TalkingLED can be used to reduce this
complexity.


Features
========

* Data defined blink sequences
* Simple cooperative application/TalkingLED interaction model
* Builtin encoded messaging with intuitive blink sequences 
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

  // define LED pin number 
  //#define LED_PIN 13    // on board LED for arduinos
  //#define LED_PIN 2    // on board LED for ESP8266 nodeMCU

  // define a LED blink sequence (zero is sequence terminator)
  // blink on for 500 ms, off for 500 ms, blink @1Hz with 50% duty cycle.
  uint16_t blinkSequence[3] = {500,500,0};

  // application code
  ...


  void setup() {

    // application code
    ...

    // init TalkingLED
    TLED.begin(LED_PIN);
    TLED.sequence(blinkSequence);

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
Even index array elements sets LED on statuses, odd index array elements
set LED off statuses. The last element array must be set to zero as
sequence terminator. Since sequence elements are unsigned 16 bits integers and
zero value is used as terminator, the allowable period value range from 1 to
65535 milliseconds. The status sequence is applied to LED
from first to last element cyclically, until a new sequence is defined (call
to methods sequence, message) or some TalkingLED methods (set, waitEnd)
that stop the blink cycle are called.

.. code:: cpp

  // examples of blink sequence definitions

  // blink at 1 Hz with 50% duty cycle
  //                              on  off
  uint16_t example1Sequence[3] = {500,500,0};

  // on pulse train from 100 ms to 500 ms duration with 500 ms off separation
  //                               on  off on  off on  off on  off on  off
  uint16_t example2Sequence[11] = {100,500,200,500,300,500,400,500,500,500,0};


TalkingLED message code
=======================

TalkingLED has a builtin messaging capability that display a message code
in the range 1 - 19. Each code is rendered by a blink sequence starting
with 3 very short LED on pulses (100 ms), followed by the message code
displayed with long (600 ms) and short (200 ms) on pulses and terminated
by 1 second LED off pause.
The message code is converted to long and short LED on pulses with the
following rules. Each short pulse correspond to 1 unit. Each long pulse
correspends to 4 units. The message code is the sum of all pulse units.
Long pulses are given first. The timing of the encoding scheme is selected
to be easily decoded by an unskilled human.

==== =====================================
Encoding scheme: message code vs blink sequence
------------------------------------------
code blink sequence, on pulses
==== =====================================
1    short
2    short short
3    short short short
4    long
5    long short
6    long short short
7    long short short short
8    long long
...  ...
18   long long long long short short
19   long long long long short short short
==== =====================================


Module reference
================

TalkingLED is implemented as C++ class. A TalkingLED object needs to be
instantiated and associated to the LED to be blinked. This object has a
set of methods for managing the LED blink sequences.

Objects and methods
-------------------

**TalkingLED**

  This class embeds all LED blink status info.


boolean **begin(** uint8_t **LEDPin)**

  This method sets the board pin connected to LED to be blinked.

  **LEDPin**: number of pin connected to LED.


boolean **message(** uint8_t **aMessageCode)**

  This method sets the message code (range 1-19) to be displayed.

  **aMessageCode**: message code number.
 

boolean **sequence(** uint16_t * **aSequence)**

  This method sets the blink sequence to be displayed.

  **aSequence**: a pointer to the blink sequence array.
 

boolean **update(** void **)**

  This method update the LED status (on or off) according to the current
  blink sequence/message.


void **waitEnd(** void **)**

  This method waits until the end of the current cycle of the current
  sequence/message.


void **delay(** uint32_t **aDelay)**

  This method waits for the specified delay while calling frequently the
  update method.

  **aDelay**: wait delay in milliseconds.


void **set(** uint8_t **aLEDStatus)**

  This method force the LED to the given status. The current
  sequence/message cycle, if any, is immediately stopped.

  **aLEDStatus**: LED status to be forced: 0 off, 1 on.


Examples
========

See the "examples" directory.


Installing
==========

By arduino IDE library manager or by unzipping TalkingLED.zip into
arduino libraries.


Contributing
============

Send wishes, comments, patches, etc. to f.pollastri_a_t_inrim.it .


Change Log
==========

commit 9c9a855e8de14c3bd63fa8efdbb393ff2e761a79
Author: Fabrizio Pollastri <mxgbot@gmail.com>
Date:   Tue Apr 23 00:35:03 2019 +0200

    Fix a missing close brace into 'message_showcase' example.

commit 60d3f4c4717416ba8133b12c125bbe9c96c2f923
Author: Fabrizio Pollastri <mxgbot@gmail.com>
Date:   Mon Apr 22 19:50:53 2019 +0200

    Fix 'set' function: type typo and missing prototype.

commit 8298e04cc3a5e7eae5ff73af7171bb542c7207ba
Author: Fabrizio Pollastri <mxgbot@gmail.com>
Date:   Sun Jan 13 00:38:56 2019 +0100

    First release.


Copyright
=========

TalkingLED is authored by Fabrizio Pollastri <f.pollastri_a_t_inrim.it>, year 2018, under the GNU General Public License version 3.

.. ==== END

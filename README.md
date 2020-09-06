# simon-arduino
*Simon game with some electronics components and Arduino*

# Intro

This is a simple project implementing [Simon game](https://en.wikipedia.org/wiki/Simon_(game)) on Arduino with a user interface based on a prototyping printed circuit board (PCB).

# User interface

## Wiring diagram

![PCB board](pcb.jpg)

Draw.io source : [Simon_PCB.drawio](Simon_PCB.drawio)

## Explain

We use 5 LEDs/buttons for user's inputs. White LED/button is used to start/stop the game. The other LEDs show the sequence to the user and are lighted when user press the corresponding button. The LEDs states changes are done with Arduino ouputs and the buttons states is read through digitals inputs. So understand that the buttons controls the LEDs through the program. An analog output send a PWM signal to the passive buzzer. A note is associated with each LED color.

Digitals inputs are wired with a 10kΩ pull-down resistor.

## Components

LEDS :
- 1 x Green
- 1 x Red
- 1 x Yellow
- 1 x Blue
- 1 x White

Resistors :
- 5 x 330Ω
- 5 x 100Ω
- 5 x 10kΩ

Others :
- 1 x passive buzzer
- 5 x push switch
- 13 x male pin header

## PCB

Top :

![Board top](board_top.jpg)

Bottom :

![Board bottom](board_bottom.jpg)

and Arduino/PCB wiring :

![Arduino wiring](arduino_wiring.jpg)

# Program

To catch user inputs we need interrupts, but the physical interrupts are limited on Arduino. For my Uno board there is only 2 physicals interrupts available, on PIN 2 and 3.

Softwares interrupts can enhanced Arduino capacity. In this project we use [PinChangeInterrupt library](https://www.arduino.cc/reference/en/libraries/pinchangeinterrupt/).

```C++
#include <PinChangeInterrupt.h>
```

The first 125 lines defines all the constants (notes, pin numbers, ...) and variables.

In setup() function as usual we found the pin mode setup. It's here we also attach interrupts to inputs (buttons) states changes :

```C++
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(green_input), green_button_change, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(red_input), red_button_change, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(yellow_input), yellow_button_change, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(blue_input), blue_button_change, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(white_input), white_button_change, CHANGE);
```

Each interrupt is linked with a function which is called when the input state changes :

```C++
void green_button_change() {
  green_state = !green_state;
  digitalWrite(green_output, green_state);
  if (green_state == HIGH) {
    last_input = GREEN;
  }
}
```

At the beginning of party (when white button is pressed), the rdn array is filled with random numbers between 1 and 4 (inclusive).

Then the code alternate two phases (while user do not mistakes) :
- Play sequence to user up to score value.
- Read user inputs and compare to sequence (adding 1 to score when end of sequence is reached).

If user input wrong color, game_over is set to 0 (true) and score to 100 (used to break while condition) :

```C+
if ( last_input == rdn[i] ) {
        i++;
      } else {
        game_over = 1;
        i = 100; // Exit while
      }
```

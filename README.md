# simon-arduino
Simon game with some electronics components and Arduino

This is a simple project implementing [Simon game](https://en.wikipedia.org/wiki/Simon_(game)) on Arduino with a user interface based on a prototyping printed circuit board (PCB).

# User interface

## Wiring

![PCB board](pcb.jpg)

We use 5 LEDs/buttons for user's inputs. White LED/button is used to start/stop the game. The other LEDs show the sequence to the user and are lighted when user press the corresponding button. The LEDs states changes are done with Arduino ouputs and the buttons states is read through digitals inputs. So understand that the buttons controls the LEDs through the program. An analog output send a PWM signal to the passive buzzer. A note is associated with each LED color.

Digitals inputs are wired with a 10kΩ pull-down resistor.

## PCB

Top :

![Board top](board_top.jpg)

Bottom :

![Board bottom](board_bottom.jpg)

and Arduino/PCB wiring :

![Arduino wiring](arduino_wiring.jpg)

# Program




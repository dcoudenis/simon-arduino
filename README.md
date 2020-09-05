# simon-arduino
Simon game with some electronics components and Arduino

This is a simple project implementing [Simon game](https://en.wikipedia.org/wiki/Simon_(game)) on Arduino with a human interface based on prototyping printed circuit board.

Wiring diagram :

![PCB board](pcb.jpg)

We will use 5 LEDs/buttons for user's inputs. White LED/button is used to start/stop the game. The other LEDs show the sequence to the user and are lighted when user press the corresponding button. The LED state changes is done with an Arduino ouput and the button state is read with a digital input. So understand that the buttons controls the LED through the program. An analog output send a PWM signal to the passive buzzer. A note is associated with each LED color.

Pictures of physical board :

Top :

![Board top](board_top.jpg)

Bottom :

![Board bottom](board_bottom.jpg)

and Arduino/PCB wiring :

![Arduino wiring](arduino_wiring.jpg)


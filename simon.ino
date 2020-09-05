#include <PinChangeInterrupt.h>

// Notes frequencies
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Pin numbers
const int buzzer = 3;
const int green_output =  4;
const int red_output =  5;
const int yellow_output =  6;
const int blue_output =  7;
const int white_output =  8;
const int green_input =  9;
const int red_input =  10;
const int yellow_input =  11;
const int blue_input =  12;
const int white_input =  13;

// Colors ids
const int GREEN = 1;
const int RED = 2;
const int YELLOW = 3;
const int BLUE = 4;
const int WHITE = 0;

// Notes to play
const int GREEN_NOTE = NOTE_C4;
const int RED_NOTE = NOTE_D4;
const int YELLOW_NOTE = NOTE_E4;
const int BLUE_NOTE = NOTE_F4;

// Variables
volatile byte green_state = LOW;
volatile byte red_state = LOW;
volatile byte yellow_state = LOW;
volatile byte blue_state = LOW;
volatile byte white_state = LOW;
volatile int last_input = -1;

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.write("Program launched...\n");
  pinMode(buzzer, OUTPUT);
  pinMode(green_output, OUTPUT);
  pinMode(red_output, OUTPUT);
  pinMode(yellow_output, OUTPUT);
  pinMode(blue_output, OUTPUT);
  pinMode(white_output, OUTPUT);
  pinMode(green_input, INPUT_PULLUP);
  pinMode(red_input, INPUT_PULLUP);
  pinMode(yellow_input, INPUT_PULLUP);
  pinMode(blue_input, INPUT_PULLUP);
  pinMode(white_input, INPUT_PULLUP);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(green_input), green_button_change, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(red_input), red_button_change, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(yellow_input), yellow_button_change, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(blue_input), blue_button_change, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(white_input), white_button_change, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rdn[99];
  int i, score;
  int game_over = 0;
  
  last_input = -1;
  
  Serial.write("Waiting to start game...\n");
  randomSeed(analogRead(0));
  while(last_input != WHITE) {
      delay(10);
  }
  Serial.write("Yeah, starting !!!\n"); // Starting new party
  // Party init
  // Random numbers in rdn array
  i = 0;
  while ( i < 99 ) {
    rdn[i] = random(1, 4 + 1); // because max is exclusive
    //Serial.println(rdn[i]);
    i++;
  }
  tone(buzzer, GREEN_NOTE, 100);
  delay(100);
  tone(buzzer, RED_NOTE, 100);
  delay(100);
  tone(buzzer, YELLOW_NOTE, 100);
  delay(100);
  tone(buzzer, BLUE_NOTE, 100);
  delay(1000);
  
  last_input = -1;
  score = 0;
  while(!game_over) {
    // Play sequence
    Serial.print("> ");
    i = 0;
    while ( i < score + 1) {
      switch(rdn[i]) {
        case GREEN:
          Serial.print("Green ");
          digitalWrite(green_output, HIGH);
          tone(buzzer, GREEN_NOTE, 500);
          delay(500);
          digitalWrite(green_output, LOW);
          break;
        case RED:
          Serial.print("Red ");
          digitalWrite(red_output, HIGH);
          tone(buzzer, RED_NOTE, 500);
          delay(500);
          digitalWrite(red_output, LOW);
          break;
        case YELLOW:
          Serial.print("Yellow ");
          digitalWrite(yellow_output, HIGH);
          tone(buzzer, YELLOW_NOTE, 500);
          delay(500);
          digitalWrite(yellow_output, LOW);
          break;
        case BLUE:
          Serial.print("Blue ");
          digitalWrite(blue_output, HIGH);
          tone(buzzer, BLUE_NOTE, 500);
          delay(500);
          digitalWrite(blue_output, LOW);
          break;
      }
      delay(500);
      i++;
    }
    Serial.println("");
    // Reading inputs
    digitalWrite(white_output, HIGH);
    Serial.print("< ");
    i = 0;
    while ( i < score + 1) {
      last_input = -1;
      while(last_input == -1) {
        delay(10);
      }
      switch(last_input) {
        case GREEN:
          Serial.print("Green ");
          tone(buzzer, GREEN_NOTE, 500);
          delay(600);
          break;
        case RED:
          Serial.print("Red ");
          tone(buzzer, RED_NOTE, 500);
          delay(600);
          break;
        case YELLOW:
          Serial.print("Yellow ");
          tone(buzzer, YELLOW_NOTE, 500);
          delay(600);
          break;
        case BLUE:
          Serial.print("Blue ");
          tone(buzzer, BLUE_NOTE, 500);
          delay(600);
          break;
        case WHITE:
          Serial.print("White ");
          break;
      }
      if ( last_input == rdn[i] ) {
        i++;
      } else {
        game_over = 1;
        i = 100; // Exit while
      }
    }
    if (!game_over) { score++; }
    Serial.println("");
    delay(500);
    digitalWrite(white_output, LOW);
    Serial.print("Score: ");
    Serial.println(score);
  }
  tone(buzzer, BLUE_NOTE, 100);
  delay(100);
  tone(buzzer, YELLOW_NOTE, 100);
  delay(100);
  tone(buzzer, RED_NOTE, 100);
  delay(100);
  tone(buzzer, GREEN_NOTE, 100);
  delay(1000);
  Serial.write("Game over.\n");
}

void green_button_change() {
  green_state = !green_state;
  digitalWrite(green_output, green_state);
  if (green_state == HIGH) {
    last_input = GREEN;
  }
}

void red_button_change() {
  red_state = !red_state;
  digitalWrite(red_output, red_state);
  if (red_state == HIGH) {
    last_input = RED;
  }
}

void yellow_button_change() {
  yellow_state = !yellow_state;
  digitalWrite(yellow_output, yellow_state);
  if (yellow_state == HIGH) {
    last_input = YELLOW;
  }
}

void blue_button_change() {
  blue_state = !blue_state;
  digitalWrite(blue_output, blue_state);
  if (blue_state == HIGH) {
    last_input = BLUE;
  }
}

void white_button_change() {
  white_state = !white_state;
  digitalWrite(white_output, white_state);
  if (white_state == HIGH) {
    last_input = WHITE;
  }
}

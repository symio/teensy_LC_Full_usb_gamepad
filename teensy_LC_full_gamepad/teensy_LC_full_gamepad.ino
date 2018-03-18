// ************************************************************************************************
// Gamepi_2_teensy_lc rewrite with optimization
// Huby Franck LGPL V3
// Original code by araym on https://www.instructables.com/id/GamePi-the-Handheld-Emulator-Console
// Optimization based upon Bounce2 examples : https://github.com/thomasfredericks/Bounce2/blob/master/examples/bounce_multiple/bounce_multiple.ino

#include <Bounce2.h>

#define BTN_NUMBER 16

const uint8_t BOUNCE_I = 10;

// The button struct (it says what a button is, globally an input and a teensy Joystick output code)
struct BTN {
  uint8_t pin; // Input or attached pin on the teensy
  uint8_t out; // output Joystick code
};

// Buttons input/ouput definition (welcome to the Matrix ; please choose red or blue ;-) )
// Buttons are defined as the struct just above
//  Up,     Down,    Left,     Right,    A,        B,        X,        Y,
//  L1,     L2,      R1,       R2,       Start,    Select,   an_L_btn, an_R_btn
const BTN BUTTONS_DEF[BTN_NUMBER] = {
   {0, 1}, {1, 2},  {2, 3},   {3, 4},   {4, 5},   {5, 6},   {6, 7},   {7, 8},
   {8, 9}, {9, 10}, {10, 11}, {11, 12}, {20, 13}, {21, 14}, {16, 15}, {19, 16}
};

Bounce * buttons = new Bounce[BTN_NUMBER];

// Left Analog Stick
int    an_L_x     = A0;
int    an_L_y     = A1;

// Right Analog Stick
int    an_R_x     = A3;
int    an_R_y     = A4;

void setup() {
  // put your setup code here, to run once:
  // ok initialize all the bounce2 objects @ once
  for (int i = 0; i < BTN_NUMBER; i++) {
    buttons[i].attach(BUTTONS_DEF[i].pin, INPUT_PULLUP);
    buttons[i].interval(BOUNCE_I);
  }

  // doing analog sticks definitions
  pinMode(A0, INPUT);         //an_L_x
  pinMode(A1, INPUT);         //an_L_y
  pinMode(A3, INPUT);         //an_R_x
  pinMode(A4, INPUT);         //an_R_y
}

void loop() {
  // put your main code here, to run repeatedly:

  // test if button is pressed or released and send the correct code via Joystick magic Object
  for (int i = 0; i < BTN_NUMBER; i++) {
    if(buttons[i].fell()) {
      Joystick.button(BUTTONS_DEF[i].out, 1);
    }
    if(buttons[i].rose()) {
      Joystick.button(BUTTONS_DEF[i].out, 0);
    }
  }
  // Left Analog Stick
  Joystick.X(       analogRead(an_L_x));
  Joystick.Y(       analogRead(an_L_y));

  // Right Analog Stick
  Joystick.Z(       analogRead(an_R_x));
  Joystick.Zrotate( analogRead(an_R_y));
}

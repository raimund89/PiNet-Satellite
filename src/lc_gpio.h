#ifndef LC_GPIO
#define LC_GPIO

#include <Ticker.h>

Ticker program_ticker;

class Color {
  public:
    int r, g, b;

    Color(int red, int green, int blue) {
      r = red;
      g = green;
      b = blue;
    }
};

// Some default colors
#define COLOR_BLACK Color(0,0,0)
#define COLOR_RED   Color(255,0,0)
#define COLOR_GREEN Color(0,255,0)
#define COLOR_BLUE  Color(0,0,255)
#define COLOR_WHITE Color(255,255,255)

// Pin definitions on an ESP8285 Magic Home type LED controller
#define PWM_GREEN 2
#define PWM_RED   0
#define PWM_BLUE  3

Color currentColor = COLOR_WHITE;
Color programColor = COLOR_RED;

void Program_CycleColors(float);

void InitGPIO()
{
  pinMode(PWM_GREEN, OUTPUT);
  pinMode(PWM_RED, OUTPUT);
  pinMode(PWM_BLUE, OUTPUT);

  // Avoid any *4 or /4, just change the analog range
  analogWriteRange(255);

  // By default, turn on at half the power
  Program_CycleColors(0.1);
}

void SetColor(Color c) {
  analogWrite(PWM_RED, c.r);
  analogWrite(PWM_GREEN, c.g);
  analogWrite(PWM_BLUE, c.b);
}

void SetColor(Color c, bool save) {
  SetColor(c);

  if(save)
    currentColor = c;
}

Color GetColor() {
  return currentColor;
}

Color GetProgramColor() {
  return programColor;
}

void SetProgramColor(Color c) {
  SetColor(c);
  programColor = c;
}

void Tick_CycleColors() {
  Color c = GetProgramColor();

  if(c.r == 255) {
    SetProgramColor(COLOR_GREEN);
  }
  else if(c.g == 255) {
    SetProgramColor(COLOR_BLUE);
  }
  else if(c.b == 255) {
    SetProgramColor(COLOR_RED);
  }
  else {
    SetProgramColor(COLOR_RED);
  }
}

void Program_CycleColors(float speed) {
  program_ticker.attach(speed, Tick_CycleColors);
}

void Program_Clear() {
  program_ticker.detach();
  SetColor(currentColor);
}

#endif

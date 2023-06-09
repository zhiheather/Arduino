#include <FastLED.h>

#define LED_PIN      7
#define NUM_LEDS   228
#define NUM_ROWS    38
#define CHANGE_COLOR_AFTER  10

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

//26
byte nerds[]
{
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 0, //N
   0, 1, 0, 0, 0, 0,
   0, 0, 1, 0, 0, 0,
   0, 0, 0, 1, 0, 0,
   1, 1, 1, 1, 1, 0, 
   0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 0, //E
   1, 0, 1, 0, 1, 0,
   1, 0, 1, 0, 1, 0, 
   1, 0, 1, 0, 1, 0,
   0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 0, //R
   1, 0, 1, 0, 0, 0,
   1, 0, 1, 1, 0, 0,
   0, 1, 0, 0, 1, 0,
   0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 0, //D
   1, 0, 0, 0, 1, 0,
   1, 0, 0, 0, 1, 0,
   0, 1, 1, 1, 0, 0,
   0, 0, 0, 0, 0, 0, 
   0, 1, 0, 0, 1, 0, //S
   1, 0, 1, 0, 1, 0,
   1, 0, 1, 0, 1, 0,
   1, 0, 0, 1, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0
};
byte ofthe []
{
   0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, //O
   0, 1, 1, 1, 0, 0,
   1, 0, 0, 0, 1, 0,
   1, 0, 0, 0, 1, 0,
   0, 1, 1, 1, 0, 0,
   0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 0, //F
   1, 0, 1, 0, 0, 0,
   1, 0, 1, 0, 0, 0,
   1, 0, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, //T
   1, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 0,
   1, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 0, //H
   0, 0, 1, 0, 0, 0,
   0, 0, 1, 0, 0, 0,
   1, 1, 1, 1, 1, 0,
   0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 0, //E
   1, 0, 1, 0, 1, 0,
   1, 0, 1, 0, 1, 0, 
   1, 0, 1, 0, 1, 0,
   0, 0, 0, 0, 0, 0
};
byte north []
{
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0, //N
  0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0,
  1, 1, 1, 1, 1, 0, 
  0, 0, 0, 0, 0, 0, //O
  0, 1, 1, 1, 0, 0,
  1, 0, 0, 0, 1, 0,
  1, 0, 0, 0, 1, 0,
  0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0, //R
  1, 0, 1, 0, 0, 0,
  1, 0, 1, 1, 0, 0,
  0, 1, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, //T
  1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0,
  1, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0, //H
  0, 0, 1, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  1, 1, 1, 1, 1, 0
};
int color[3] = {150, 0, 0};

void randomizeColor()
{
  color[0] = random(0, 150);
  color[1] = random(0, 150);
  color[2] = random(0, 150);
}
  
void loop() {
      randomizeColor();

    // NERDS
    for (int i = 0; i < sizeof(nerds); i++)
    {
      if (nerds[i] == 1)
      { 
        leds[i] = CRGB(color[0], color[1], color[2]);
      }
      else 
      {
        leds[i] = CRGB(0, 0, 0);
      }
    }  
    FastLED.show();
    delay(2000);

    // OF THE
    for (int i = 0; i < sizeof(ofthe); i++)
    {
      if (ofthe[i] == 1)
      { 
        leds[i] = CRGB(color[0], color[1], color[2]);
      }
      else 
      {
        leds[i] = CRGB(0, 0, 0);
      }
    }  
    FastLED.show();
    delay(2000);

    //NORTH
    for (int i = 0; i < sizeof(north); i++)
    {
      if (north[i] == 1)
      { 
        leds[i] = CRGB(color[0], color[1], color[2]);
      }
      else 
      {
        leds[i] = CRGB(0, 0, 0);
      }
    }  
    FastLED.show();
    delay(2000);
}

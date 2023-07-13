#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS   228

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

int logo [][6]
{
  { 1, 1, 1, 0, 1, 0 }, //5
  { 1, 0, 1, 0, 1, 0 },
  { 1, 0, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 1, 1, 1, 1, 1, 0 }, //6
  { 1, 0, 1, 0, 1, 0 },
  { 1, 0, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 1, 1, 1, 1, 1, 0 }, //8
  { 1, 0, 1, 0, 1, 0 },
  { 1, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0 }
};
int shift = 0;

  
void loop() {
    int offset = 0;
    int color[3] = {100, 0, 0};
    int roundStart = shift;
    
    while (offset < NUM_LEDS)
    {
      for (int i = 0 + roundStart; i < 13; i++)
      {
        roundStart = 0;
        for (int j = 0; j < 6; j++ )
        {
          if ( logo[i][j] == 1)
          {
            leds[offset] = CRGB(color[0], color[1], color[2]);
          }
          else
          {
            leds[offset] = CRGB(0, 0, 0);
          }
          offset = offset + 1;
        }

      }
    }
    FastLED.show();
    delay(500);
    shift += 1;
    if (shift >= 13)
    {
      shift = 0;
    }
   
  // delay(500);
  
  /*leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  delay(500);  
  leds[1] = CRGB(0, 255, 0);
  FastLED.show();
  delay(500);
  leds[2] = CRGB(0, 0, 255);
  FastLED.show();
  delay(500);
  leds[5] = CRGB(150, 0, 255);
  FastLED.show();
  delay(500);
  leds[9] = CRGB(255, 200, 20);
  FastLED.show();
  delay(500);
  leds[14] = CRGB(85, 60, 180);
  FastLED.show();
  delay(500);
  leds[19] = CRGB(50, 255, 20);
  FastLED.show();
  delay(500);*/
}

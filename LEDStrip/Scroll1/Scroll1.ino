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

    while (offset < shift*6)
    {
      leds[offset] = CRGB(0, 0, 0);
      offset++;
    }
    
    for (int i = 0; i < 13; i++)
    {
      for (int j = 0; j < 6; j++ )
      {
        if (offset < NUM_LEDS)
        {
          if ( logo[i][j] == 1)
          {
            leds[offset] = CRGB(color[0], color[1], color[2]);
          }
          else
          {
            leds[offset] = CRGB(0, 0, 0);
          }
          offset++;
        }
        // fell off the end, backfill start
        else 
        {
          if (logo[i][j] == 1)
          {
            leds[offset - NUM_LEDS] = CRGB(color[0], color[1], color[2]);
          }
          else
          {
            leds[offset - NUM_LEDS] = CRGB(0, 0, 0);
          }
          offset++;
        }
      }

    }

  
    while (offset < NUM_LEDS)
    {
      leds[offset] = CRGB(0, 0, 0);
      offset = offset + 1;
    }
    
    FastLED.show();
    delay(200);
    shift += 1;
    if (shift >= 50)
    {
      shift = 0;
    }
}

#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS   228

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

  int greenSet[][3] = {
    {0, 0, 0},
    {0, 50, 0},
    {0, 100, 0},
    {0, 100, 0},
    {0, 50, 0},
    {0, 0, 0}
  };

  int greenSetOffset[][3] {
    {0, 2, 0},
    {0, 2, 0},
    {0, 2, 0},
    {0, 2, 0},
    {0, 2, 0},
    {0, 2, 0}
  };

  
void loop() {
    int offset = 0;
    while (offset < NUM_LEDS)
    {
      for (int i = 0; i < 6; i++)
      {
        leds[i + offset] = CRGB(greenSet[i][0], greenSet[i][1], greenSet[i][2]);
      
        for (int j = 0; j < 3; j++)
        {
          greenSet[i][j] += greenSetOffset[i][j];
  
          if (greenSet[i][j] > 150)
          {
            greenSet[i][j] = 150;
            greenSetOffset[i][j] *= -1;
          }
          else if (greenSet[i][j] < 0)
          {
            greenSet[i][j] = 0;
            greenSetOffset[i][j] *= -1;
          }
        }
      }
      offset = offset + 6;
    }
    delay(100);
    FastLED.show();
   
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

#include <FastLED.h>

#define LED_PIN      7
#define NUM_LEDS   228
#define NUM_ROWS    38


CRGB leds[NUM_LEDS];
uint8_t topValue = 230;
uint8_t bottomValue = 15;


  int greenSet[][3] = {
    {0, 30, 0},
    {0, 90, 0},
    {0, 150, 0},
    {0, 150, 0},
    {0, 90, 0},
    {0, 30, 0}
  };

  int greenSetMask[3] {0, 1, 0};

 int panel[NUM_ROWS][6][3];

 int rowIncrement[NUM_ROWS]; // increment of LEDs brightness per loop
 
void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  
  int offset = 0;   
  for (int i = 0; i < NUM_ROWS; i++)
  {
    rowIncrement[i] = random(6) - 3;
    if (rowIncrement[i] == 0)
    {
      rowIncrement[i] = 1;
    }
  }
  // set initial LED values, with a random start offset
  while (offset < NUM_LEDS)
  {
    int startOffset = random(50);
    startOffset = startOffset - 25;
    for (int i = 0; i < 6; i++)
    {
      leds[offset] = CRGB(greenSet[i][0] + startOffset*greenSetMask[0], greenSet[i][1] + startOffset*greenSetMask[1], greenSet[i][2] + startOffset*greenSetMask[2]);
      //leds[offset] = CRGB(greenSet[i][0], greenSet[i][1], greenSet[i][2]);
      offset++;
    }
  }
  FastLED.show();
}
  
void loop() {
    int offset = 0;

    while (offset < NUM_LEDS)
    {
      int currentRow = offset/6;
      // precheck row, do we need to reverse?
      for (int i = 0; i < 6; i++)
      {
        // if any of our LEDS are under the bottom value, we need to start increasing brightness
        if (leds[offset + i].green < bottomValue && rowIncrement[currentRow] < 0)
        {
          rowIncrement[currentRow] = rowIncrement[currentRow] * -1;
          /*Serial.print("Now increasing row ");
          Serial.print(currentRow);
          Serial.print("\r\n");*/
        }
        // if any of our LEDS are over the top value, we need to start decreasing brightness
        else if (leds[offset + i].green > topValue && rowIncrement[currentRow] > 0)
        {
          rowIncrement[currentRow] = rowIncrement[currentRow] * -1;
          /*Serial.print("Now decreasing row ");
          Serial.print(currentRow);
          Serial.print("\r\n");*/
        }
      }
      // now set this row based on any new incrementals
      for (int j = 0; j < 6; j++)
      {
        leds[offset + j] = CRGB(leds[offset + j].red + rowIncrement[currentRow]*greenSetMask[0], leds[offset + j].green + rowIncrement[currentRow]*greenSetMask[1], leds[offset + j].blue + rowIncrement[currentRow]*greenSetMask[2]);
      }
      offset = offset + 6;
    }
    FastLED.show();
    //delay(100);
    
  }

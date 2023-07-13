#include <FastLED.h>

#define LED_PIN      7
#define NUM_LEDS   228
#define NUM_ROWS    38
#define CHANGE_COLOR_AFTER  10
#define AURORA_DELAY 20

CRGB leds[NUM_LEDS];


// values for aurora
uint8_t topValue = 230;
uint8_t bottomValue = 5;


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

 // values for scroller
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

int color[3] = {150, 0, 0};
int loopSinceColorChange = 0;

void randomizeColor()
{
  color[0] = random(0, 150);
  color[1] = random(0, 150);
  color[2] = random(0, 150);
}
 
void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  initiateAurora();

}

void initiateAurora()
{
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

  initiateAurora();

  for (int cycleCount = 0; cycleCount < 1000; cycleCount ++)
  {
    offset = 0;
    while (offset < NUM_LEDS)
    {
      int currentRow = offset/6;
      // precheck row, do we need to reverse?
      for (int i = 0; i < 6; i++)
      {
        // if any of our LEDS are under the bottom value, we need to start increasing brightness
        if (leds[offset + i].green < bottomValue && rowIncrement[currentRow] < 0)
        {
          // let's reset the row increment also
          rowIncrement[currentRow] = random(2) + 1;
          //rowIncrement[currentRow] = rowIncrement[currentRow] * -1;
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
    delay(AURORA_DELAY);
  }
  // scroll 568
  for (int scrollCount = 0; scrollCount < 35; scrollCount++)
  {
    offset = 0;
    if (loopSinceColorChange > CHANGE_COLOR_AFTER)
    {
      randomizeColor();
      loopSinceColorChange = 0;
    }
    loopSinceColorChange++;

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
    
    // wipe so the aurora doesn't lose it
    offset = 0;
    shift = 0;
    while (offset < NUM_LEDS)
    {
      leds[offset] = CRGB(0, 0, 0);
      offset = offset + 1;
    }
  }

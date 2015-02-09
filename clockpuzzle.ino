/*
Code by Josh Ward, for the puzzle "Spin the Throttle" as seen on JCC5.

This code is only really usable for Puzzle number 10 on JoCo Cruise 5's Puzzle Hunt, "#5isAlive".  It might also be useful
if you're making a circular array of LEDs in a switchback pattern.  The way the lights are arrayed looks something like this:

     28       3       4
       29     2     5
         30   1   6
          31  0 7 
27 26 25 24        8 9 10 11
           23 16 15
          22  17  14
        21    18    13   
      20      19      12

It would be very posible to add more lights per row, and more rows in the circle, you would just have to change all 
the %8 and %4 lines to match your new numbers.

So, wire it up like that, connect the data and clock pins to 6 and 7 (if you have a clock line), one end of a button to RST
and the other end to pin 3.

This code is licensed Creative Commons, Attribution-NonCommercial-ShareAlike.  

"This license lets others remix, tweak, and build upon your 
work non-commercially, as long as they credit you and 
license their new creations under the identical terms."
*/

#include "FastLED.h"


// How many leds in your strip?
#define NUM_LEDS 32

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 6
#define pin3 3
#define CLOCK_PIN 7  //I didn't need it, but it's here anyway.


// Define the array of leds
CRGB leds[NUM_LEDS];

uint8_t n = 0;  //hue
uint8_t top = 0;  //top of the clock
uint8_t randomtop = 0;
uint8_t rate = 75; //default spin rate


uint8_t counter = 0;
uint8_t colorcount = 0;



void setup() { 
	FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS); //Set to whatever kind of LEDs you're using.
        FastLED.setBrightness(32);
        randomSeed(analogRead(5));
  pinMode(pin3, OUTPUT);  //making an extra "ground" pin to pull down the reset button.
  digitalWrite(pin3, LOW);
}

void loop() { 
  
//Hue values if you want to manually set more than just red.
//red: 0
//orange: 32
//yellow: 64
//green: 96
//blue: 160
//purple: 192
startup();
  randomtop = 32; //really random to start...
  top = findtop(top, randomtop, rate);
  showG(getcolor(), top); 
  showR(getcolor(), top);
  showE(0, top);
  showE(getcolor(), top);
  showN(0, top);
  top = findtop(top, randomtop, rate); //still at the top
  showT(0, top);
  showO(getcolor(), top);
  showP(getcolor(), top);
  top = findtop(top, randomtop, rate); //still at the top
  showE(0, top);
  showN(getcolor(), top);
  showD(getcolor(), top);
  randomtop = random(20, 40);  //first time the top is moving, anywhere between 20 and 40 marks from where it started.
                               //Note after the event: I should have added a modifier so it would never be the same
                               //top end as the previous one. (Something like "if randomtop%8 == 0, do it again"
  top = findtop(top, randomtop, rate);
  showR(0, top);
  showE(getcolor(), top);
  showD(getcolor(), top);
  randomtop = random(20, 40);
  top = findtop(top, randomtop, rate);
  showL(getcolor(), top);
  showE(getcolor(), top);
  showT(0, top);
  showT(getcolor(), top);
  showE(getcolor(), top);
  showR(getcolor(), top);
  showS(getcolor(), top);
  randomtop = random(20, 40);
  top = findtop(top, randomtop, rate);
  showI(0, top);
  showN(0, top);
  randomtop = random(20, 40);
  top = findtop(top, randomtop, rate);
  showM(0, top);
  showY(getcolor(), top);
  randomtop = random(20, 40);
  top = findtop(top, randomtop, rate);
  showA(0, top);
  showN(0, top); 
  showS(getcolor(), top);
  showW(getcolor(), top);
  showE(getcolor(), top); 
  showR(getcolor(), top);
  
  for(int j = 4; j >= 0; j--) {
        Serial.println(j);
 FastLED.clear();
  for(uint8_t i = 0; i < NUM_LEDS; i++) {

  if (i%8 == j || i%8 == (7-j)){
    leds[i] = CHSV(0, 255, 255);
  }
  }
  FastLED.show();
  delay(1000);
}
FastLED.clear();
FastLED.show();
    Serial.println("did I get here?");
    
while (1) {
  delay(32000);
  }
/* This code below is only for testing. Remove before flight.*/
/*
This is the counter for how many times the animation is completed for the stres test I did before the cruise.

if (counter >= NUM_LEDS) {
  counter = 0;
colorcount += 16;
}

for(uint8_t i = 0; i < NUM_LEDS; i++) {
if (i <= counter) {
leds[i] = CHSV(colorcount, 255, 255);
  }
}
FastLED.show();
delay(3000);

counter++;
*/
/* End test code here */
  

}

void startup(){
    FastLED.clear();
for(uint8_t j = 0; j < 4; j++) {
  for(uint8_t i = 0; i < NUM_LEDS; i++) {

  if (i%8 == j || i%8 == (7-j)){
    leds[i] = CHSV(0, 255, 255);
  }
  }
  FastLED.show();
  delay(1000);
}
}

uint8_t getcolor() {
 uint8_t color = random(32, 192);
 while ((color >= 75) && (color <= 120)) {  //Since green is off limits, do it again if you come up with anything close.
   color = random(32, 192);
 }
 return color;
}

void showSegmentOne(uint8_t rail1, uint8_t color, uint8_t top) {
FastLED.clear();
  FastLED.show();
  delay(1000);
  
  int j = (rail1+top)%8;
  
  leds[(j*4)+0] = CHSV(color, 255, 255);
  leds[(j*4)+1] = CHSV(color, 255, 255);
  leds[(j*4)+2] = CHSV(color, 255, 255);  
  leds[(j*4)+3] = CHSV(color, 255, 255);
}

void showSegmentTwo(uint8_t rail2, uint8_t color, uint8_t top) {
  uint8_t j = (rail2+top)%8;
  
  leds[(j*4)+0] = CHSV(color, 255, 255);
  leds[(j*4)+1] = CHSV(color, 255, 255);
  leds[(j*4)+2] = CHSV(color, 255, 255);  
  leds[(j*4)+3] = CHSV(color, 255, 255);
FastLED.show();
delay(3000);
}

uint8_t findtop(uint8_t top, uint8_t pick, uint8_t rate){
  delay(1000);
FastLED.clear();
  FastLED.show();
  delay(1000);
  pick = pick + top;
  for(uint8_t j = top; j <= pick; j++) {  
  for(uint8_t i = 0; i < NUM_LEDS; i++) {
  leds[i] = CRGB::Black;
  }
  FastLED.show();
  
  leds[((j%8)*4)+0] = CHSV(96, 255, 255);
  leds[((j%8)*4)+1] = CHSV(96, 255, 255);
  leds[((j%8)*4)+2] = CHSV(96, 255, 255);  
  leds[((j%8)*4)+3] = CHSV(96, 255, 255);
  
  FastLED.show();
  delay(rate);
  }
  
  for (int bright = 255; bright > 0; bright-=7){
  leds[((pick%8)*4)+0] = CHSV(96, 255, bright);
  leds[((pick%8)*4)+1] = CHSV(96, 255, bright);
  leds[((pick%8)*4)+2] = CHSV(96, 255, bright);  
  leds[((pick%8)*4)+3] = CHSV(96, 255, bright);
  
  FastLED.show();
  delay(100);
  }
  pick = pick%8;
  return pick;
}

//Yay semaphore!

void showA(uint8_t color, uint8_t top){
  showSegmentOne(4, color, top);
  showSegmentTwo(5, color, top);
}
void showB(uint8_t color, uint8_t top){
  showSegmentOne(4, color, top);
  showSegmentTwo(6, color, top);
}
void showC(uint8_t color, uint8_t top){
  showSegmentOne(4, color, top);
  showSegmentTwo(7, color, top);
}
void showD(uint8_t color, uint8_t top){
  showSegmentOne(4, color, top);
  showSegmentTwo(0, color, top);
}
void showE(uint8_t color, uint8_t top){
  showSegmentOne(4, color, top);
  showSegmentTwo(1, color, top);
}
void showF(uint8_t color, uint8_t top){
  showSegmentOne(4, color, top);
  showSegmentTwo(2, color, top);
}
void showG(uint8_t color, uint8_t top){
  showSegmentOne(4, color, top);
  showSegmentTwo(3, color, top);
}
void showH(uint8_t color, uint8_t top){
  showSegmentOne(5, color, top);
  showSegmentTwo(6, color, top);
}
void showI(uint8_t color, uint8_t top){
  showSegmentOne(5, color, top);
  showSegmentTwo(7, color, top);
}
void showJ(uint8_t color, uint8_t top){
  showSegmentOne(0, color, top);
  showSegmentTwo(2, color, top);
}
void showK(uint8_t color, uint8_t top){
  showSegmentOne(0, color, top);
  showSegmentTwo(5, color, top);
}
void showL(uint8_t color, uint8_t top){
  showSegmentOne(1, color, top);
  showSegmentTwo(5, color, top);
}
void showM(uint8_t color, uint8_t top){
  showSegmentOne(2, color, top);
  showSegmentTwo(5, color, top);
}
void showN(uint8_t color, uint8_t top){
  showSegmentOne(3, color, top);
  showSegmentTwo(5, color, top);
}
void showO(uint8_t color, uint8_t top){
  showSegmentOne(6, color, top);
  showSegmentTwo(7, color, top);
}
void showP(uint8_t color, uint8_t top){
  showSegmentOne(6, color, top);
  showSegmentTwo(0, color, top);
}
void showQ(uint8_t color, uint8_t top){
  showSegmentOne(6, color, top);
  showSegmentTwo(1, color, top);
}
void showR(uint8_t color, uint8_t top){
  showSegmentOne(6, color, top);
  showSegmentTwo(2, color, top);
}
void showS(uint8_t color, uint8_t top){
  showSegmentOne(6, color, top);
  showSegmentTwo(3, color, top);
}
void showT(uint8_t color, uint8_t top){
  showSegmentOne(7, color, top);
  showSegmentTwo(0, color, top);
}
void showU(uint8_t color, uint8_t top){
  showSegmentOne(7, color, top);
  showSegmentTwo(1, color, top);
}
void showV(uint8_t color, uint8_t top){
  showSegmentOne(0, color, top);
  showSegmentTwo(3, color, top);
}
void showW(uint8_t color, uint8_t top){
  showSegmentOne(1, color, top);
  showSegmentTwo(2, color, top);
}
void showX(uint8_t color, uint8_t top){
  showSegmentOne(1, color, top);
  showSegmentTwo(3, color, top);
}
void showY(uint8_t color, uint8_t top){
  showSegmentOne(7, color, top);
  showSegmentTwo(2, color, top);
}
void showZ(uint8_t color, uint8_t top){
  showSegmentOne(2, color, top);
  showSegmentTwo(3, color, top);
}


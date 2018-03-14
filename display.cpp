#include <vector>
#include "display.h"
#include "mbed.h"

void Display::clear() {
  for(int i = 0; i < displayBitmap.size(); i++) {
    displayBitmap[i] = 0;
  }
}
  
void Display::__set_pixel__(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
  int index = 3*(width*x + y);
  displayBitmap[index] = r == 0 ? 0 : 1<<r;
  displayBitmap[index+1] = g == 0 ? 0 : 1<<g;
  displayBitmap[index+2] = b == 0 ? 0 : 1<<b;
}

void Display::set_pixel64x64(int x, int y, uint8_t r, uint8_t g, uint8_t b) {

  if(x >= 32) {
    y = 127 - y;
    x = 63 - x;
  }

  __set_pixel__(x, y, r, g, b);
}


void Display::draw() {
  for(int i = 0; i < displayBitmap.size(); i++) {
    displayBitmap_temp[i] = displayBitmap[i];
  }

  for(int counter = 0; counter < 8; counter++) {
    for(int x=0; x < 16; x++) {
      for(int y = 0; y < width; y++) {
	int index = 3*(width*x + y);
	
	uint8_t *r = &displayBitmap_temp[index];
	uint8_t *g = &displayBitmap_temp[index+1];
	uint8_t *b = &displayBitmap_temp[index+2];
	
	R1_pin = *r > 0 ? 1 : 0;
	G1_pin = *g > 0 ? 1 : 0;
	B1_pin = *b > 0 ? 1 : 0;

	*r >>= 1;
	*g >>= 1;
	*b >>= 1;

	index = 3*(width*(x+16) + y);
	
	r = &displayBitmap_temp[index];
	g = &displayBitmap_temp[index+1];
	b = &displayBitmap_temp[index+2];

	R2_pin = *r > 0 ? 1 : 0;
	G2_pin = *g > 0 ? 1 : 0;
	B2_pin = *b > 0 ? 1 : 0;

	*r >>= 1;
	*g >>= 1;
	*b >>= 1;

	S_pin = 0;
	S_pin = 1;
      }
      
      L_pin = 1;
      L_pin = 0;
      
      int pinState = 0;
      for (int i=4; i>=0; i--)  {
	if ( x & (1<<i) )
	  pinState= 1;
	else
	  pinState= 0;
	
	abcd_pins[i] = pinState;
      }
      
      E_pin = 0;
      wait_us(delay_between_lines);
      E_pin = 1;
    }
  }
}

static void display_thread_hook(Display *display) {
  while(true) {
    display->draw();
    wait_us(display->delay_between_frames);
  }
}

void Display::start() {
  E_pin = 1;
  clear();
  thread.start(callback(display_thread_hook, this));
}


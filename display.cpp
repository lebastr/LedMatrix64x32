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
  uint32_t out = 0x0;

  for(int i = 0; i < displayBitmap.size(); i++) {
    displayBitmap_temp[i] = displayBitmap[i];
  }

  for(int counter = 0; counter < 8; counter++) {
    for(uint32_t x=0; x < 16; x++) {
      for(uint32_t y = 0; y < width; y++) {
	int index = 3*(width*x + y);

	out = display_port;
	out &= ~(R1_pin | G1_pin | B1_pin | R2_pin | G2_pin | B2_pin);

	uint8_t *r = &displayBitmap_temp[index];
	uint8_t *g = &displayBitmap_temp[index+1];
	uint8_t *b = &displayBitmap_temp[index+2];
	
	out |= *r > 0 ? R1_pin : 0x0;
	out |= *g > 0 ? G1_pin : 0x0;
	out |= *b > 0 ? B1_pin : 0x0;

	*r >>= 1;
	*g >>= 1;
	*b >>= 1;

	index = 3*(width*(x+16) + y);
	
	r = &displayBitmap_temp[index];
	g = &displayBitmap_temp[index+1];
	b = &displayBitmap_temp[index+2];

	out |= *r > 0 ? R2_pin : 0x0;
	out |= *g > 0 ? G2_pin : 0x0;
	out |= *b > 0 ? B2_pin : 0x0;

	*r >>= 1;
	*g >>= 1;
	*b >>= 1;

	display_port = out;

	out &= ~S_pin;
	display_port = out;

	out |= S_pin;
	display_port = out;
      }
      
      out |= L_pin;
      display_port = out;

      out &= ~L_pin;
      display_port = out;

      out &= ~0x3c;

      out |= (x << 2);

      display_port = out;

      out &= ~E_pin;
      display_port = out;
      
      wait_us(delay_between_lines);

      out |= E_pin;
      display_port = out;
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
  display_port = display_port | E_pin;
  clear();
  thread.start(callback(display_thread_hook, this));
}


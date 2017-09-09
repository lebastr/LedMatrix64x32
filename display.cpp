#include <vector>
#include "display.h"
#include "mbed.h"

void Display::clear() {
  for(int j = 0; j < 32; j++) {
    for(int i = 0; i < 64; i++) {
      displayBitmap[j*64+i] = 0;
    }
  }
}
  
void Display::set_pixel(int x, int y, uint8_t color) {
  displayBitmap[64*x+y] = color;
}

void Display::draw() {
  for(int x=0; x < 16; x++) {
    for(int y = 0; y < 64; y++) {
      uint8_t c = displayBitmap[64*x + y];

      R1_pin = c & 1;
      G1_pin = (c >> 1) & 1;
      B1_pin = (c >> 2) & 1;

      c = displayBitmap[(x+16)*64 + y];
      R2_pin = c & 1;
      G2_pin = (c >> 1) & 1;
      B2_pin = (c >> 2) & 1;

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

#include "mbed.h"
#include <vector>

struct Display {
  DigitalOut A_pin; // Data pin for rows selection A
  DigitalOut B_pin; // Data pin for rows selection B
  DigitalOut C_pin; // Data pin for rows selection C
  DigitalOut D_pin; // Data pin for rows selection D
  
  DigitalOut G1_pin; //6; //green leds for uppwer rows
  DigitalOut G2_pin; //7; //green leds for lower rows
  DigitalOut R1_pin; //red leds for uppwer rows
  DigitalOut R2_pin; //red leds for lower rows
  DigitalOut B1_pin; // blue leds for lower rows
  DigitalOut B2_pin; // blue leds for upper rows
  
  DigitalOut S_pin; //Clock pin
  DigitalOut L_pin; //9; //Latch pin
  DigitalOut E_pin; //10; //Enable pin
  DigitalOut abcd_pins[4];
  
  Thread thread;

  const int delay_between_lines = 10; // us
  const int delay_between_frames = 1000; // us
  
  std::vector<uint8_t> displayBitmap;
  
  Display() : A_pin(D2), B_pin(D3), C_pin(D4), D_pin(D5), G1_pin(D9), 
	      G2_pin(D10), R1_pin(D11), R2_pin(D12), B1_pin(D14), B2_pin(D15),
	      S_pin(D8), L_pin(D6), E_pin(D7), abcd_pins{A_pin, B_pin, C_pin, D_pin}
  {
    displayBitmap = std::vector<uint8_t>(32*64);
  };

  
  void clear();
  
  void set_pixel(int x, int y, uint8_t color);

  void draw();
  
  void start();

  //   static void display_thread_hook(Display *display);
};

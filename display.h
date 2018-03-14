#include "mbed.h"
#include "rtos.h"
#include <vector>

#define A_pin   0x00000004
#define B_pin   0x00000008
#define C_pin   0x00000010
#define D_pin   0x00000020
#define R1_pin  0x00000100
#define G1_pin  0x00000080
#define B1_pin  0x00000400
#define R2_pin  0x00001000
#define G2_pin  0x00004000
#define B2_pin  0x00008000
#define S_pin   0x00002000
#define L_pin   0x00000800
#define E_pin   0x00000200

struct Display {
  PortOut display_port;
  /* DigitalOut A_pin; // Data pin for rows selection A */
  /* DigitalOut B_pin; // Data pin for rows selection B */
  /* DigitalOut C_pin; // Data pin for rows selection C */
  /* DigitalOut D_pin; // Data pin for rows selection D */
  
  /* DigitalOut G1_pin; //6; //green leds for uppwer rows */
  /* DigitalOut G2_pin; //7; //green leds for lower rows */
  /* DigitalOut R1_pin; //red leds for uppwer rows */
  /* DigitalOut R2_pin; //red leds for lower rows */
  /* DigitalOut B1_pin; // blue leds for lower rows */
  /* DigitalOut B2_pin; // blue leds for upper rows */
  
  /* DigitalOut S_pin; //Clock pin */
  /* DigitalOut L_pin; //9; //Latch pin */
  /* DigitalOut E_pin; //10; //Enable pin */
  /* DigitalOut abcd_pins[4]; */
  
  Thread thread;

  const int delay_between_lines = 10; // us
  const int delay_between_frames = 1000; // us
  const int width = 128;
  
  std::vector<uint8_t> displayBitmap;
  std::vector<uint8_t> displayBitmap_temp;
  
  Display() : display_port(PortE, 0x0000ffbc), thread(osPriorityRealtime)
  {
    displayBitmap = std::vector<uint8_t>(3*32*width);
    displayBitmap_temp = std::vector<uint8_t>(3*32*width);
  };

  
  void clear();
  
  void __set_pixel__(int x, int y, uint8_t r, uint8_t g, uint8_t b);
  void set_pixel64x64(int x, int y, uint8_t r, uint8_t g, uint8_t b);

  void draw();
  
  void start();

  //   static void display_thread_hook(Display *display);
};

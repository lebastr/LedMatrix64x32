#include "mbed.h"
#include <vector>
#include <string>
#include "rtos.h"
#include "fonts/homespun_font.h"

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

#define LightingTime        200       // us
#define WaitBeetweenFrames  2000     // us
#define WidthPanel          4*64
#define HeightPanel         16
#define Tints               4


PortOut display_port(PortE, 0x0000ffbc);
Thread thread(osPriorityRealtime);
Timeout light_off_timeout;

uint8_t DisplayBuffer[HeightPanel][WidthPanel]; //x x b2 g2 r2 b1 g1 r1
volatile bool LatchReady = true;
volatile uint32_t output = E_pin;

void draw_text(uint32_t col, uint32_t row, string text);

void draw_text(uint32_t col, uint32_t row, char* text, size_t length);

void clear_display();

void rect(int left, int top, int right, int bottom, int r, int g, int b);

void light_off_hook() {
  LatchReady = true;
}

void hook(void) {
  uint32_t counter = 0;

  counter = 0;
  for(int frame_number = 0;;frame_number++) {
    size_t index;
    index = 0;
    for(size_t row = 0; row < HeightPanel; ++row) {
      for(size_t col = 0; col < WidthPanel; ++col, ++index) {
	uint8_t val;
	val = DisplayBuffer[row][col];
	
	output &= ~(R1_pin | R2_pin | G1_pin | G2_pin | B1_pin | B2_pin);
	output |= val & 0x01 ? R1_pin : 0;
	output |= val & 0x02 ? G1_pin : 0;
	output |= val & 0x04 ? B1_pin : 0;
	output |= val & 0x08 ? R2_pin : 0;
	output |= val & 0x10 ? G2_pin : 0;
	output |= val & 0x20 ? B2_pin : 0;
	
	output &= ~S_pin;
	display_port = output;
	
	output |= S_pin;
	display_port = output;

	if(LatchReady) {
	  output |= E_pin;
	  display_port = output;
	}
      }
      
      output &= ~S_pin;
      
      for(;!LatchReady;) {
	counter++;
      }
      
      output |= E_pin;
      display_port = output;
      
      output |= L_pin;
      display_port = output;
      
      output &= ~L_pin;
      display_port = output;
      
      output &= ~(A_pin | B_pin | C_pin | D_pin);
      output |= (row << 2);
      
      display_port = output;
      
      output &= ~E_pin;
      display_port = output;
      
      LatchReady = false;
      light_off_timeout.attach_us(&light_off_hook, LightingTime);
    }
    if(frame_number == 100){
      char buf[10];
      sprintf(buf, "%ld", counter);
      draw_text(10,10,buf);
    }
  }
}


inline void __set_pixel__(uint32_t col, uint32_t row, int r, int g, int b){
  uint8_t mask;
  uint8_t val;
  int shift;

  
  if(row < 16) {
    mask = 7*8;
    shift = 0;
  } else {
    mask = 7;
    shift = 3;
    row -= 16;
  }

  val = DisplayBuffer[row][col];
  val &= mask;
  val |= r > 0 ? (0x1 << shift) : 0;
  val |= g > 0 ? (0x2 << shift) : 0;
  val |= b > 0 ? (0x4 << shift) : 0;
  DisplayBuffer[row][col] = val;
}

inline void set_pixel(uint32_t col, uint32_t row, int r, int g, int b) {
  row &= 63;
  col &= 127;

  if(row < 32) {
    row = 31 - row;
    col = 127 - col;
  } else {
    row -= 32;
    col += 128;
  }

  __set_pixel__(col, row, r, g, b);
}

inline int draw_letter(uint32_t col, uint32_t row, char letter) {
  int index;
  index = letter - '0' + 16;
  
  if (index < 0) {
    return -1;
  }

  for(int i = 0; i < 7; i++) {
    uint8_t val = font[index][i];
    for(int j = 0; j < 8; j++) {
      set_pixel(col+i, row+j, val&1, 0, 0);
      val >>= 1;
    }
  }
  return 1;
}

void draw_text(uint32_t col, uint32_t row, string text) {
  for(size_t i = 0; i < text.length(); ++i) {
    draw_letter(col, row, text[i]);
    col += 7;
  }
}

void draw_text(uint32_t col, uint32_t row, char* text, size_t length) {
  for(size_t i = 0; i < length; ++i) {
    draw_letter(col, row, text[i]);
    col += 7;
  }
}

void clear_display() {
  for(int row = 0; row < 64; row++) {
    for(int col = 0; col < 128; col++) {
      set_pixel(col, row, 0,0,0);
    }
  }
}

void rect(int left, int top, int right, int bottom, int r, int g, int b) {
  for(int col = left; col <= right; col++) {
    for(int row = top; row <= bottom; row++) {
      set_pixel(col, row, r, g, b);
    }
  }
}



int main() {
  uint32_t val;

  hook();
  
  //  thread.start(hook);
  
  val = 0;
  while(true){
    char buf[10];
    sprintf(buf, "%ld", val);
    draw_text(10,10,buf);
    //    wait_ms(100);
    rect(0,10,40,20,0,0,0);
    
    //    clear_display();
    val++;
  }
}



// inline void __set_pixel__(uint32_t row, uint32_t col, int r, int g, int b){
//   uint16_t r_pin, g_pin, b_pin;
//   uint16_t mask;

//   if(row < 16) {
//     r_pin = R1_pin;
//     g_pin = G1_pin;
//     b_pin = B1_pin;
//   } else {
//     r_pin = R2_pin;
//     g_pin = G2_pin;
//     b_pin = B2_pin;
//     row -= 16;
//   }

//   mask = ~(r_pin | g_pin | b_pin);

//   for(int i = 0; i < Tints; ++i) {
//     uint16_t val;
//     val = DisplayBuffer[row*Width + col + i*Width*Height];
//     val &= mask;
//     val |= r > 0 ? r_pin : 0;
//     val |= g > 0 ? g_pin : 0;
//     val |= b > 0 ? b_pin : 0;
//     r--;
//     g--;
//     b--;
//     DisplayBuffer[row*Width + col + i*Width*Height] = val;
//   }
// }

// /* row must be >= 0 and < 64. col >= 0 and < 128
 
// */


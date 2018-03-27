#include "mbed.h"
#include <vector>
#include <string>
#include "rtos.h"
#include "fonts/homespun_font.h"

#define R1_pin_shift  2
#define G1_pin_shift  3
#define B1_pin_shift  4
#define R2_pin_shift  5
#define G2_pin_shift  7 
#define B2_pin_shift  8

// b2 g2 x r2 b1 g1 r1


#define A_pin_shift   9
#define B_pin_shift   10
#define C_pin_shift   12
#define D_pin_shift   14

#define L_pin_shift   11
#define S_pin_shift   13

#define R1_pin  (0x1 << R1_pin_shift)  
#define G1_pin	(0x1 << G1_pin_shift)
#define B1_pin	(0x1 << B1_pin_shift)
#define R2_pin	(0x1 << R2_pin_shift)
#define G2_pin	(0x1 << G2_pin_shift)
#define B2_pin	(0x1 << B2_pin_shift)

#define A_pin 	(0x1 << A_pin_shift) 
#define B_pin 	(0x1 << B_pin_shift) 
#define C_pin 	(0x1 << C_pin_shift) 
#define D_pin 	(0x1 << D_pin_shift) 

#define L_pin 	(0x1 << L_pin_shift) 
#define S_pin 	(0x1 << S_pin_shift) 

#define LightingTime        10        // 83 успевает залить строку
#define WaitBeetweenFrames  1000     // us
#define WidthPanel          4*64
#define HeightPanel         16
#define ColorDepth          4
  
DigitalOut    E_Pin_Port(D7);

PortOut display_port(PortE, 0x0000ffbc);

Thread thread(osPriorityRealtime);

Timeout light_off_timeout;

uint8_t DisplayBuffer[HeightPanel][ColorDepth][WidthPanel];

volatile bool LatchReady = true;

void draw_text(uint32_t col, uint32_t row, string text, uint32_t r, uint32_t g, uint32_t b);

void draw_text(uint32_t col, uint32_t row, char* text, size_t length, uint32_t r, uint32_t g, uint32_t b);

void clear_display();

void rect(int left, int top, int right, int bottom, int r, int g, int b);

void light_off_hook() {
  LatchReady = true;
  E_Pin_Port = 1;
}

void hook(void) {
  uint32_t counter = 0;
  uint32_t output = 0;

  counter = 0;
  for(;;) {
    for(size_t row = 0; row < HeightPanel; ++row) {
      for(size_t depth = 0; depth < ColorDepth; ++depth) {
	for(size_t col = 0; col < WidthPanel;++col) {
	  uint16_t val = DisplayBuffer[row][depth][col];
	  
	  output &= ~(R1_pin | G1_pin | B1_pin | R2_pin | G2_pin | B2_pin);
	  
	  output |= val << 2;
	  
	  output &= ~S_pin;
	  display_port = output;
	  
	  output |= S_pin;
	  display_port = output;
	}
      
	output &= ~S_pin;
      
	for(;!LatchReady;) {
	  counter++;
	}
      
	output |= L_pin;
	display_port = output;
      
	output &= ~L_pin;
	display_port = output;
      
	output &= ~(A_pin | B_pin | C_pin | D_pin);
	output |= row & 0x1 ? A_pin : 0;
	output |= row & 0x2 ? B_pin : 0;
	output |= row & 0x4 ? C_pin : 0;
	output |= row & 0x8 ? D_pin : 0;
      
	display_port = output;
      
	E_Pin_Port = 0;

	LatchReady = false;
	light_off_timeout.attach_us(&light_off_hook, LightingTime*(0x1 << depth));

	for(;!LatchReady;) {
	  counter++;
	}
      }
    }
    wait_us(WaitBeetweenFrames);
  }
}


inline void __set_pixel__(uint32_t col, uint32_t row, uint32_t r, uint32_t g, uint32_t b){
  uint8_t mask;
  uint8_t val;

  // b2 g2 x r2 b1 g1 r1
  uint8_t r_bit, g_bit, b_bit;
  
  if(row < 16) {
    r_bit = 0x1;
    g_bit = 0x2;
    b_bit = 0x4;
    mask = 15*8;
  } else {
    r_bit = 0x8;
    g_bit = 0x20;
    b_bit = 0x40;
    mask = 7;
    row -= 16;
  }

  for(size_t depth = 0; depth < ColorDepth; ++depth){
    val = DisplayBuffer[row][depth][col];
    val &= mask;
    
    val |= r & 0x1 ? r_bit : 0;
    val |= g & 0x1 ? g_bit : 0;
    val |= b & 0x1 ? b_bit : 0;
    DisplayBuffer[row][depth][col] = val;

    r >>= 1;
    g >>= 1;
    b >>= 1;
  }
}

inline void set_pixel(uint32_t col, uint32_t row, uint32_t r, uint32_t g, uint32_t b) {
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

inline int draw_letter(uint32_t col, uint32_t row, char letter, uint32_t r, uint32_t g, uint32_t b) {
  int index;
  index = letter - '0' + 16;
  
  if (index < 0) {
    return -1;
  }

  for(int i = 0; i < 7; i++) {
    uint8_t val = font[index][i];
    for(int j = 0; j < 8; j++) {
      set_pixel(col+i, row+j, val&0x1 ? r : 0, val&0x1 ? g : 0, val&0x1 ? b : 0);
      val >>= 1;
    }
  }
  return 1;
}

void draw_text(uint32_t col, uint32_t row, string text, uint32_t r, uint32_t g, uint32_t b) {
  for(size_t i = 0; i < text.length(); ++i) {
    draw_letter(col, row, text[i], r, g, b);
    col += 7;
  }
}

void draw_text(uint32_t col, uint32_t row, char* text, size_t length, uint32_t r, uint32_t g, uint32_t b) {
  for(size_t i = 0; i < length; ++i) {
    draw_letter(col, row, text[i], r, g, b);
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
  
  //hook();
  thread.start(hook);
  
  val = 0;
  while(true){
    char buf[10];
    
    sprintf(buf, "%ld", val);
    int x = 10 + val;
    int y = 50 + val/2;
    draw_text(x, y, buf, val/100, val/110, val/120);
    wait_ms(40);
    rect(x, y, x+50, y+10, 0, 0, 0);

    //    set_pixel(100, val, 0, 0, 1);
    //    wait_ms(500);
    //    set_pixel(100, val, 0, 0, 0);
    
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


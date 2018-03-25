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

#define LightingTime        20       // us
#define WaitBeetweenFrames  2000     // us
#define Width               4*64
#define Height              16
#define Tints               4


PortOut display_port(PortE, 0x0000ffbc);
Thread thread(osPriorityRealtime);

uint16_t DisplayBuffer[Width*Height*Tints];

void hook(void) {
  uint32_t out;
  for(;;) {
    uint32_t index = 0;
    
    for(uint32_t tint = 0; tint < Tints; ++tint) {
      for(uint32_t row = 0; row < Height; ++row) {
	out = 0;
	for(uint32_t col = 0; col < Width; col++, ++index) {
	  uint32_t val;
	  out = DisplayBuffer[index];
	  out |= E_pin;
	  display_port = out;

	  out |= S_pin;
	  display_port = out;
	}
	
	out |= L_pin;
	display_port = out;
	
	out &= ~L_pin;
	display_port = out;
	
	out |= (row << 2);
	
	display_port = out;
	
	out &= ~E_pin;
	display_port = out;
	
	wait_us(LightingTime);
	
	out |= E_pin;
	display_port = out;
      }
    }
    wait_us(1000);
  }
  
}

inline void __set_pixel__(uint32_t row, uint32_t col, int r, int g, int b){
  uint16_t r_pin, g_pin, b_pin;
  uint16_t mask;

  if(row < 16) {
    r_pin = R1_pin;
    g_pin = G1_pin;
    b_pin = B1_pin;
  } else {
    r_pin = R2_pin;
    g_pin = G2_pin;
    b_pin = B2_pin;
    row -= 16;
  }

  mask = ~(r_pin | g_pin | b_pin);

  for(int i = 0; i < Tints; ++i) {
    uint16_t val;
    val = DisplayBuffer[row*Width + col + i*Width*Height];
    val &= mask;
    val |= r > 0 ? r_pin : 0;
    val |= g > 0 ? g_pin : 0;
    val |= b > 0 ? b_pin : 0;
    r--;
    g--;
    b--;
    DisplayBuffer[row*Width + col + i*Width*Height] = val;
  }
}

/* row must be >= 0 and < 64. col >= 0 and < 128
 
*/

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

  __set_pixel__(row, col, r, g, b);
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
  
  //hook();
  thread.start(hook);
  
  val = 0;
  while(true){
    char buf[10];
    sprintf(buf, "%ld", val);
    draw_text(10,10,buf);
    wait_ms(100);
    rect(0,10,40,20,0,0,0);
    
    //    clear_display();
    val++;
  }
}

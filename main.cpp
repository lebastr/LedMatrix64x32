#include "mbed.h"
#include <vector>
#include "rtos.h"
#include "fonts.h"
#include "fonts/homespun_font.h"
#include <string>

#define R1_pin_shift  2     // Номер порта у R1
#define G1_pin_shift  3     // Номер порта у G1
#define B1_pin_shift  4
#define R2_pin_shift  5
#define G2_pin_shift  7 
#define B2_pin_shift  8

#define A_pin_shift   9
#define B_pin_shift   10
#define C_pin_shift   12
#define D_pin_shift   14

#define L_pin_shift   11
#define S_pin_shift   13

#define R1_pin  (0x1 << R1_pin_shift)  // Бит порта для R1
#define G1_pin	(0x1 << G1_pin_shift)  // Бит порта для G1
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

#define LightingTime        150     // Минимальное время свечения строки.
#define WaitBeetweenFrames  1000    // Время ожидания между двумя кадрами. Это минимальное время, при котором вторая задача получает управление.
#define WidthPanel          4*64    // Ширина ассоциированного с панелью буффера
#define HeightPanel         16      // Его высота
#define ColorDepth          3       // Глубина цвета в битах
  
DigitalOut    E_Pin_Port(D7);

PortOut display_port(PortE, 0x0000ffbc);  // Все линии дисплея кроме Enable идут на порт E.

Thread thread(osPriorityRealtime);

Timeout light_off_timeout;

uint8_t DisplayBuffer1[HeightPanel*ColorDepth*WidthPanel];
uint8_t DisplayBuffer2[HeightPanel*ColorDepth*WidthPanel];

uint8_t *CycleReadBuffer = DisplayBuffer1;
uint8_t *DrawingBuffer = DisplayBuffer2;

volatile bool LatchReady = true;

void draw_text(uint32_t col, uint32_t row, string text, uint32_t r, uint32_t g, uint32_t b);

void draw_text(uint32_t col, uint32_t row, char* text, size_t length, uint32_t r, uint32_t g, uint32_t b);

void clear_display();

void rect(int left, int top, int right, int bottom, int r, int g, int b);

void light_off_hook() {
  LatchReady = true;
  E_Pin_Port = 1;
}

void swap_buffer() {
  uint8_t *temp = CycleReadBuffer;
  CycleReadBuffer = DrawingBuffer;
  DrawingBuffer = temp;
}

inline int buffer_shift(int row, int depth, int col) {
  return col + WidthPanel*depth + ColorDepth*WidthPanel*row;
}

void hook(void) {
  uint32_t output = 0;

  for(;;) {
    for(size_t row = 0; row < HeightPanel; ++row) {
      for(size_t depth = 0; depth < ColorDepth; ++depth) {
	for(size_t col = 0; col < WidthPanel;++col) {
	  uint16_t val = CycleReadBuffer[buffer_shift(row, depth, col)];
	  
	  output &= ~(R1_pin | G1_pin | B1_pin | R2_pin | G2_pin | B2_pin);
	  
	  output |= val << 2;
	  
	  output &= ~S_pin;
	  display_port = output;
	  
	  output |= S_pin;
	  display_port = output;
	}
      
	output &= ~S_pin;
      
	for(;!LatchReady;) { }
      
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
    val = DrawingBuffer[buffer_shift(row, depth, col)];
    val &= mask;
    
    val |= r & 0x1 ? r_bit : 0;
    val |= g & 0x1 ? g_bit : 0;
    val |= b & 0x1 ? b_bit : 0;
    DrawingBuffer[buffer_shift(row, depth, col)] = val;

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

inline void draw_bitmap(int right_col, int bottom_row, Bitmap bitmap, const int red, const int green, const int blue) {
  int index = 0;

  for(int h = 0; h < bitmap.height; h++) {
    int y = bottom_row - h;
    int x = 0;
    
    for(int b = 0; b < bitmap.byte_width; b++) {
      unsigned char byte = bitmap.data[index];

      for(int p = 0; p < 8 && x < bitmap.width; p++, x++){
	if (byte & 0x1) {
	  set_pixel(right_col-x, y, red, green, blue);
	} else {
	  set_pixel(right_col-x, y, 0, 0, 0);
	}
	byte >>= 1;
      }
      index++;
    }
  }
}

inline void draw_bitmap_sequence(int right, int bottom, Bitmap *fonts, int *idx, int size, int r, int g, int b) {
  for(int i = 0; i < size; i++) {
    Bitmap bitmap = fonts[idx[i]];
    draw_bitmap(right, bottom, bitmap, r, g, b);
    right -= bitmap.width + 2;
  }
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
  for(int i = 0; i < HeightPanel*ColorDepth*WidthPanel; i++) {
    DrawingBuffer[i] = 0;
  }
}

void rect(int left, int top, int right, int bottom, int r, int g, int b) {
  for(int col = left; col <= right; col++) {
    for(int row = top; row <= bottom; row++) {
      set_pixel(col, row, r, g, b);
    }
  }
}

// TODO max_len > 2
int decimal_decomposition(unsigned int value, int max_len, int *buffer) {
  int i;
  buffer[0] = 10;

  if (value == 0) {
    buffer[1] = 0;
    return 2;
  }
  
  for(i = 1; i < max_len && value != 0; i++) {
    buffer[i] = value % 10;
    value /= 10;
  }

  return i;
}

void draw_frame(unsigned int speed, unsigned int battery, unsigned int minutes) {
  const int buffer_length = 5;
  int buffer[buffer_length];
  int len;

  // TODO. Максимальное значение цвета сейчас зависит от ColorDepth. К сожалению при изменении ColorDepth надо менять и значения цветов
  // Стоит сделать цвет float-ом, где 1.0 - это максимальная яркость, а 0.0 - черный цвет

  len = decimal_decomposition(speed, buffer_length, buffer);
  draw_bitmap_sequence(123, 56, font3, buffer, len, 0, 7, 0);

  len = decimal_decomposition(battery, buffer_length, buffer);
  draw_bitmap_sequence(47, 18, font1, buffer, len, 15, 15*battery/100, 15*battery/100);

  len = decimal_decomposition(minutes, buffer_length, buffer);
  draw_bitmap_sequence(124, 22, font2, buffer, len, 7, 7, 0);
}

int main() {
  uint32_t val;
  
  //hook();
  thread.start(hook);
  
  val = 0;
  while(true){
    clear_display();
    draw_frame(val, 35, 34);
    swap_buffer();
    wait_ms(1000);
    val++;
  }
}
 

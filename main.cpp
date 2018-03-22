#include "mbed.h"
#include <vector>
#include "rtos.h"

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

#define LightingTime  10  // us
#define Width         4*64
#define Height        16
#define Tints         8   // TODO надо 8


PortOut display_port(PortE, 0x0000ffbc);
Thread thread(osPriorityRealtime);

uint16_t buffer[Width*Height*Tints];

void hook(void) {
  uint32_t out;
  for(;;) {
    uint32_t index = 0;
    
    for(uint32_t tint = 0; tint < Tints; ++tint) {
      for(uint32_t row = 0; row < Height; ++row) {
	out = 0;
	for(uint32_t col = 0; col < Width; ++col, ++index) {
	  out = buffer[index];
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
  }
}


int main() {
  uint32_t val;

  for(uint32_t tints = 0; tints < Tints; ++tints) {
    uint32_t index;

    if(tints == 0) {
      val = R1_pin | G1_pin;
    } else {
      val = R2_pin | B2_pin;
    }

    index = tints*Width*Height;
    for(uint32_t t = 0; t < Width*Height; ++t, ++index) {
      buffer[index] = val;
    }
  }

  //hook();
  thread.start(callback(hook));

  for(val = 1;;val++) {
    //       port = (val & 0x1);
  }
}

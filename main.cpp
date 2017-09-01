#include "mbed.h"

Thread thread;

DigitalOut Led(LED1);
InterruptIn ThereminPin(D13);
uint32_t Tick = 0;

DigitalOut A_pin(D2); // Data pin for rows selection A
DigitalOut B_pin(D3); // Data pin for rows selection B
DigitalOut C_pin(D4); // Data pin for rows selection C
DigitalOut D_pin(D5); // Data pin for rows selection D

DigitalOut G1_pin(D9); //6; //green leds for uppwer rows
DigitalOut G2_pin(D10); //7; //green leds for lower rows
DigitalOut R1_pin(D11); //red leds for uppwer rows
DigitalOut R2_pin(D12); //red leds for lower rows
DigitalOut B1_pin(D14); // blue leds for lower rows
DigitalOut B2_pin(D15); // blue leds for upper rows

DigitalOut S_pin(D8); //Clock pin
DigitalOut L_pin(D6); //9; //Latch pin
DigitalOut E_pin(D7); //10; //Enable pin

DigitalOut abcd_pins[] = {A_pin,B_pin,C_pin,D_pin};

int xdelay = 10;

uint16_t displayBitmap[32*64];//[64]; // Bitmap for display

// The bitmap (64x32) is arranged with 8 bytes per row aligned on long.
// The upper 32 rows controls the Red LED's
// The lower 32 rows controls the Green LED's
// To get yellow, set both green and red at the same time... ;-)

void clear_display()
{
  for(int j = 0; j < 32; j++) {
    for(int i = 0; i < 64; i++) {
      displayBitmap[j*64 + i] = 0;
    }
  }
}

void set_pixel(int x, int y, uint8_t color)
{
  displayBitmap[x*64 + y] = color;
}

void drawDisplay()
{
  for(int x=0; x<16; x++) {
    for(int y = 0; y < 64; y++) {
      uint8_t c = displayBitmap[x*64 + y];

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
    wait_us(xdelay);
    E_pin = 1;
  }
}

void display_drawer_thread()
{
  E_pin = 1;
  clear_display();
  while(true) {
    drawDisplay();
    wait_ms(1);
  }
}

uint16_t game_field[32][64];
uint16_t neighbors[32][64];

void init_game() {
  for(int x = 0; x < 32; x++) {
    for(int y = 0; y < 64; y++) {
      game_field[x][y] = 0;
    }
  }  

  // game_field[15][20] = 1;
  // game_field[15][21] = 1;
  // game_field[15][22] = 1;
  // game_field[16][22] = 1;
  // game_field[14][21] = 1;


  // game_field[15][20] = 1;
  // game_field[15][21] = 1;
  // game_field[15][22] = 1;
  // game_field[16][22] = 1;
  // game_field[17][21] = 1;
  
  
  for(int y = 15; y < 45; y++) {
     game_field[15][y] = 1;
  }
}

void step()
{
  int x, y;
  for(int x = 0; x < 32; x++) {
    for(int y = 0; y < 64; y++) {
      neighbors[x][y] = 0;
    }
  }

  for(uint16_t x0 = 0; x0 < 32; x0++) {
    for(uint16_t y0 = 0; y0 < 64; y0++) {
      if(game_field[x0][y0] == 1) {
	x = x0 + 32;
	y = y0 + 63;
	neighbors[(x+1)%32][y%63] += 1;
	neighbors[(x+1)%32][(y+1)%63] += 1;
	neighbors[(x+1)%32][(y-1)%63] += 1;
	neighbors[x%32][(y+1)%63] += 1;
	neighbors[x%32][(y-1)%63] += 1;
	neighbors[(x-1)%32][y%63] += 1;
	neighbors[(x-1)%32][(y+1)%63] += 1;
	neighbors[(x-1)%32][(y-1)%63] += 1;
      }
    }
  }
    
  for(int x = 0; x < 32; x++) {
    for(int y = 0; y < 64; y++) {
      if(neighbors[x][y] == 3) {
	game_field[x][y] = 1;  
      } else if (neighbors[x][y] == 2) {
	continue;
      } else {
	game_field[x][y] = 0;
      }
    }
  }
}

void draw_game() {
  for(int x = 0; x < 32; x++) {
    for(int y = 0; y < 64; y++) {
      set_pixel(x,y,game_field[x][y]);
    }
  }   
}

void theremin_interrupt() {
  Tick++;
  if (Tick % 1024 == 0) {
    Led = !Led;
  }
}

int main()
{
  ThereminPin.rise(&theremin_interrupt);
  thread.start(display_drawer_thread);
  init_game();

  int s = 0;
  
  while(1) {
    if (s == 400){
      s = 0;
      game_field[5][50] = 1;
      game_field[5][51] = 1;
      game_field[5][52] = 1;
      game_field[6][52] = 1;
      game_field[7][51] = 1;
      
      //      init_game();
    }
    draw_game();
    wait_ms(50);
    step();
    s++;
  }
}

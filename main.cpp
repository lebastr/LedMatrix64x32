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
  
  std::vector<uint32_t> displayBitmap;
  
  Display() : A_pin(D2), B_pin(D3), C_pin(D4), D_pin(D5), G1_pin(D9), 
	      G2_pin(D10), R1_pin(D11), R2_pin(D12), B1_pin(D14), B2_pin(D15),
	      S_pin(D8), L_pin(D6), E_pin(D7), abcd_pins{A_pin, B_pin, C_pin, D_pin}
  {
    displayBitmap = std::vector<uint32_t>(32*64);
  };

  
  void clear() {
    for(int j = 0; j < 32; j++) {
      for(int i = 0; i < 64; i++) {
	displayBitmap[j*64+i] = 0;
      }
    }
  };
  
  void set_pixel(int x, int y, uint32_t color) {
    displayBitmap[64*x+y] = color;
  };

  void draw() {
    for(int x=0; x < 16; x++) {
      for(int y = 0; y < 64; y++) {
	uint32_t c = displayBitmap[64*x + y];

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
  };
  
  void start() {
    E_pin = 1;
    clear();
    thread.start(callback(Display::display_thread_hook, this));
  };

  static void display_thread_hook(Display *display) {
    while(true) {
      display->draw();
      wait_us(display->delay_between_frames);
    }
  };
};

struct Game {
  uint16_t game_field[32][64];
  uint16_t neighbors[32][64];

  Game() {
    for(int x = 0; x < 32; x++) {
      for(int y = 0; y < 64; y++) {
	game_field[x][y] = 0;
      }
    }  

    game_field[15][20] = 1;
    game_field[15][21] = 1;
    game_field[15][22] = 1;
    game_field[16][22] = 1;
    game_field[14][21] = 1;


    // game_field[15][20] = 1;
    // game_field[15][21] = 1;
    // game_field[15][22] = 1;
    // game_field[16][22] = 1;
    // game_field[17][21] = 1;
  
  
    // for(int y = 15; y < 45; y++) {
    //   game_field[15][y] = 1;
    // }
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
	  y = y0 + 64;
	  neighbors[(x+1)%32][y%64] += 1;
	  neighbors[(x+1)%32][(y+1)%64] += 1;
	  neighbors[(x+1)%32][(y-1)%64] += 1;
	  neighbors[x%32][(y+1)%64] += 1;
	  neighbors[x%32][(y-1)%64] += 1;
	  neighbors[(x-1)%32][y%64] += 1;
	  neighbors[(x-1)%32][(y+1)%64] += 1;
	  neighbors[(x-1)%32][(y-1)%64] += 1;
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

  void draw(Display *display) {
    for(int x = 0; x < 32; x++) {
      for(int y = 0; y < 64; y++) {
	display->set_pixel(x,y,game_field[x][y]);
      }
    }   
  }
};

Game game;

int main() {
  Display display;
  display.start();

  while(true) {
    game.draw(&display);
    wait_ms(1000);
    game.step();
  }
}

//static Display display;

// int main()
// {
//   display_thread.start(display.loop);
//   setup();
//   loop();
//   init_game();

//   int s = 0;
  
//   while(1) {
//     if (s == 400){
//       s = 0;
//       game_field[5][50] = 1;
//       game_field[5][51] = 1;
//       game_field[5][52] = 1;
//       game_field[6][52] = 1;
//       game_field[7][51] = 1;
      
//       //      init_game();
//     }
//     draw_game();
//     wait_ms(50);
//     step();
//     s++;
//   }
// }

// void loop() {



// }

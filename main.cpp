#include "mbed.h"
#include <vector>
#include "display.h"

struct Game {

  std::vector<std::vector<uint8_t>> game_field;
  std::vector<std::vector<uint8_t>> neighbors;

  Game() {
    game_field = std::vector<std::vector<uint8_t>> (32, std::vector<uint8_t>(64, 0));
    neighbors  = std::vector<std::vector<uint8_t>> (32, std::vector<uint8_t>(64, 0));
   

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

  void draw(Display *display) {
    for(int x = 0; x < 32; x++) {
      for(int y = 0; y < 64; y++) {
	display->set_pixel(x,y,game_field[x][y]);
      }
    }   
  }
};

Game game;
Display display;

int main() {
  display.start();

  while(true) {
    for(int i = 0; i < 400; i++){
      game.draw(&display);
      wait_ms(10);
      game.step();
    }
    game.game_field[10][10] = 1;
    game.game_field[10][11] = 1;
    game.game_field[10][12] = 1;
    game.game_field[11][12] = 1;
    game.game_field[12][11] = 1;
  }
}

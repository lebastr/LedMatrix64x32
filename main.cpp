#include "mbed.h"
#include <vector>
#include "display.h"

struct Game {
  const int width = 63;
  const int height = 64;
  
  std::vector<std::vector<uint8_t>> game_field;
  std::vector<std::vector<uint8_t>> neighbors;

  Game() {
    game_field = std::vector<std::vector<uint8_t>> (height, std::vector<uint8_t>(width, 0));
    neighbors  = std::vector<std::vector<uint8_t>> (height, std::vector<uint8_t>(width, 0));
   

    for(int x = 0; x < height; x++) {
      for(int y = 0; y < width; y++) {
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
    for(int x = 0; x < height; x++) {
      for(int y = 0; y < width; y++) {
	neighbors[x][y] = 0;
      }
    }

    for(uint16_t x0 = 0; x0 < height; x0++) {
      for(uint16_t y0 = 0; y0 < width; y0++) {
	if(game_field[x0][y0] == 1) {
	  x = x0 + height;
	  y = y0 + width;
	  neighbors[(x+1)%height][y%width] += 1;
	  neighbors[(x+1)%height][(y+1)%width] += 1;
	  neighbors[(x+1)%height][(y-1)%width] += 1;
	  neighbors[x%height][(y+1)%width] += 1;
	  neighbors[x%height][(y-1)%width] += 1;
	  neighbors[(x-1)%height][y%width] += 1;
	  neighbors[(x-1)%height][(y+1)%width] += 1;
	  neighbors[(x-1)%height][(y-1)%width] += 1;
	}
      }
    }
    
    for(int x = 0; x < height; x++) {
      for(int y = 0; y < width; y++) {
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
    for(int x = 0; x < height; x++) {
      for(int y = 0; y < width; y++) {
	if(game_field[x][y] == 1){
	  display->set_pixel64x64(x,y, x % 7+1, 7 - y%7, 0);
	} else {
	  display->set_pixel64x64(x,y,0,0,0);
	}
      }
    }   
  }
};

Game game;
Display display;

int main() {
  int t = 0;
  display.start();
  //  display.clear();
  while(true) {
    for(int i = 0; i < 400; i++){
      game.draw(&display);
      //   wait_ms(10);
      game.step();
    }
    game.game_field[10][10] = 1;
    game.game_field[10][11] = 1;
    game.game_field[10][12] = 1;
    game.game_field[11][12] = 1;
    game.game_field[12][11] = 1;
  }
}

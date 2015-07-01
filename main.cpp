/*This Program is made of 1040 lines of pure C++ code*/

#include "includes.hpp"

int main() {
	srand(time(NULL));
	GameEngine game;
	SDL_Event e;
	Uint32 curtime;
	while(game.getState()!=::Quit) {
		curtime=SDL_GetTicks();
		while(SDL_PollEvent(&e)) {
			game.HandleEvent(e);
		}
		game.Update();
		game.Draw();
		while(SDL_GetTicks()-curtime<16) {
			SDL_Delay(1);
		}
	}
	return 0;
}
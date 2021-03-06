#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstring>

#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#elif defined __unix__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#elif defined __APPLE__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

#endif

#include "zombies_vs_soldier.hpp"
#include "SDL_Class.hpp"
#include "bullet.hpp"
#include "zombie.hpp"
#include "soldier.hpp"
#include "scores.hpp"
#include "menu.hpp"
#include "game.hpp"

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

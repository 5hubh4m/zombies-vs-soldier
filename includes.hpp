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


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstring>

SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer=NULL;
TTF_Font* gFont, *gFontSmall;

#include "SDL_Class.hpp"

Texture gBullet, gSoldier, gZombie, gText, gTile, gPlay, gScore, gExit, gTitle, gPause, gPlayButton, gVolume;
Mix_Chunk* gPain=NULL;
Mix_Chunk* gDie=NULL;
Mix_Chunk* gShoot=NULL;
Mix_Chunk* gGrunt=NULL;
Mix_Chunk* gGrimm=NULL;
Mix_Chunk* gAction=NULL;
Mix_Chunk* gEat=NULL;

#include "defines.hpp"
#include "scores.hpp"
#include "bullet.hpp"
#include "zombie.hpp"
#include "soldier.hpp"
#include "menu.hpp"
#include "game.hpp"
#include "functions.hpp"

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

Bullet::Bullet(int _x, int _y, double rad) {
  Pos.w=gBullet.getWidth();
  Pos.h=gBullet.getHeight();
  Pos.x=_x;
  Pos.y=_y;
  Vel.x=15*cos(rad);
  Vel.y=15*sin(rad);
  state=Travelling;
}

void Bullet::Update() {
  if(Pos.x>0 && Pos.x<SCREEN_WIDTH-Pos.w && Pos.y>0 && Pos.y<SCREEN_HEIGHT-Pos.h) {
    Pos.x+=Vel.x;
    Pos.y-=Vel.y;
  }
  else {
    state=Struck;
  }
}

BulletState Bullet::getState() {
  return state;
}

SDL_Point Bullet::getPos() {
  return {Pos.x, Pos.y};
}

SDL_Rect* Bullet::getBoundingBox() {
  return &Pos;
}

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

Menu::Menu() {
  scale=0.5;
}

void Menu::Init() {
  Mix_HaltChannel(-1);
  Mix_PlayChannel(-1, gGrimm, -1);
  Exit={(SCREEN_WIDTH-gExit.getWidth())/2, SCREEN_HEIGHT-gExit.getHeight(), gExit.getWidth(), gExit.getHeight()};
  Score={(SCREEN_WIDTH-gScore.getWidth())/2, Exit.y-gScore.getHeight(), gScore.getWidth(), gScore.getHeight()};
  Play={(SCREEN_WIDTH-gPlay.getWidth())/2, Score.y-gPlay.getHeight(), gPlay.getWidth(), gPlay.getHeight()};
  Title={(SCREEN_WIDTH-gTitle.getWidth())/2, 0, gTitle.getHeight(), gTitle.getWidth()};
  state=::Play;
}

void Menu::Update(int mouseX, int mouseY) {
  SDL_Rect a={mouseX, mouseY, 1, 1};
  if(Collide(&a, &Play)) {
    state=::Play;
  }
  else if(Collide(&a, &Score)) {
    state=HighScore;
  }
  else if(Collide(&a, &Exit)) {
    state=::Exit;
  }
}

void Menu::Render() {
  switch(state) {
  case ::Play:
    gTitle.render(Title.x, Title.y);
    gPlay.render(Play.x, Play.y);
    gScore.render(Score.x+gScore.getWidth()/4, Score.y+gScore.getHeight()/2, 0.5);
    gExit.render(Exit.x+gExit.getWidth()/4, Exit.y+gExit.getHeight()/2, 0.5);
    break;
  case HighScore:
    gTitle.render(Title.x, Title.y);
    gPlay.render(Play.x+gPlay.getWidth()/4, Play.y+gPlay.getHeight()/2, 0.5);
    gScore.render(Score.x, Score.y);
    gExit.render(Exit.x+gExit.getWidth()/4, Exit.y+gExit.getHeight()/2, 0.5);
    break;
  case ::Exit:
    gTitle.render(Title.x, Title.y);
    gPlay.render(Play.x+gPlay.getWidth()/4, Play.y+gPlay.getHeight()/2, 0.5);
    gScore.render(Score.x+gScore.getWidth()/4, Score.y+gScore.getHeight()/2, 0.5);
    gExit.render(Exit.x, Exit.y);
    break;
  }
}

MenuState Menu::getState() {
  return state;
}

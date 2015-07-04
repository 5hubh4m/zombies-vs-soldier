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

Score::Score() {
  head=-1;
  for(int i=0; i<14; i++) {
    scores[i]=-1;
  }
  fileread();
}

void Score::filewrite() {
  std::ofstream file;
  if(head>-1) {
    if(file.is_open()) {
      file.close();
    }
    file.open(FILE_NAME, std::ios::trunc | std::ios::binary);
    file.write((char *)this, sizeof(Score));
    file.close();
  }
}

void Score::fileread() {
  std::ifstream file;
  file.open(FILE_NAME, std::ios::in | std::ios::binary);
  if(file.is_open()) {
    file.read((char *)this, sizeof(Score));
  }
  file.close();
  sortscore();
}

void Score::addscore(int s) {
  sortscore();
  if(head<13) {
    scores[++head]=s;
  }
  else {
    if(s>scores[0] && s>0) {
      scores[0]=s;
    }
  }
  sortscore();
}

void Score::sortscore(void) {
  int temp;
  if(head>0) {
    for(int i=0; i<=head; i++) {
      for(int j=0; j<=head-1; j++) {
        if(scores[j]<scores[j+1]) {
          temp=scores[j+1];
          scores[j+1]=scores[j];
          scores[j]=temp;
        }
      }
    }
  }
}

void Score::Render(void) {
  char str[20], str2[10];
  int w=0;;
  strcpy(str, "High Scores!");
  gText.loadFromRenderedText(gFont, str, {static_cast<Uint8>(rand()%128+128), static_cast<Uint8>(rand()%128+128), static_cast<Uint8>(rand()%128+128), 0xFF}, 50);
  gText.render((SCREEN_WIDTH-gText.getWidth())/2, w);
  w+=gText.getHeight();
  if(head>-1) {
    for(int i=0; i<=head; i++) {
      int2str(i+1, str2);
      strcpy(str, ". ");
      strcat(str2, str);
      int2str(scores[i], str);
      strcat(str2, str);
      gText.loadFromRenderedText(gFontSmall, str2, {0xFF, 0xFF, 0xFF, 0xFF}, 20);
      gText.render((SCREEN_WIDTH-gText.getWidth())/2, w);
      w+=gText.getHeight();
    }
  }
}

int Score::gethead(void) {
  return head;
}

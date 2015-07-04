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

SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer=NULL;

TTF_Font* gFont;
TTF_Font* gFontSmall;

Texture gBullet;
Texture gSoldier;
Texture gZombie;
Texture gText;
Texture gTile;
Texture gPlay;
Texture gScore;
Texture gExit;
Texture gTitle;
Texture gPause;
Texture gPlayButton;
Texture gVolume;

Mix_Chunk* gPain=NULL;
Mix_Chunk* gDie=NULL;
Mix_Chunk* gShoot=NULL;
Mix_Chunk* gGrunt=NULL;
Mix_Chunk* gGrimm=NULL;
Mix_Chunk* gAction=NULL;
Mix_Chunk* gEat=NULL;

Texture::Texture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Texture::~Texture() {
  free();
}

bool Texture::loadFromFile(std::string path) {
  free();
  SDL_Texture* newTexture=NULL;
  SDL_Surface* loadedSurface=IMG_Load(path.c_str());
  if(loadedSurface==NULL) {
    std::cout<<"Unable to load image "<<path.c_str()<<"! SDL_image Error: "<<IMG_GetError()<<std::endl;
  }
  else {
    newTexture=SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(newTexture==NULL) {
      std::cout<<"Unable to create texture from "<<path.c_str()<<"! SDL Error: "<<SDL_GetError()<<std::endl;
    }
    else {
      mWidth=loadedSurface->w;
      mHeight=loadedSurface->h;
    }
    SDL_FreeSurface(loadedSurface);
  }
  mTexture=newTexture;
  return mTexture!=NULL;
}

bool Texture::loadFromRenderedText(TTF_Font* gFont, char* textureText, SDL_Color textColor, int size) {
  if(gFont==NULL) {
    std::cout<<"Unable to Open Font! TTF Error: "<<SDL_GetError()<<std::endl;
    return false;
  }
  else {
    free();
    SDL_Surface* textSurface=TTF_RenderText_Blended(gFont, textureText, textColor);
    if(textSurface!=NULL) {
      mTexture=SDL_CreateTextureFromSurface(gRenderer, textSurface);
      if(mTexture==NULL) {
        std::cout<<"Unable to create texture from rendered text! SDL Error: "<<SDL_GetError()<<std::endl;
      }
      else {
        mWidth = textSurface->w;
        mHeight = textSurface->h;
      }
      SDL_FreeSurface(textSurface);
    }
    else {
      std::cout<<"Unable to render text surface! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
    }
    return mTexture!=NULL;
  }
}

void Texture::free() {
  if(mTexture!= NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(int x, int y, float scale, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
  SDL_Rect renderQuad={x, y, static_cast<int>(mWidth*scale), static_cast<int>(mHeight*scale)};
  if(clip!=NULL) {
    renderQuad.w=clip->w;
    renderQuad.h=clip->h;
  }
  SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() {
  return mWidth;
}

int Texture::getHeight() {
  return mHeight;
}

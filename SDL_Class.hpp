#ifndef SDL_CLASS_HPP
#define SDL_CLASS_HPP

class Texture {
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
public:
	Texture();
	~Texture();
	bool loadFromFile(std::string path);
	bool loadFromRenderedText(TTF_Font* gFont, char* textureText, SDL_Color textColor, int size);
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, float scale=1.0, SDL_Rect* clip=NULL, double angle=0.0, SDL_Point* center=NULL, SDL_RendererFlip flip=SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
};

extern Texture gBullet;
extern Texture gSoldier;
extern Texture gZombie;
extern Texture gText;
extern Texture gTile;
extern Texture gPlay;
extern Texture gScore;
extern Texture gExit;
extern Texture gTitle;
extern Texture gPause;
extern Texture gPlayButton;
extern Texture gVolume;

#endif

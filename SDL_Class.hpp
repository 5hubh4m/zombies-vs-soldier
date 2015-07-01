class Texture {
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
  public:
	Texture() {
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
	~Texture() {
		free();
	}
	bool loadFromFile(std::string path) {
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
	bool loadFromRenderedText(TTF_Font* gFont, char* textureText, SDL_Color textColor, int size) {
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
	void free() {
		if(mTexture!= NULL) {
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
			mWidth = 0;
			mHeight = 0;
		}
	}
	void setColor(Uint8 red, Uint8 green, Uint8 blue) {
		SDL_SetTextureColorMod(mTexture, red, green, blue);
	}
	void setBlendMode(SDL_BlendMode blending) {
		SDL_SetTextureBlendMode(mTexture, blending);
	}
	void setAlpha(Uint8 alpha) {
		SDL_SetTextureAlphaMod(mTexture, alpha);
	}
	void render(int x, int y, float scale=1.0, SDL_Rect* clip=NULL, double angle=0.0, SDL_Point* center=NULL, SDL_RendererFlip flip=SDL_FLIP_NONE) {
		SDL_Rect renderQuad={x, y, static_cast<int>(mWidth*scale), static_cast<int>(mHeight*scale)};
		if(clip!=NULL) {
			renderQuad.w=clip->w;
			renderQuad.h=clip->h;
		}
		SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
	}
	int getWidth() {
		return mWidth;
	}
	int getHeight() {
		return mHeight;
	}
};
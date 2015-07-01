class GameEngine {
	class Menu menu;
	Soldier Sol;
	std::vector<Zombie> zombies;
	int mouseX, mouseY;
	Uint32 frame;
	int score, fact, killedzombies;
	GameState state;
	Score scores;
	SDL_Rect tileclip;
  public:
  	GameEngine() {
  		if(!Init()) {
  			std::cout<<"Error(s)! Unable to complete initialization!"<<std::endl;
  			Cleanup();
  			Quit();
  		}
  	}
  	~GameEngine() {
  		Cleanup();
  		Quit();
  	}
  	void Reset() {
  		frame=0;
		score=0;
		killedzombies=0;
		fact=300;
		state=::Menu;
		zombies.clear();
		Sol.Init();
		menu.Init();
		tileclip.x=(rand()%(gTile.getWidth()/100))*100;
		tileclip.y=0;
		tileclip.w=100;
		tileclip.h=100;
  	}
	bool Init() {
		bool success=true;
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0) {
			std::cout<<"SDL could not initialize! SDL Error: "<<SDL_GetError()<<std::endl;
			success=false;
		}
		else {
			if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
				std::cout<<"Warning: Linear texture filtering not enabled!";
			}
			gWindow=SDL_CreateWindow("Zombies v/s Soldier",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									SCREEN_WIDTH,
									SCREEN_HEIGHT,
									SDL_WINDOW_SHOWN);
			if(gWindow==NULL) {
				std::cout<<"Window could not be created! SDL Error: "<<SDL_GetError()<<std::endl;
				success=false;
			}
			else {
				gRenderer=SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
				if(gRenderer==NULL) {
					std::cout<<"Renderer could not be created! SDL Error: "<<SDL_GetError()<<std::endl;
					success=false;
				}
				else {
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
					int imgFlags = IMG_INIT_PNG;
					if(!(IMG_Init(imgFlags) & imgFlags)) {
						std::cout<<"SDL_image could not initialize! SDL_image Error: "<<IMG_GetError()<<std::endl;
						success=false;
					}
					if(TTF_Init()<0) {
						std::cout<<"SDL_ttf could not initialize! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
						success=false;
					}
					gFont=TTF_OpenFont(FONT_FILE, 50);
					gFontSmall=TTF_OpenFont(FONT_FILE, 30);
					if(gFont==NULL || gFontSmall==NULL) {
						std::cout<<"SDL_ttf could not initialize! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
						success=false;
					}
					else {
						TTF_SetFontHinting(gFont, TTF_HINTING_LIGHT);
						TTF_SetFontHinting(gFontSmall, TTF_HINTING_LIGHT);
					}
					if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0) {
						std::cout<<"SDL_mixed could not initialize! SDL_mixer Error: "<<Mix_GetError()<<std::endl;
						success=false;
					}
					gGrimm=Mix_LoadWAV(GRIMM_FILE);
					gAction=Mix_LoadWAV(ACTION_FILE);
					gShoot=Mix_LoadWAV(SHOOT_FILE);
					gDie=Mix_LoadWAV(DIE_FILE);
					gGrunt=Mix_LoadWAV(GRUNT_FILE);
					gPain=Mix_LoadWAV(PAIN_FILE);
					gEat=Mix_LoadWAV(EAT_FILE);
					if(gShoot==NULL 
						|| gDie==NULL 
						|| gGrunt==NULL 
						|| gPain==NULL 
						|| gEat==NULL 
						|| gGrimm==NULL 
						|| gAction==NULL) {
						std::cout<<"Unable to load files!"<<std::endl;
						success=false;
					}
					else {
						Mix_Volume(-1, MIX_MAX_VOLUME);
					}
					if(!(gSoldier.loadFromFile(SOLDIER_FILE)
						&& gBullet.loadFromFile(BULLET_FILE)
						&& gZombie.loadFromFile(ZOMBIE_FILE)
						&& gTile.loadFromFile(TILE_FILE)
						&& gPlay.loadFromFile(PLAY_FILE)
						&& gScore.loadFromFile(SCORE_FILE)
						&& gExit.loadFromFile(EXIT_FILE)
						&& gTitle.loadFromFile(TITLE_FILE)
						&& gPause.loadFromFile(PAUSE_FILE)
						&& gPlayButton.loadFromFile(PLAYBUTTON_FILE)
						&& gVolume.loadFromFile(VOLUME_FILE))) {
						std::cout<<"Unable to load file!"<<std::endl;
						success=false;
					}
				}
			}
		}
		Reset();
		return success;
	}
	void Cleanup() {
		gSoldier.free();
		gBullet.free();
		gZombie.free();
		gText.free();
		gTile.free();
		gPlay.free();
		gScore.free();
		gExit.free();
		gPlayButton.free();
		gPause.free();
		gVolume.free();
		Mix_FreeChunk(gGrunt);
	    Mix_FreeChunk(gDie);
	    Mix_FreeChunk(gPain);
	    Mix_FreeChunk(gShoot);
	    Mix_FreeChunk(gGrimm);
	    Mix_FreeChunk(gAction);
	    gShoot=NULL;
	    gGrunt=NULL;
	    gPain=NULL;
	    gDie=NULL;
	    gGrimm=NULL;
	    gAction=NULL;
		TTF_CloseFont(gFont);
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gFont=NULL;
		gWindow=NULL;
		gRenderer=NULL;
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
		TTF_Quit();
	}
	void Spawn() {
		zombies.push_back(Zombie());
	}
	void HandleEvent(SDL_Event e) {
		SDL_Rect a, b, c;
		char str[20];
		switch(state) {
			case Menu: {
				switch(e.type) {
					case SDL_QUIT:
						Quit();
						break;
					case SDL_MOUSEMOTION:
						mouseX=e.motion.x;
						mouseY=e.motion.y;
						break;
					case SDL_MOUSEBUTTONDOWN:
						mouseX=e.motion.x;
						mouseY=e.motion.y;
						if(e.button.button==SDL_BUTTON_LEFT) {
							switch(menu.getState()) {
								case Play:
									Reset();
									state=GameRunning;
									break;
								case HighScore:
									state=ShowingScore;
									break;
								case Exit:
									state=::Quit;
							}
						}
						break;
				}
				break;
			}
			case GameRunning: {
				switch(e.type) {
					case SDL_QUIT:
						Quit();
						break;
					case SDL_MOUSEMOTION:
						mouseX=e.motion.x;
						mouseY=e.motion.y;
						break;
					case SDL_MOUSEBUTTONDOWN:
						mouseX=e.motion.x;
						mouseY=e.motion.y;
						if(e.button.button==SDL_BUTTON_LEFT) {
							a={mouseX, mouseY, 1, 1};
							b={0, SCREEN_HEIGHT-gPause.getHeight(), gPause.getWidth(), gPause.getHeight()};
							if(Collide(&a, &b)) {
								state=Pause;
							}
							else {
								Sol.Fire();
							}
						}
						break;
				}
				break;
			}
			case Pause: {
				switch(e.type) {
					case SDL_QUIT:
						Quit();
						break;
					case SDL_MOUSEBUTTONDOWN:
						mouseX=e.motion.x;
						mouseY=e.motion.y;
						a={mouseX, mouseY, 1, 1};
						strcpy(str, "Back to Menu!");
						gText.loadFromRenderedText(gFont, str, {0x00, 0x00, 0x00, 0x00}, 20);
						b={(SCREEN_WIDTH-gPlayButton.getWidth())/2,
								(SCREEN_HEIGHT-gPlayButton.getHeight())/2,
								gPlayButton.getWidth(),
								gPlayButton.getHeight()};
						c={(SCREEN_WIDTH-gText.getWidth())/2,
								b.y+gPlayButton.getHeight(),
								gText.getWidth(),
								gText.getHeight()};
						if(e.button.button==SDL_BUTTON_LEFT) {
							if(Collide(&a, &b)) {
								state=GameRunning;
							}
							else if(Collide(&a, &c)) {
								scores.addscore(score);
								state=GameOver;
							}
						}
						break;
				}
				break;
			}
			case ShowingScore: {
				switch(e.type) {
					case SDL_QUIT:
						Quit();
						break;
					case SDL_MOUSEBUTTONDOWN:
						state=::Menu;
						break;
				}
			}
			case GameOver: {
				switch(e.type) {
					case SDL_QUIT:
						Quit();
						break;
					case SDL_MOUSEBUTTONDOWN:
						state=::Menu;
						break;
				}
			}
		}
	}
	void Update() {
		switch(state) {
			case ::Menu:
				menu.Update(mouseX, mouseY);
				break;
			case GameRunning:
				if(Sol.getSolState()!=SolDead) {
					if(frame%fact==0) {
						Spawn();
					}
					Sol.Update(mouseX, mouseY, &zombies);
					if(!zombies.empty()) {
						for(std::vector<Zombie>::iterator it=zombies.begin(); it!=zombies.end();) {
							it->Update(Sol.getBulletVector(), Sol.getRect(), &zombies);
							if(it->getZomState()==Disapp) {
								zombies.erase(it);
								if(it->getType()) {
									score+=5;
								}
								else {
									score+=10;
								}
								killedzombies++;
								if(killedzombies%4==0) {
									if(fact>60) {
										fact-=30;
									}
								}
							}
							else {
								it++;
							}
						}
					}
				}
				else {
					Mix_PlayChannel(-1, gDie, 0);
					if(frame%60==0) {
						state=GameOver;
						scores.addscore(score);
					}
				}
				break;
			case ShowingScore:
				break;
			case ::Quit:
				Quit();
		}
		frame++;
	}
	void Draw() {
		SDL_RenderClear(gRenderer);
		char str[20], str2[5];
		int w;
		switch(state) {
			case ::Menu: {
				menu.Render();
				break;
			}
			case Pause: {
				gSoldier.setAlpha(0x80);
				gBullet.setAlpha(0x80);
				gZombie.setAlpha(0x80);
				gText.setAlpha(0x80);
				gTile.setAlpha(0x80);
				renderGame();
				gPlayButton.render((SCREEN_WIDTH-gPlayButton.getWidth())/2, (SCREEN_HEIGHT-gPlayButton.getHeight())/2);
				strcpy(str, "Back to Menu!");
				gText.loadFromRenderedText(gFont, str, {0xFF, 0xFF, 0x00, 0xFF}, 20);
				gText.render((SCREEN_WIDTH-gText.getWidth())/2
							,(SCREEN_HEIGHT-gPlayButton.getHeight())/2+gPlayButton.getHeight());
				gSoldier.setAlpha(0xFF);
				gBullet.setAlpha(0xFF);
				gZombie.setAlpha(0xFF);
				gText.setAlpha(0xFF);
				gTile.setAlpha(0xFF);
				break;
			}
			case GameRunning: {
				renderGame();
				break;
			}
			case ::ShowingScore: {
				scores.Render();
				break;
			}
			case GameOver: {
				strcpy(str, "Game Over!");
				gText.loadFromRenderedText(gFont, str,
					{static_cast<Uint8>(rand()%128+128),
					static_cast<Uint8>(rand()%128+128),
					static_cast<Uint8>(rand()%128+128),
					0xFF}, 50);
				w=(SCREEN_HEIGHT-gText.getHeight())/2;
				gText.render((SCREEN_WIDTH-gText.getWidth())/2, w);
				w+=gText.getHeight();
				strcpy(str, "Score: ");
				int2str(score, str2);
				strcat(str, str2);
				gText.loadFromRenderedText(gFont, str, 
					{static_cast<Uint8>(rand()%128+128),
					static_cast<Uint8>(rand()%128+128),
					static_cast<Uint8>(rand()%128+128),
					0xFF}, 50);
				gText.render((SCREEN_WIDTH-gText.getWidth())/2, w);
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderPresent(gRenderer);
	}
	void Quit() {
		state=::Quit;
		scores.filewrite();
		Cleanup();
		exit(0);
	}
	void renderGame() {
		for(int i=0; i<SCREEN_WIDTH; i+=100) {
			for(int j=0; j<SCREEN_HEIGHT; j+=100) {
				gTile.render(i, j, 1, &tileclip);
			}
		}
		gPause.render(0, SCREEN_HEIGHT-gPause.getHeight());
		char str[20];
		strcpy(str, " Score: ");
		gText.loadFromRenderedText(gFont, str, {0xFF, 0xFF, 0x00, 0x80}, 40);
		gText.render(0, 0);
		int w=gText.getWidth();
		int2str(score, str);
		gText.loadFromRenderedText(gFont, str, {0xFF, 0xFF, 0xFF, 0x80}, 40);
		gText.render(w, 0);
		if(Sol.getSolState()==SolDead) {
			Sol.Render();
		}
		if(!zombies.empty()) {
			for(std::vector<Zombie>::iterator it=zombies.begin(); it!=zombies.end(); it++) {
				it->Render();
			}
		}
		if(Sol.getSolState()!=SolDead) {
			Sol.Render();
		}
		int2str(killedzombies, str);
		strcat(str, " ");
		gText.loadFromRenderedText(gFont, str, {0xFF, 0xFF, 0xFF, 0x80}, 40);
		w=gText.getWidth();
		gText.render(SCREEN_WIDTH-gText.getWidth(), SCREEN_HEIGHT-gText.getHeight());
		strcpy(str, " Zombies Killed: ");
		gText.loadFromRenderedText(gFont, str, {0x00, 0xFF, 0xFF, 0x80}, 40);
		gText.render(SCREEN_WIDTH-w-gText.getWidth(), SCREEN_HEIGHT-gText.getHeight());
	}
	GameState getState() {
		return state;
	}
};
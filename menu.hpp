class Menu {
	MenuState state;
	SDL_Rect Play, Score, Exit, Title;
	float scale=0.5;
  public:
  	void Init() {
  		Mix_HaltChannel(-1);
  		Mix_PlayChannel(-1, gGrimm, -1);
  		Exit={(SCREEN_WIDTH-gExit.getWidth())/2, SCREEN_HEIGHT-gExit.getHeight(), gExit.getWidth(), gExit.getHeight()};
  		Score={(SCREEN_WIDTH-gScore.getWidth())/2, Exit.y-gScore.getHeight(), gScore.getWidth(), gScore.getHeight()};
  		Play={(SCREEN_WIDTH-gPlay.getWidth())/2, Score.y-gPlay.getHeight(), gPlay.getWidth(), gPlay.getHeight()};
		Title={(SCREEN_WIDTH-gTitle.getWidth())/2, 0, gTitle.getHeight(), gTitle.getWidth()};
		state=::Play;
	}
	void Update(int mouseX, int mouseY) {
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
  	void Render() {
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
  	MenuState getState() {
  		return state;
  	}
};
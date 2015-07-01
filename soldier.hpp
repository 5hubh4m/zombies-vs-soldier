class Soldier {
	SDL_Point center;
	SDL_Rect Pos, TestPos;
	Vector2Df Vel; 
	int frame, anim;
	float health;
	double rad, deadangle;
	bool musflag;
	SDL_Rect Clip[4];
	SoldierState state;
	std::vector<Bullet> bullets;
	int x, y;
  public:
  	void Init() {
  		state=Walking;
  		bullets.clear();
  		bullets.clear();
		Pos.w=gSoldier.getWidth()/4;
		Pos.h=gSoldier.getHeight();
		Pos.y=(SCREEN_HEIGHT-Pos.h)/2;
		Pos.x=(SCREEN_WIDTH-Pos.w)/2;
		TestPos=Pos;
		Clip[0].x=0;
		Clip[0].y=0;
		Clip[0].w=Pos.w;
		Clip[0].h=Pos.h;
		Clip[2].x=Pos.w;
		Clip[2].y=0;
		Clip[2].w=Pos.w;
		Clip[2].h=Pos.h;
		Clip[1].x=2*Pos.w;
		Clip[1].y=0;
		Clip[1].w=Pos.w;
		Clip[1].h=Pos.h;
		Clip[3].x=3*Pos.w;
		Clip[3].y=0;
		Clip[3].w=Pos.w;
		Clip[3].h=Pos.h;
		anim=0;
		frame=0;
		health=100;
		center={Pos.w/2, Pos.h/2};
		musflag=true;
	}
	void Update(int mouseX, int mouseY, std::vector<Zombie>* zombies) {
		bool collide=false;
		x=mouseX;
		y=mouseY;
		rad=atan2(y-Pos.y-(Pos.h/2), Pos.x+(Pos.w/2)-x)+PI;
		Vel.x=std::abs(5*cos(rad));
		Vel.y=std::abs(5*sin(rad));
		if(state!=SolDead) {
			if(!zombies->empty()) {
				for(std::vector<Zombie>::iterator it=zombies->begin(); it!=zombies->end(); it++) {
					if(Collide(&TestPos, it->getRect()) && it->getZomState()!=ZomDead) {
						collide=true;
						health-=0.1;
						if(health<33 && musflag) {
							Mix_HaltChannel(-1);
							Mix_PlayChannel(-1, gAction, -1);
							musflag=false;
						}
						if(frame%(rand()%120+1)==0) {
							Mix_PlayChannel(-1, gPain, 0);
						}
						if(health<=0) {
							state=SolDead;
							deadangle=rand()%360;
						}
						break;
					}
				}
			}
		}
		if(health>0) {
			if(!(abs(Pos.x+Pos.w/2-x)<50 && abs(Pos.y+Pos.h/2-y)<50)) {
				state=Walking;
				TestMove();
				if(!collide) {
					if(x>Pos.x) {
						Pos.x+=(Pos.x+ceil(Vel.x)<SCREEN_WIDTH-Pos.w)?ceil(Vel.x):0;
					}
					else {
						Pos.x-=(Pos.x-ceil(Vel.x)>0)?ceil(Vel.x):0;
					}
					if(y>Pos.y) {
						Pos.y+=(Pos.y+ceil(Vel.y)<SCREEN_HEIGHT-Pos.h)?ceil(Vel.y):0;
					}
					else {
						Pos.y-=(Pos.y-ceil(Vel.y)>0)?ceil(Vel.y):0;
					}
				TestPos=Pos;
				}
			}
			else {
				state=Standing;
			}
		}
		for(int i=0; i<bullets.size(); i++) {
			if(bullets[i].getState()==Struck) {
				bullets.erase(bullets.begin()+i);
			}
		}
		for(int i=0; i<bullets.size(); i++) {
			bullets[i].Update();
		}
  	}
  	void Fire() {
  		Mix_PlayChannel(-1, gShoot, 0);
  		int _x, _y;
  		int mod=Pos.w/2-10;
  		_y=ceil(Pos.y+Pos.h/2-mod*sin(rad)+9*cos(rad));
  		_x=ceil(Pos.x+Pos.w/2+mod*cos(rad)+9*sin(rad));
  		bullets.push_back(Bullet(_x, _y, rad+(rand()%10-5)*PI/180));
  	}
  	void Render() {
  		frame++;
		for(int i=0; i<bullets.size(); i++) {
			gBullet.render(bullets[i].getPos().x, bullets[i].getPos().y);
		}
		if(state!=SolDead) {
			SDL_Rect fillRect={Pos.x, Pos.y-30, (int)health, 15};
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);        
			SDL_RenderFillRect(gRenderer, &fillRect);
			if(state==Walking) {
				if(frame%8==0) {
	  				anim=(anim+1)%3;
				}
				gSoldier.render(Pos.x, Pos.y, 1, &Clip[anim], 360-rad*(180/PI), &center, SDL_FLIP_NONE);
			}
			else if(state==Standing) {
				gSoldier.render(Pos.x, Pos.y, 1, &Clip[1], 360-rad*(180/PI), &center, SDL_FLIP_NONE);
			}
		}
		else {
			gSoldier.render(Pos.x, Pos.y, 1, &Clip[3], deadangle, &center, SDL_FLIP_NONE);
		}
  	}
  	SDL_Point getPos() {
  		return {Pos.x, Pos.y};
  	}
  	std::vector<Bullet>* getBulletVector() {
  		return &bullets;
  	}
  	int getHealth() {
  		return health;
  	}
  	SDL_Rect* getRect() {
  		return &Pos;
  	}
  	void TestMove() {
  		if(x>TestPos.x) {
			TestPos.x+=(TestPos.x+ceil(Vel.x)<SCREEN_WIDTH-TestPos.w)?ceil(Vel.x):0;
		}
		else {
			TestPos.x-=(TestPos.x-ceil(Vel.x)>0)?ceil(Vel.x):0;
		}
		if(y>TestPos.y) {
			TestPos.y+=(TestPos.y+ceil(Vel.y)<SCREEN_HEIGHT-TestPos.h)?ceil(Vel.y):0;
		}
		else {
			TestPos.y-=(TestPos.y-ceil(Vel.y)>0)?ceil(Vel.y):0;
		}
  	}
  	SoldierState getSolState() {
  		return state;
  	}
};
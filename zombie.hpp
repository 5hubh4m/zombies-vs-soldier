class Zombie {
	SDL_Point center;
	Vector2Df Vel; 
	int frame, anim, health, type;
	double rad, deadangle;
	SDL_Rect Clip[9], Pos;
	ZombieState state;
  public:
  	Zombie() {
  		type=rand()%2;
		Pos.w=gZombie.getWidth()/9;
		Pos.h=gZombie.getHeight()/2;
		Vel.x=0;
		Vel.y=0;
		for(int i=0; i<9; i++) {
			Clip[i].y=type*Pos.h;
			Clip[i].x=i*Pos.w;
			Clip[i].w=Pos.w;
			Clip[i].h=Pos.h;
		}
		rad=(rand()%360)*(PI/180);
		Pos.x=(rand()%2)?(-rand()%100):(SCREEN_WIDTH+rand()%100);
		Pos.y=(rand()%2)?(-rand()%100):(SCREEN_HEIGHT+rand()%100);
		anim=0;
		frame=0;
		health=100;
		state=Alive;
		center={Pos.w/2, Pos.h/2};
	}
	void Update(std::vector<Bullet>* bullets, SDL_Rect* SolPos, std::vector<Zombie>* zombies) {
		Vector2Df  v2={0, 0}, v4={0, 0};
		int c=0;
		SDL_Point cPos={0, 0};
		std::vector<Zombie>::iterator t;
		bool collide=false;
		int x=SolPos->x;
		int y=SolPos->y;
		SDL_Point a, b;
		rad=atan2(y-Pos.y-(Pos.h/2), Pos.x+(Pos.w/2)-x)+PI;
		if(state==Alive) {
			if(frame%((rand())%600+180)==0) {
				Mix_PlayChannel(-1, gGrunt, 0);
			}
			if(!zombies->empty()) {
				for(std::vector<Zombie>::iterator it=zombies->begin(); it!=zombies->end(); it++) {
					if(&(*it)!=this && it->getZomState()==Alive) {
						if(distance({Pos.x, Pos.y}, {it->getPos().x, it->getPos().y})<64) {
							v2.x-=5*(it->getPos().x-Pos.x);
							v2.y-=5*(it->getPos().y-Pos.y);
						}
					}
					else {
						t=it;
					}
				}
			}
			v4.x=(SolPos->x-Pos.x)/100;
			v4.y=(SolPos->y-Pos.y)/100;
			Vel.x=Vel.x+v2.x+v4.x;
			Vel.y=Vel.y+v2.y+v4.y;
			if(sqrt(pow(Vel.x, 2)+pow(Vel.y, 2))>2) {
				Vel.x=(2*(Vel.x))/sqrt(pow(Vel.x, 2)+pow(Vel.y, 2));
				Vel.y=(2*(Vel.y))/sqrt(pow(Vel.x, 2)+pow(Vel.y, 2));
			}
			if(!Collide(SolPos, &Pos)) {
				Pos.x+=ceil(Vel.x);
				Pos.y+=ceil(Vel.y);
			}
			else {
				if(frame%(rand()%360+180)) {
					Mix_PlayChannel(-1, gEat, 0);
				}
			}
			for(int i=0; i<bullets->size();) {
				a=bullets->operator[](i).getPos();
				a.x+=5;
				a.y+=5;
				b.x=Pos.x+Pos.w/2;
				b.y=Pos.y+Pos.h/2;
				if(distance(a, b)<40) {
					health-=15+2*(!type);
					if(health<=0) {
						state=ZomDead;
						deadangle=rand()%135;
						frame=0;
					}
					bullets->erase(bullets->begin()+i);
				}
				else {
					i++;
				}
			}
		}
  	}
  	void Render() {
  		if(state==Alive) {
  			frame++;
  			if(frame%4==0) {
  				anim=(anim+1)%8;
  			}
  			SDL_Rect fillRect={Pos.x, Pos.y-15, (int)(health*0.25*(!(type)+2)), 5};
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);        
			SDL_RenderFillRect(gRenderer, &fillRect);
			gZombie.render(Pos.x, Pos.y, 1, &Clip[anim], 90-rad*(180/PI), &center, SDL_FLIP_NONE);
  		}
  		else if(frame<240) {
  			gZombie.render(Pos.x, Pos.y, 1, &Clip[8], deadangle, &center, SDL_FLIP_NONE);
  			frame++;
  		}
  		else {
  			state=Disapp;
  		}
  	}
  	SDL_Rect* getRect() {
  		return &Pos;
  	}
  	SDL_Point getPos() {
  		return {Pos.x, Pos.y};
	}
	Vector2Df getVel() {
		return Vel;
	}
  	ZombieState getZomState() {
  		return state;
  	}
  	int getType() {
  		return type;
  	}
  	int getHealth() {
  		return health;
  	}
};
class Bullet {
	SDL_Rect Pos;
	Vector2Df Vel;
	BulletState state;
  public:
  	Bullet(int _x, int _y, double rad) {
		Pos.w=gBullet.getWidth();
		Pos.h=gBullet.getHeight();
		Pos.x=_x;
		Pos.y=_y;
		Vel.x=15*cos(rad);
		Vel.y=15*sin(rad);
		state=Travelling;
	}
	void Update() {
		if(Pos.x>0 && Pos.x<SCREEN_WIDTH-Pos.w && Pos.y>0 && Pos.y<SCREEN_HEIGHT-Pos.h) {
			Pos.x+=Vel.x;
			Pos.y-=Vel.y;
		}
		else {
			state=Struck;
		}
  	}
  	BulletState getState() {
  		return state;
  	}
  	SDL_Point getPos() {
  		return {Pos.x, Pos.y};
  	}
  	SDL_Rect* getBoundingBox() {
  		return &Pos;
  	}
};
#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet {
	SDL_Rect Pos;
	Vector2Df Vel;
	BulletState state;
  public:
  Bullet(int, int, double);
	void Update();
  BulletState getState();
  SDL_Point getPos();
  SDL_Rect* getBoundingBox();
};

#endif

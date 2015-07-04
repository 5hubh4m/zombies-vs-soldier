#ifndef SOLDIER_HPP
#define SOLDIER_HPP

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
  void Init();
	void Update(int mouseX, int mouseY, std::vector<Zombie>* zombies);
	void Fire();
	void Render();
	SDL_Point getPos();
	std::vector<Bullet>* getBulletVector();
	int getHealth();
	SDL_Rect* getRect();
	void TestMove();
	SoldierState getSolState();
};

#endif

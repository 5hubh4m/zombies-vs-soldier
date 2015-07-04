#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

class Zombie {
	SDL_Point center;
	Vector2Df Vel;
	int frame, anim, health, type;
	double rad, deadangle;
	SDL_Rect Clip[9], Pos;
	ZombieState state;
public:
  Zombie();
	void Update(std::vector<Bullet>* bullets, SDL_Rect* SolPos, std::vector<Zombie>* zombies);
	void Render();
	SDL_Rect* getRect();
	SDL_Point getPos();
	Vector2Df getVel();
	ZombieState getZomState();
	int getType();
	int getHealth() ;
};

#endif

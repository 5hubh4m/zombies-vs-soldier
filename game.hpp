#ifndef GAME_HPP
#define GAME_HPP

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
	GameEngine();
	~GameEngine();
	void Reset();
	bool Init();
	void Cleanup();
	void Spawn();
	void HandleEvent(SDL_Event);
	void Update();
	void Draw();
	void Quit();
	void renderGame();
	GameState getState();
};

#endif

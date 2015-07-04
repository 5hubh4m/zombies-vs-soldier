#ifndef ZOMBIES_VS_SOLDIER_HPP
#define ZOMBIES_VS_SOLDIER_HPP

#define ZOMBIE_FILE "res/Zombie.png"
#define BULLET_FILE "res/Bullet.png"
#define SOLDIER_FILE "res/Soldier.png"
#define TILE_FILE "res/WallTile.png"
#define FONT_FILE "res/Impact.ttf"
#define SHOOT_FILE "res/Shoot.wav"
#define GRUNT_FILE "res/Grunt.wav"
#define PAIN_FILE "res/Pain.aif"
#define DIE_FILE "res/Die.wav"
#define EAT_FILE "res/Eat.aif"
#define GRIMM_FILE "res/Grimm.wav"
#define ACTION_FILE "res/Action.wav"
#define TITLE_FILE "res/Title.png"
#define PLAY_FILE "res/Play.png"
#define SCORE_FILE "res/HighScore.png"
#define EXIT_FILE "res/Exit.png"
#define FILE_NAME "scores.db"
#define PAUSE_FILE "res/Pause.png"
#define PLAYBUTTON_FILE "res/PlayButton.png"
#define VOLUME_FILE "res/Volume.png"

#define PI 3.14159265359

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

enum GameState {
	Menu, GameRunning, Pause, ShowingScore, GameOver, Quit
};

enum MenuState {
	Play, HighScore, Exit
};

enum SoldierState {
	Walking, Standing, SolDead
};

enum ZombieState {
	Alive, ZomDead, Disapp
};

enum BulletState {
	Travelling, Struck
};

struct Vector2Df {
		float x, y;
};

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern TTF_Font* gFont;
extern TTF_Font* gFontSmall;

extern Mix_Chunk* gPain;
extern Mix_Chunk* gDie;
extern Mix_Chunk* gShoot;
extern Mix_Chunk* gGrunt;
extern Mix_Chunk* gGrimm;
extern Mix_Chunk* gAction;
extern Mix_Chunk* gEat;

int distance(SDL_Point, SDL_Point);
bool Collide(SDL_Rect*, SDL_Rect*);
void int2str(int, char[]);

#endif

#ifndef MENU_HPP
#define MENU_HPP

class Menu {
	MenuState state;
	SDL_Rect Play, Score, Exit, Title;
	float scale;
public:
	Menu();
  void Init();
	void Update(int mouseX, int mouseY);
  void Render();
  MenuState getState();
};

#endif

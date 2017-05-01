#ifndef GAME_H
#define GAME_H

class Console;

class Game
{
	public:
		Game(Console*);
		virtual ~Game();

		virtual void init();
		virtual void update();
		virtual void render();
		virtual void quit();

    virtual void menu_init();
    virtual void menu_update();
    virtual void menu_render();
    virtual void menu_quit();
    
	protected:
		Console* console = nullptr;
};

#endif

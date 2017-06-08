#ifndef TANK_GAME_H
#define TANK_GAME_H
#include "Game.h"
#include "Console.h"

#define DOWN 0
#define LEFT 1
#define UP 2
#define RIGHT 3
#define WIDTH 32
#define HEIGHT WIDTH
#define DRAW_W 20
#define DRAW_H 20
#define TANK_W 3
#define TANK_WIDTH(t) (t.direction == DOWN || t.direction == UP ? TANK_W : TANK_H)
#define TANK_WIDTH_PREV(t) (t.prevDirection == DOWN || t.prevDirection == UP ? TANK_W : TANK_H)
#define TANK_H 2
#define TANK_HEIGHT(t) (t.direction == DOWN || t.direction == UP ? TANK_H : TANK_W)
#define TANK_HEIGHT_PREV(t) (t.prevDirection == DOWN || t.prevDirection == UP ? TANK_H : TANK_W)
#define BULLET_W 1
#define BULLET_H BULLET_W
#define C1 GREEN
#define C2 BLUE
#define C3 RED
#define C4 YELLOW
#define CB PINK_COLOR
#define CN BROWN
#define CW WHITE
#define ONE_S_X -1
#define ONE_S_Y 1
#define ONE_S_R 1
#define TWO_S_X WIDTH-TANK_W
#define TWO_S_Y 0
#define TWO_S_R 0
#define THREE_S_X 0
#define THREE_S_Y HEIGHT-TANK_H
#define THREE_S_R 2
#define FOUR_S_X WIDTH-TANK_W
#define FOUR_S_Y HEIGHT-TANK_H
#define FOUR_S_R 3
#define BULLET_SPEED 2
#define TANK_SPEED 1
#define NONE 255
#define WALL_AMOUNT 4
#define NOSE_X(t) (t.direction == DOWN ? t.position.x+1 : (t.direction == LEFT ? t.position.x-1 : (t.direction == UP ? t.position.x+1 : t.position.x+2)))
#define NOSE_Y(t) (t.direction == DOWN ? t.position.y+2 : (t.direction == LEFT ? t.position.y+1 : (t.direction == UP ? t.position.y-1 : t.position.y+1)))
#define NOSE_X_PREV(t) (t.prevDirection == DOWN ? t.prevPosition.x+1 : (t.prevDirection == LEFT ? t.prevPosition.x-1 : (t.prevDirection == UP ? t.prevPosition.x+1 : t.prevPosition.x+2)))
#define NOSE_Y_PREV(t) (t.prevDirection == DOWN ? t.prevPosition.y+2 : (t.prevDirection == LEFT ? t.prevPosition.y+1 : (t.prevDirection == UP ? t.prevPosition.y-1 : t.prevPosition.y+1)))
#define CONTROL 3
#define NUM_TANKS 4
#define SHOOT_COOLDOWN 5

class Bullet
{
  public:
    Bullet(){}
    ~Bullet(){}
    
    Vec2 position;
    Vec2 prevPosition;
    byte direction;

    void update();
    void render(Console*);
};

class Wall
{
  public:
    Wall(){}
    ~Wall(){}
  
    Vec2 position;
    byte width;
    byte height;

    void render(Console*);
};

class Tank
{
  public:
    Tank(){}
    ~Tank(){}
  
    Vec2 position;
    Vec2 prevPosition;
    byte direction;
    byte prevDirection;
    Bullet bullet;
    ColorRGB color;
    byte shootTime = 0;
    

    void rotate(byte);
    void move(byte);
    void shoot();

    bool noseCollides(Wall&);
    bool collides(Wall&);
    bool noseCollidesNose(Tank&);
    bool noseCollides(Tank&);
    bool collides(Tank&);

    bool isInRange(Tank&);

    void update(const Controller&);
    void render(Console*);
};

class TankGame : public Game
{
public:
	TankGame(Console*);
	~TankGame();

	void init() override;
	void update() override;
	void render() override;
	void quit() override;

	void menu_init() override;
	void menu_update() override;
	void menu_render() override;
	void menu_quit() override;
private:
  void checkCollisions(Tank&,Tank&);
  void checkCollisions(Tank&,Wall&);
  void checkCollisions();

  Tank tanks[NUM_TANKS];
  Wall walls[WALL_AMOUNT];
  
};

class TankGameWrapper : public Game
{
  public:
    TankGameWrapper(Console*);
    ~TankGameWrapper();
  
    void init() override;
    void update() override;
    void render() override;
    void quit() override;
  
    void menu_init() override;
    void menu_update() override;
    void menu_render() override;
    void menu_quit() override;
   private:
    TankGame* m_tankGame = nullptr;
};

#endif

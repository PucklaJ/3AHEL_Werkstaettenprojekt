#include "TankGame.h"
#include "Console.h"

TankGame::TankGame(Console* console) : Game(console)
{

}

TankGame::~TankGame()
{

}

void TankGame::init()
{
  for(int i = 0;i<NUM_TANKS;i++)
  {
      tanks[i].direction = 0;
      tanks[i].bullet.position.x = NONE;
      tanks[i].bullet.position.y = NONE;
  }
  
  tanks[0].position.x = ONE_S_X;
  tanks[0].position.y = ONE_S_Y;
  tanks[0].color = ColorRGB(C1);
  for(int i = 0;i<ONE_S_R;i++)
      tanks[0].rotate(RIGHT);
  tanks[1].position.x = TWO_S_X;
  tanks[1].position.y = TWO_S_Y;
  tanks[1].color = ColorRGB(C2);
  for(int i = 0;i<TWO_S_R;i++)
      tanks[1].rotate(RIGHT);
  tanks[2].position.x = THREE_S_X;
  tanks[2].position.y = THREE_S_Y;
  tanks[2].color = ColorRGB(C3);
  for(int i = 0;i<THREE_S_R;i++)
      tanks[2].rotate(RIGHT);
  tanks[3].position.x = FOUR_S_X;
  tanks[3].position.y = FOUR_S_Y;
  tanks[3].color = ColorRGB(C4);
  for(int i = 0;i<FOUR_S_R;i++)
      tanks[3].rotate(RIGHT);

  walls[0].position.x = 5;
  walls[0].position.y = 5;
  walls[0].width = 10;
  walls[0].height = 1;
  walls[1].position.x = 10;
  walls[1].position.y = 20;
  walls[1].width = 1;
  walls[1].height = 8;
  walls[2].position.x = 6;
  walls[2].position.y = 20;
  walls[2].width = 1;
  walls[2].height = 8;
  walls[3].position.x = 20;
  walls[3].position.y = 10;
  walls[3].width = 8;
  walls[3].height = 1;
}

int numDead=0;

void TankGame::update()
{
  numDead = 0;
  for(int i = 0;i<NUM_TANKS;i++)
  {
      if(tanks[i].dead)
      {
        numDead++;
      }
      else
      {
        tanks[i].update(console->getController(i));
      }
  }
    
  checkCollisions();
}

void TankGame::restart()
{
  for(int i = 0;i<NUM_TANKS;i++)
  {
      tanks[i].direction = 0;
      tanks[i].bullet.position.x = NONE;
      tanks[i].bullet.position.y = NONE;
      tanks[i].dead = false;
  }
  
  tanks[0].position.x = ONE_S_X;
  tanks[0].position.y = ONE_S_Y;
  tanks[0].color = ColorRGB(C1);
  for(int i = 0;i<ONE_S_R;i++)
      tanks[0].rotate(RIGHT);
  tanks[1].position.x = TWO_S_X;
  tanks[1].position.y = TWO_S_Y;
  tanks[1].color = ColorRGB(C2);
  for(int i = 0;i<TWO_S_R;i++)
      tanks[1].rotate(RIGHT);
  tanks[2].position.x = THREE_S_X;
  tanks[2].position.y = THREE_S_Y;
  tanks[2].color = ColorRGB(C3);
  for(int i = 0;i<THREE_S_R;i++)
      tanks[2].rotate(RIGHT);
  tanks[3].position.x = FOUR_S_X;
  tanks[3].position.y = FOUR_S_Y;
  tanks[3].color = ColorRGB(C4);
  for(int i = 0;i<FOUR_S_R;i++)
      tanks[3].rotate(RIGHT);
}

void TankGame::render()
{
  console->fillScreen(console->Color(BLACK));

  for(int i = 0;i<WALL_AMOUNT;i++)
  {
    walls[i].render(console);
  }

  for(int i = 0;i<NUM_TANKS;i++)
  {
    tanks[i].render(console);
  }

  if(numDead > 2)
  {
    delay(2000);
    restart();
  }
}

void TankGame::quit()
{
	
}

void TankGame::menu_init()
{
   console->fillScreen(console->Color(BLACK));
   console->setTextColor(console->Color(WHITE));
   console->setTextSize(1);    // size 1 == 8 pixels high
}

void TankGame::menu_update()
{
   
}

void TankGame::menu_render()
{
  console->setCursor(0, 12);
 
  console->print('T'); 
  console->print('A');
  console->print('N');
  console->print('K'); 
  console->print('S');
}

void TankGame::menu_quit()
{
  console->fillScreen(console->Color(BLACK));
}

void TankGame::checkCollisions(Tank& t1,Tank& t2)
{
  if(t1.collides(t2))
  {
      if(t1.direction == DOWN)
      {
          if(t1.position.y < t2.position.y)
          {
              t1.position.y-=TANK_SPEED;
          }
          else
          {
              t1.position.y+=TANK_SPEED;
          }
      }
      else if(t1.direction == LEFT)
      {
          if(t1.position.x < t2.position.x)
          {
              t1.position.x-=TANK_SPEED;
          }
          else
          {
              t1.position.x+=TANK_SPEED;
          }
      }
      else if(t1.direction == UP)
      {
          if(t1.position.y < t2.position.y)
          {
              t1.position.y-=TANK_SPEED;
          }
          else
          {
              t1.position.y+=TANK_SPEED;
          }
      }
      else if(t1.direction == RIGHT)
      {
          if(t1.position.x < t2.position.x)
          {
              t1.position.x-=TANK_SPEED;
          }
          else
          {
              t1.position.x+=TANK_SPEED;
          }
      }
  }
}
void TankGame::checkCollisions(Tank& t,Wall& w)
{
  if(t.collides(w))
  {
      if(t.direction == DOWN)
      {
          if(t.position.y < w.position.y)
          {
              t.position.y-=TANK_SPEED;
          }
          else
          {
              t.position.y+=TANK_SPEED;
          }
      }
      else if(t.direction == LEFT)
      {
          if(t.position.x < w.position.x)
          {
              t.position.x-=TANK_SPEED;
          }
          else
          {
              t.position.x+=TANK_SPEED;
          }
      }
      else if(t.direction == UP)
      {
          if(t.position.y < w.position.y)
          {
              t.position.y-=TANK_SPEED;
          }
          else
          {
              t.position.y+=TANK_SPEED;
          }
      }
      else if(t.direction == RIGHT)
      {
          if(t.position.x < w.position.x)
          {
              t.position.x-=TANK_SPEED;
          }
          else
          {
              t.position.x+=TANK_SPEED;
          }
      }
  }
}
void TankGame::checkCollisions()
{
  for(int i = 0;i<NUM_TANKS;i++)
  {
      if(tanks[i].dead)
        continue;

      for(int j = 0;j<WALL_AMOUNT;j++)
      {
          checkCollisions(tanks[i],walls[j]);
          checkCollisions(tanks[i].bullet,walls[j]);
      }
      for(int j = i+1;j<NUM_TANKS;j++)
      {
          if(tanks[i].isInRange(tanks[j]))
              checkCollisions(tanks[i],tanks[j]);

          if(tanks[j].bullet.position.x != NONE)
            checkCollisions(tanks[i],tanks[j].bullet);
      }
  }
}

void TankGame::checkCollisions(Tank& t,Bullet& b)
{
  if(((t.position.x < b.position.x && t.position.x + TANK_WIDTH(t) > b.position.x &&
       t.position.y < b.position.y && t.position.y + TANK_HEIGHT(t) > b.position.y) ||
     (NOSE_X(t) == b.position.x && NOSE_Y(t) == b.position.y)) || 
     ((t.position.x < PREV_POS_X(b) && t.position.x + TANK_WIDTH(t) > PREV_POS_X(b) &&
       t.position.y < PREV_POS_Y(b) && t.position.y + TANK_HEIGHT(t) > PREV_POS_Y(b) ||
     (NOSE_X(t) == PREV_POS_X(b) && NOSE_Y(t) == PREV_POS_Y(b)))))
  {
     b.position.x = b.position.y = NONE;
     t.dead = true;
  }
}

void TankGame::checkCollisions(Bullet& b,Wall& w)
{
  if((w.position.x < b.position.x && w.position.x + w.width > b.position.x &&
       w.position.y < b.position.y && w.position.y + w.height > b.position.y) || 
     (w.position.x < PREV_POS_X(b) && w.position.x + w.width > PREV_POS_X(b) &&
       w.position.y < PREV_POS_Y(b) && w.position.y + w.height > PREV_POS_Y(b)))
  {
     b.position.x = b.position.y = NONE;
  }
}

void Tank::rotate(byte r)
{
    if(r == RIGHT)
    {
        if(direction == DOWN)
        {
            direction = RIGHT;
            position.x += 1;
            position.y -= 1;
        }
        else if(direction == LEFT)
        {
            direction = DOWN;
            position.x -= 1;
            position.y += 1;
        }
        else if(direction == UP)
        {
            direction = LEFT;
            position.x += 1;
            position.y -= 1;
        }
        else if(direction == RIGHT)
        {
            direction = UP;
            position.x -= 1;
            position.y += 1;
        }
    }
    else
    {
        if(direction == DOWN)
        {
            direction = LEFT;
            position.x += 1;
            position.y -= 1;
        }
        else if(direction == LEFT)
        {
            direction = UP;
            position.x -= 1;
            position.y += 1;
        }
        else if(direction == UP)
        {
            direction = RIGHT;
            position.x += 1;
            position.y -= 1;
        }
        else if(direction == RIGHT)
        {
            direction = DOWN;
            position.x -= 1;
            position.y += 1;
        }
    }
}
void Tank::move(byte m)
{
  if(m == UP)
  {
      if(direction == DOWN)
      {
          position.y+=TANK_SPEED;
      }
      else if(direction == LEFT)
      {
          position.x-=TANK_SPEED;
      }
      else if(direction == UP)
      {
          position.y-=TANK_SPEED;
      }
      else
      {
          position.x+=TANK_SPEED;
      }
  }
  else
  {
      if(direction == DOWN)
      {
          position.y-=TANK_SPEED;
      }
      else if(direction == LEFT)
      {
          position.x+=TANK_SPEED;
      }
      else if(direction == UP)
      {
          position.y+=TANK_SPEED;
      }
      else
      {
          position.x-=TANK_SPEED;
      }
  }
}

void Tank::update(const Controller& c)
{
    if(shootTime > 0)
      shootTime--;
  
   if(c.isConnected())
   {

    // Movement Control
    byte dir = (c.isPressed(BUT_UP) ? UP : (c.isPressed(BUT_DOWN) ? DOWN : NONE));

    if(dir != NONE)
    {
      move(dir);
    }

    // Rotate control

    byte rot = (c.isPressed(BUT_LEFT) ? LEFT : (c.isPressed(BUT_RIGHT) ? RIGHT : NONE));

    if(rot != NONE)
    {
      rotate(rot);
    }

    // Shoot control

    if(c.justPressed(BUT_A))
    {
      shoot();
    }
    
   }
  
   bullet.update();
}

void Tank::shoot()
{
  if(direction == DOWN)
  {
      bullet.position.x = position.x + 1;
      bullet.position.y = position.y + 2;
  }
  else if(direction == LEFT)
  {
      bullet.position.x = position.x - 1;
      bullet.position.y = position.y + 1;
  }
  else if(direction == UP)
  {
      bullet.position.x = position.x + 1;
      bullet.position.y = position.y - 1;
  }
  else if(direction == RIGHT)
  {
      bullet.position.x = position.x + 2;
      bullet.position.y = position.y + 1;
  }

  shootTime = SHOOT_COOLDOWN;
  
  bullet.direction = direction;
}

bool Tank::noseCollides(Wall& w)
{
  if(NOSE_X((*this))< w.position.x + w.width && NOSE_X((*this))+1 > w.position.x &&
      NOSE_Y((*this))<w.position.y + w.height && NOSE_Y((*this))+1 > w.position.y)
  {
     return true;
  }
  
  return false;
}
bool Tank::collides(Wall& w)
{
  if((position.x < w.position.x + w.width && position.x + TANK_WIDTH((*this)) > w.position.x &&
          position.y < w.position.y + w.height && position.y + TANK_HEIGHT((*this)) > w.position.y)
      || noseCollides(w))
  {
      return true;
  }
  
  return false;
}
bool Tank::noseCollidesNose(Tank& t)
{
  if(NOSE_X((*this))< NOSE_X(t) + 1 && NOSE_X((*this))+1 > NOSE_X(t) &&
     NOSE_Y((*this))<NOSE_Y(t) + 1 && NOSE_Y((*this))+1 > NOSE_Y(t))
  {
      return true;
  }
  
  return false;
}
bool Tank::noseCollides(Tank& t)
{
  if(NOSE_X((*this))< t.position.x + TANK_WIDTH(t) && NOSE_X((*this))+1 > t.position.x &&
     NOSE_Y((*this))<t.position.y + TANK_HEIGHT(t) && NOSE_Y((*this))+1 > t.position.y)
  {
      return true;
  }
  
  return false;
}
bool Tank::collides(Tank& t)
{
  if((position.x < t.position.x + TANK_WIDTH(t) && position.x + TANK_WIDTH((*this)) > t.position.x &&
          position.y < t.position.y + TANK_HEIGHT(t) && position.y + TANK_HEIGHT((*this)) > t.position.y)
      || noseCollides(t) || t.noseCollides(*this) || noseCollidesNose(t))
  {
      return true;
  }
  
  return false;
}

bool Tank::isInRange(Tank& t)
{
  if((t.position.x-position.x)*(t.position.x-position.x)+(t.position.y-position.y)*(t.position.y-position.y) < 4*TANK_W*TANK_W)
      return true;
  
  return false;
}

void Tank::render(Console* c)
{
  c->fillRect(position.x,position.y,TANK_WIDTH((*this)),TANK_HEIGHT((*this)),c->Color(color));
  c->drawPixel(NOSE_X((*this)),NOSE_Y((*this)),c->Color(CN));

  if(bullet.position.x != NONE)
    bullet.render(c);
}

void Bullet::render(Console* c)
{
  c->drawPixel(position.x,position.y,c->Color(CB));
}

void Bullet::update()
{
  if(position.x < 0 || position.x >= WIDTH || position.y < 0 || position.y >= HEIGHT)
    {
        position.x = NONE;
    }
    
    if(position.x != NONE)
    {
        switch(direction)
        {
            case DOWN:
                position.y+=BULLET_SPEED;
                break;
            case LEFT:
                position.x-=BULLET_SPEED;
                break;
            case UP:
                position.y-=BULLET_SPEED;
                break;
            case RIGHT:
                position.x+=BULLET_SPEED;
                break;
        }
    }
}

void Wall::render(Console* c)
{
  c->fillRect(position.x,position.y,width,height,c->Color(CW));
}

TankGameWrapper::TankGameWrapper(Console* c) : Game(c)
{
  
}

TankGameWrapper::~TankGameWrapper()
{
  
}

void TankGameWrapper::init()
{
  m_tankGame = new TankGame(console);
  m_tankGame->init();
}
void TankGameWrapper::update()
{
  m_tankGame->update();
}
void TankGameWrapper::render()
{
  m_tankGame->render();
}
void TankGameWrapper::quit()
{
  m_tankGame->quit();
  delete m_tankGame;
}

void TankGameWrapper::menu_init()
{
  m_tankGame = new TankGame(console);
  m_tankGame->menu_init();
}
void TankGameWrapper::menu_update()
{
  m_tankGame->menu_update();
}
void TankGameWrapper::menu_render()
{
  m_tankGame->menu_render();
}
void TankGameWrapper::menu_quit()
{
  m_tankGame->menu_quit();
  delete m_tankGame;
}


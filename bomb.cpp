#include "bomb.h"
#include <QPainter>
#include "spaceship.h"
#include "alien.h"

Bomb::Bomb()
{

}

Bomb::Bomb(int x, int y, int size, bool type, QImage img)
{
    this->x = x;
    this->y = y;
    this->type = type;
    this->size = size;
    this->img = img;
}

void Bomb::draw(QPainter *paint)
{
//    if (type == true)
//        paint->drawImage(QRect(x,y, size,size*2),rocket);
//    else
//    {
//        paint->drawImage(QRect(x,y,size,size*2), bomb);
//    }
    paint->drawImage(QRect(x,y, size,size*2),img);
}

void Bomb::move(int dy)
{
    if (type == true) y -= dy;
    else y += dy;
}

bool Bomb::borders(Alien* alien)
{
    return (x + size > alien->getX() && x < alien->getX() + alien->getSize() && y < alien->getY() + alien->getSize() && y + size*2 > alien->getY());
}

bool Bomb::borders(Spaceship ship)
{
    return (x + size > ship.getX() && x < ship.getX() + ship.getSize() && y < ship.getY() + ship.getSize() && y + size*2 > ship.getY());
}

int Bomb::getY() const
{
    return y;
}

void Bomb::setY(int value)
{
    y = value;
}

bool Bomb::getType() const
{
    return type;
}

void Bomb::setType(bool value)
{
    type = value;
}

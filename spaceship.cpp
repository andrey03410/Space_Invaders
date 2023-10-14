#include "spaceship.h"
#include "bomb.h"
#include <QPainter>
#include <QSound>

Spaceship::Spaceship()
{
    x = 0;
    y = 0;
    health = 5;
}

Spaceship::Spaceship(int y,int size)
{
    x = 200;
    this->y = y;
    this->size = size;
    health = 5;
}

void Spaceship::draw(QPainter *paint)
{
    paint->drawImage(QRect(x,y,size,size),img);
}

void Spaceship::move(int dx)
{
    x += dx;
}

void Spaceship::attack(QList <Bomb*> &a)
{
    a.append(new Bomb(x + size*3/8,y ,size/4, true, rocket));
    QSound::play(":/new/sound/shot.wav");
}

int Spaceship::getX() const
{
    return x;
}

void Spaceship::setX(int value)
{
    x = value;
}

int Spaceship::getY() const
{
    return y;
}

void Spaceship::setY(int value)
{
    y = value;
}

int Spaceship::getSize() const
{
    return size;
}

void Spaceship::setSize(int value)
{
    size = value;
}

int Spaceship::getHealth() const
{
    return health;
}

void Spaceship::setHealth(int value)
{
    health = value;
}

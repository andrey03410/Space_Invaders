#include "alien.h"
#include <QPainter>

Alien::Alien()
{

}

Alien::Alien(int x, int y, int size, QImage img)
{
    this->x = x;
    this->y = y;
    this->size = size;
    this->img = img;
}

void Alien::draw(QPainter *paint)
{
    paint->drawImage(QRect(x,y,size,size), img);
}

void Alien::move(int dx)
{
    x += dx;
}

int Alien::getX() const
{
    return x;
}

void Alien::setX(int value)
{
    x = value;
}

int Alien::getY() const
{
    return y;
}

void Alien::setY(int value)
{
    y = value;
}

int Alien::getSize() const
{
    return size;
}

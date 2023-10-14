#ifndef ALIEN_H
#define ALIEN_H

#include <QImage>


class Alien
{
public:
    Alien();
    Alien(int x, int y, int size, QImage img);
    void draw(QPainter* paint);
    void move(int dx);
    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getSize() const;

private:
    int x, y, size;
    QImage img;
};

#endif // ALIEN_H

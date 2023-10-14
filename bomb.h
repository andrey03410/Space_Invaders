#ifndef BOMB_H
#define BOMB_H
#include <QImage>
class Spaceship;
class Alien;
class QPainter;


class Bomb
{
public:
    Bomb();
    Bomb(int x, int y,int size, bool type, QImage img); // type == false если бомба от пришельцев, true если от корабля
    void draw(QPainter* paint);
    void move(int dy);
    bool borders(Alien* alien);
    bool borders(Spaceship ship);
    int getY() const;
    void setY(int value);

    bool getType() const;
    void setType(bool value);

private:
    int x,y, size;
    bool type;
    QImage img;

};

#endif // BOMB_H

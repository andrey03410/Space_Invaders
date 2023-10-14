#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <QImage>
class QPainter;
class Bomb;


class Spaceship
{
public:
    Spaceship();
    Spaceship(int y,int size);
    void draw(QPainter* paint);
    void move(int dx);
    void attack(QList <Bomb*> &a);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getSize() const;
    void setSize(int value);

    int getHealth() const;
    void setHealth(int value);

private:
    int x,y,size;
    int health;
    QImage img = QImage(":/new/img/spaceship.png");
    QImage rocket = QImage(":/new/img/rocket.png");
};

#endif // SPACESHIP_H

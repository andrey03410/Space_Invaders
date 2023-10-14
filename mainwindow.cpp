#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QPainter>
#include "spaceship.h"
#include <QTimer>
#include "bomb.h"
#include <QPushButton>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(update1()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(update2()));
    MainWindow::ui->pushButton->setStyleSheet("QPushButton{"
                                              " color: #00a86b;"
                                              "  background-color: black;"
                                              "}");
    MainWindow::ui->pushButton_2->setStyleSheet("QPushButton{"
                                              " color: #00a86b;"
                                              "  background-color: black;"
                                              "}");
    font1.setPixelSize(20);
    font2.setPixelSize(30);
    font1.setPointSize(15);
    MainWindow::ui->pushButton->setFont(font1);
    MainWindow::ui->pushButton_2->setFont(font1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_mainmenu(QPainter* paint)
{
    paint->setBrush(Qt::black);
    paint->drawRect(0,0,width(), height());
    paint->drawImage(QRect(width()/4, 0, width()/2, width()/4), logo);
    MainWindow::ui->pushButton->setGeometry(width()/2 - 100,height() - 100,200,35);
    MainWindow::ui->pushButton_2->setGeometry(width()/2 - 100,height() - 50,200,35);
}

void MainWindow::init()
{
    ship_size = width() / ALIEN_COUNT;
    ship.setY(height()- ship_size);
    ship.setSize(ship_size);
    ship.setHealth(5);
    layers = 1;
    points = 0;
    timer1->start(1000/60);
    setFixedSize(width(), height());
    game_theme->setLoops(10);
    game_theme->play();
    lim_aliens = (height() - HUD_SIZE - ship_size) / (ship_size / 2);
    init_aliens();
}

void MainWindow::init_aliens()
{
    bombs.clear();
    for (int i = 0; i < layers; i++)
    {
        for(int j = 0; j < ALIEN_COUNT; j++)
        {
            aliens.append(new Alien(ship_size*2 + ship_size*j*3/4, HUD_SIZE + ship_size/2 * i, ship_size/2, alien));
        }
    }
    quantity = ALIEN_COUNT * layers;
    delay2 = 500;
    delay1 = 100;
    timer2->start(delay2);
}

void MainWindow::draw_game(QPainter *paint)
{
    paint->drawImage(QRect(0,0, width(), height()), background);
    QString a = "Жизни: " + QString::number(ship.getHealth());
    QString b = "Очки: " + QString::number(points);
    paint->setFont(font2);
    paint->setPen(Qt::green);
    paint->drawText(width() -130, 25, a);
    paint->drawText(0, 25, b);
    foreach(Bomb* i, bombs)
        i->draw(&*paint);
    foreach(Alien* i, aliens)
        i->draw(&*paint);
    ship.draw(&*paint);
}

void MainWindow::game_over(QPainter* paint)
{
    timer1->stop();
    timer2->stop();
    game_theme->stop();
    aliens.clear();
    bombs.clear();
    paint->drawImage(QRect(0,0,width(), height()), end);
    MainWindow::ui->pushButton->show();
    MainWindow::ui->pushButton_2->show();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(game_status == 0) draw_mainmenu(&painter);
    else if(game_status == 1) draw_game(&painter);
    else game_over(&painter);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        dx_ship = -1;
    }
    else if (event->key() == Qt::Key_Right)
    {
        dx_ship = 1;
    }
    if (event->key() == Qt::Key_Space && delay3 == 0 && game_status == 1)
    {
        ship.attack(bombs);
        delay3 = 30;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) dx_ship = 0;
}

void MainWindow::update1()
{
    if (delay3 > 0) delay3--;
    ship.move(width()/TIME_T*dx_ship);
    if (ship.getX() <= 0) ship.setX(0);   // для того чтобы корабль не заходил за пределы экрана
    if (ship.getX() + ship_size >= width()) ship.setX(width() - ship_size);
    QMutableListIterator <Bomb*> i(bombs);
    while (i.hasNext())  // проверка столкновений
    {
        if (i.peekNext()->getType() == true)
        {
            QMutableListIterator <Alien*> k(aliens);
            while (k.hasNext())
            {
                if(i.peekNext()->borders(k.next()))
                {
                    points += 500;
                    i.next();
                    i.remove();
                    k.remove();
                    QSound::play(":/new/sound/hit_alien.wav");
                    break;
                }
            }
        }
        else
        {
            if(i.peekNext()->borders(ship))
            {
                ship.setHealth(ship.getHealth() - 1);
                QSound::play(":/new/sound/hit_spaceship.wav");
                i.next();
                i.remove();
            }
        }
        if(i.hasNext())
        {
            i.peekNext()->move(height()/TIME_T*2);
            if (i.peekNext()->getY() <= 0 || i.peekNext()->getY() > height() + 500) i.remove();
            i.next();
        }
    }
    if(ship.getHealth() <= 0)
    {
        game_status = 2;
        QSound::play(":/new/sound/end.wav");
    }
    repaint();
}

void MainWindow::update2()
{
    delay1--;
    foreach(Alien* i, aliens)  // проверка соударения пришельцев о края экрана
    {
        if (i->getY() + i->getSize() >= height() - ship_size)
        {
            game_status = 2;
            break;
        }
        if(i->getX() < 0)
        {
            dx_aliens = -dx_aliens;
            break;
        }
        else if(i->getX() > width() - i->getSize())
        {
            dx_aliens = -dx_aliens;
            break;
        }
    }
    foreach(Alien* i, aliens)  // движение пришлеьцев
    {
        if(delay1 < 0) i->setY(i->getY() + i->getSize());
        i->move(width()/TIME_T * dx_aliens);
        if (qrand() % 1000 < probability) bombs.append(new Bomb(i->getX(), i->getY(), i->getSize()/2, false, bomb));
    }
    if (delay1 < 0) delay1 = 100;
    if (aliens.size() == 0)
    {
        if (layers < lim_aliens) layers++;
        init_aliens();
    }
    if (aliens.size() <= quantity / 2)
    {
        delay2 /= 2;
        quantity /= 2;
        timer2->start(delay2);
    }
}

void MainWindow::on_pushButton_clicked()
{
    game_status = 1;
    MainWindow::ui->pushButton->hide();
    MainWindow::ui->pushButton_2->hide();
    init();
    setFocus();
}

void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include "spaceship.h"
#include "alien.h"
#include <QKeyEvent>
#include <QList>
#include "bomb.h"
#include <QImage>
#include <QTimer>
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void draw_mainmenu(QPainter* paint);
    void init();
    void init_aliens();
    void draw_game(QPainter* paint);
    void game_over(QPainter* paint);
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    void update1();  // для снарядов и корабля
    void update2();  // для пришельцев

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer1 = new QTimer();
    QTimer* timer2 = new QTimer();
    Spaceship ship = Spaceship(height(),width() / 15);
    const int TIME_T = 120;      // время за которое корабль добирается из левой части экрана до правой (в кадрах в секунду, по умолчанию стоит 60, т.е 2 секунды)
    const int ALIEN_COUNT = 15;  // количество пришельцев на слой
    const int HUD_SIZE = 50;

    int dx_ship = 0;
    int dx_aliens = 1;
    int ship_size;
    char game_status = 0; // 0 - главное меню, 1 - начало игры, 2 - конец игры
    int quantity = 15;
    int lim_aliens;      // максимально возможное количество слоев пришельцев

    unsigned int points = 0;
    int layers = 1;
    int delay1 = 100;  // сколько осталось "шагов" пришельцев до спуска на новый слой
    int delay2 = 500;  // скорость пришельцев (чем меньше, тем выше)
    int delay3 = 0;    // задержка на выстрелы корабля
    int probability = 30;   // вероятность выстрела пришельца на момент времени (максимальное 1000)

    QList <Bomb*> bombs;
    QList <Alien*> aliens;

    QFont font1 = QFont("arial");
    QFont font2 = QFont("arial");

    QImage logo = QImage(":/new/img/logo.png");
    QImage background = QImage(":/new/img/space.jpg");
    QImage bomb = QImage(":/new/img/bomb.png");
    QImage end = QImage(":/new/img/end.jpg");
    QImage alien = QImage(":/new/img/alien.png");

    QSound* game_theme = new QSound(":/new/sound/game_theme.wav");
};
#endif // MAINWINDOW_H

#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>

class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();

protected: // slots
    void timerEvent(QTimerEvent *) override; // slot for timer
    void keyPressEvent(QKeyEvent *) override; //  keybord triggers
    void paintEvent(QPaintEvent *event) override;

private:

    // size of snake's patrs
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    // size of the game field
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;

    // size of the snake (number of parts)
    int N = 3;

    // timer
    static const int DELAY = 150; // interval for repeating
    int timerID;

    bool inGame;

    // directions
    enum Directions { LEFT, RIGHT, UP, DOWN };

    // direction of the snake
    Directions dir;

    // place of the apple
    QPoint apple;

    // parts of the snake
    QVector<QPoint> dots;

    int score = 0;

    void doDrawing(); // funkce kreslení
    void localApple(); // funkce náhodné pozice jablka
    void initGame(); // funkce inicializace hry
    void move(); // pohyb hadu
    void checkField(); // kontrola, není-li had mimo hranici pole
    void gameOver(); // oznamení o ukončení hry
    void checkApple(); // kontrola snezení jablka
};

#endif // SNAKE_H

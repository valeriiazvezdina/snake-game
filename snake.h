#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QVector>
#include <QPoint> // struktura umožňující ukládat data ve dvojicích jako souřadnice X a Y, což usnadní praci
#include <QKeyEvent> // pro praci se stiskutím klávesnice

class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();

protected: // sloty
    void timerEvent(QTimerEvent *) override; // slot pro intervalový timer
    void keyPressEvent(QKeyEvent *) override; //  zpracovávání dotyku klávesnice
    void paintEvent(QPaintEvent *event) override; // kreslení

private:
    // static protože nejsou zavázány na jednotkách classu a fungují stejně pro celý class

    // rozměry jednotlivých částí hada
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    // rozměry pole
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;

    // velikost hada, tj. množství částí hada na zacátku hry
    int N = 3;

    // timer
    static const int DELAY = 150; // interval opakování
    int timerID;

    // stav hry: pokud se nenarazime do zdi, stav je true, jinak je false
    bool inGame;

    // možné směry
    enum Directions { LEFT, RIGHT, UP, DOWN };

    // směr hada
    Directions dir;

    // pozice jablka
    QPoint apple;

    // zde bude uložena veškerá informace ohledně pozic jednotlivých částí hadu
    QVector<QPoint> dots;

    int score = 0;

    // metody
    void doDrawing(); // funkce kreslení
    void localApple(); // funkce náhodné pozice jablka
    void initGame(); // funkce inicializace hry
    void move(); // pohyb hadu
    void checkField(); // kontrola, není-li had mimo hranici pole
    void gameOver(); // oznamení o ukončení hry
    void checkApple(); // kontrola snezení jablka
};

#endif // SNAKE_H

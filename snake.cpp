#include "snake.h"

#include <QApplication>
#include <QPainter> // umožní praci s kreslením
#include <QTime> // práce s časem
#include <QRandomGenerator> // generace náhodných čísel
#include <QMessageBox> // okna informace

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{
    // nastavení backgroundu hry
    setStyleSheet("background-color:black;");
    // nastavujeme velikost pole
    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);
    // název okna
    setWindowTitle("Snake game");
    // inicializace hry a základních metod
    initGame();
}

Snake::~Snake() { }

void Snake::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event); // tuto proměnnu event nepouzíváme

    if (inGame) { // pokud had je "aktivní" vyplňujeme následující akce
        checkApple();
        move();
        checkField();
    }
    this->repaint(); // překreslení po provedení akcí
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    // podle dotyku měníme směr hadu
    if (key == Qt::Key_Left && dir != RIGHT) {
        dir = LEFT;
    }
    if (key == Qt::Key_Right && dir != LEFT) {
        dir = RIGHT;
    }
    if (key == Qt::Key_Up && dir != DOWN) {
        dir = UP;
    }
    if (key == Qt::Key_Down && dir != UP) {
        dir = DOWN;
    }
}

void Snake::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // tato proměnna není nutná a nebudeme ji používat
    doDrawing(); // přetížení standardní funkce paintEvent
}

void Snake::initGame()
{
    // základní vlastnosti hadu
    inGame = true;
    dir = RIGHT;
    dots.resize(N); // původně had má tři části, kde hlava je nulový index

    // inicializace elementů hadu v centru pole
    for (int i = 0; i < dots.size(); ++i) {
        dots[i].rx() = ((FIELD_WIDTH - 1) / 2) - i;
        dots[i].ry() = (FIELD_HEIGHT - 1) / 2;
    }

    // nastavení pozici jablka
    localApple();

    // timer, který bude vyvolávát určité funkce po první inicializace hry a po určitému intervalu
    timerID = startTimer(DELAY);
}

void Snake::doDrawing()
{
    QPainter qp(this);

    if (inGame) {
        // kreslení jablka
        qp.setBrush(Qt::yellow);
        qp.drawEllipse(apple.x() * DOT_WIDTH, apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

        // kreslení hada
        for (int i = 0; i < dots.size(); ++i) {
            if (i == 0) {
                qp.setBrush(Qt::red);
                qp.drawEllipse(dots[i].x() * DOT_WIDTH, dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            } else {
                qp.setBrush(Qt::green);
                qp.drawEllipse(dots[i].x() * DOT_WIDTH, dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
                }
            }

        qp.drawText(5,20, QString("%1").arg(score));

        } else {
            gameOver();
            score = 0;
    }
}

void Snake::localApple()
{
    QRandomGenerator *gen =  QRandomGenerator::system();
    apple.rx() = gen->bounded(DOT_WIDTH);
    apple.ry() = gen->bounded(DOT_HEIGHT);
}

void Snake::move()
{
    // přemíštění poslední části hada na místo předposlední části, tedy celý had posouvá o jeden prvek v určitém směru
    for (int i = dots.size()-1; i > 0; --i) {
        dots[i] = dots[i-1];
    }

    // pohyb hlavy hada
    switch (dir) {
    case LEFT: {
        dots[0].rx() -= 1;
        break;
        }
    case RIGHT: {
        dots[0].rx() += 1;
        break;
        }
    case UP: {
        dots[0].ry() -= 1;
        break;
        }
    case DOWN: {
        dots[0].ry() += 1;
        break;
        }
    }
}

void Snake::checkField()
{
    // kontrola, nenarazil-li had sam do sebe, což ale je možný pouze, když N je větší než 4
    if (dots.size() > 4) {
        for (int i = 1; i < dots.size(); ++i) {
            if (dots[0] == dots[i]) {
                inGame = false;
            }
        }
    }

    // kontrola hranici pole
    if (dots[0].x() >= FIELD_WIDTH) {
        inGame = false;
    }
    if (dots[0].x() < 0) {
        inGame = false;
    }
    if (dots[0].y() >= FIELD_HEIGHT) {
        inGame = false;
    }
    if (dots[0].y() < 0) {
        inGame = false;
    }

    // zastavení hry, pokud had nepřošel kontrolu
    if (!inGame) {
        killTimer(timerID );
    }
}

void Snake::checkApple()
{
    if (apple == dots[0]) {
        dots.push_back(QPoint(0, 0));
        score++;
        /* není rozdíl jaký dávat souřadnice, protože ve funkci move měníme poslední element
        pole na předposlední, tedy jediné, co je důležitý, je zvětšení pole o nový prvek */
        localApple(); // znovu nastavíme nové jablko
    }
}

void Snake::gameOver()
{
    // okno oznamující, že hra skončila
    QMessageBox mb1;
    mb1.setText("game over");
    mb1.exec();
    initGame();
}

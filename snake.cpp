#include "snake.h"

#include <QApplication>
#include <QPainter> // for using keybord
#include <QTime> // práce s časem
#include <QRandomGenerator> // generation random numbers
#include <QMessageBox> // information window

Snake::Snake(QWidget *parent)
    : QWidget(parent)
{
    // set up the background
    setStyleSheet("background-color:black;");
    // set up the size
    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);
    // the name of the window
    setWindowTitle("Snake game");
    initGame();
}

Snake::~Snake() { }

void Snake::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (inGame) {
        checkApple();
        move();
        checkField();
    }
    this->repaint();

void Snake::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    // change the direction
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
    Q_UNUSED(event);
    doDrawing(); // overloading the standard function of paintEvent
}

void Snake::initGame()
{
    // properties of snake
    inGame = true;
    dir = RIGHT;
    dots.resize(N);

    // inicialization the snake at the middle 
    for (int i = 0; i < dots.size(); ++i) {
        dots[i].rx() = ((FIELD_WIDTH - 1) / 2) - i;
        dots[i].ry() = (FIELD_HEIGHT - 1) / 2;
    }

    localApple();

    // timer for repeating actions
    timerID = startTimer(DELAY);
}

void Snake::doDrawing()
{
    QPainter qp(this);

    if (inGame) {
        // paiting the apple
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
    // replacement of the last part of the snake with the part before the last one => whole snake is moving on the 1 element
    for (int i = dots.size()-1; i > 0; --i) {
        dots[i] = dots[i-1];
    }

    // move of the snake head 
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
    // control for snake's cannibalism
    if (dots.size() > 4) {
        for (int i = 1; i < dots.size(); ++i) {
            if (dots[0] == dots[i]) {
                inGame = false;
            }
        }
    }

    // control for the field's size
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

    // game over
    if (!inGame) {
        killTimer(timerID );
    }
}

void Snake::checkApple()
{
    if (apple == dots[0]) {
        dots.push_back(QPoint(0, 0));
        score++;
        localApple(); // znovu nastavíme nové jablko
    }
}

void Snake::gameOver()
{
    // game over window
    QMessageBox mb1;
    mb1.setText("game over");
    mb1.exec();
    initGame();
}

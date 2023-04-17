#include "snake.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    int *p;
    int i;
    p = &i;
    *p = 10;

    QApplication app(argc, argv);
    Snake window; // instance classu
    window.show(); // zobrazení instancí
    return app.exec(); // realizace programu
}

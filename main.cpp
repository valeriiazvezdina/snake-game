#include "snake.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Snake window;
    window.show();
    return app.exec();
}

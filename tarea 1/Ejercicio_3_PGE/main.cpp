#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Widget gameWidget;
    gameWidget.setWindowTitle("Juego de la vibora");
    gameWidget.show();

    return a.exec();
}

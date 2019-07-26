//Created by
//Marcin Chrostowski
//Paweł Ostaszewski

#include "Controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;

    controller.run();

    return a.exec();
}

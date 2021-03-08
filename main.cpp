#include "mainwindow.h"
#include "Interpreter.h"

#include <QApplication>
#include <memory>
#include "Basic.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance();
    Basic& basic = Basic::getInstance();

    // connect signals
    QObject::connect(&basic, &Basic::codeAppendRow,
                     &w, &MainWindow::codeAppendRow);
    QObject::connect(&basic, &Basic::clickClearButton,
                     &w, &MainWindow::clickClearButton);
    QObject::connect(&basic, &Basic::clearDisplays,
                     &w, &MainWindow::clearDisplays);

    w.show();
    return a.exec();
}

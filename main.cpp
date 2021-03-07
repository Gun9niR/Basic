#include "mainwindow.h"
#include "Interpreter.h"

#include <QApplication>
#include <memory>
#include "Basic.h"

Basic basic;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

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

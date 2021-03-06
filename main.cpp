#include "mainwindow.h"
#include "Interpreter.h"

#include <QApplication>
#include <memory>

// declare interpreter gloabally so that mainwindow can access its member functions
Interpreter interpreter;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // connect signals
    QObject::connect(&interpreter, &Interpreter::codeAppendRow,
                     &w, &MainWindow::codeAppendRow);
    QObject::connect(&interpreter, &Interpreter::clickClearButton,
                     &w, &MainWindow::clickClearButton);
    QObject::connect(&interpreter, &Interpreter::clearDisplays,
                     &w, &MainWindow::clearDisplays);

    // start application
    w.show();
    return a.exec();
}

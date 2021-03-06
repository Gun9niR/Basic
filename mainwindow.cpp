#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
#include <memory>
#include "Interpreter.h"
#include "qdebug.h"

extern Interpreter interpreter;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    // select file path with a dialogue
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), "./", tr("Basic programs (*.basic)"));

    interpreter.loadFile(fileName);
}

void MainWindow::codeAppendRow(QString str) {
    ui->codeDisplay->append(str);
}

void MainWindow::on_clearButton_clicked()
{
    interpreter.reset();
    clearDisplays();
}

void MainWindow::clickClearButton() {
    // cannot use animateClick, as it seems to be async
    on_clearButton_clicked();
}

void MainWindow::clearDisplays() {
    ui->codeDisplay->clear();
    ui->resultDisplay->clear();
    ui->statementDisplay->clear();
}

void MainWindow::on_console_returnPressed()
{
    QString str = ui->console->text().trimmed();
    ui->console->clear();

    interpreter.handleRawInstruction(str);
}

void MainWindow::on_runButton_clicked()
{
    interpreter.runCode();
}

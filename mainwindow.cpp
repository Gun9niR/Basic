#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
#include <memory>
#include "Basic.h"
#include "qdebug.h"

MainWindow& MainWindow::getInstance() {
    static MainWindow w;
    return w;
}

MainWindow::~MainWindow() {
    delete ui;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), onInputStmt(false)
{
    ui->setupUi(this);
    ui->statementDisplay->setTabStopWidth(4 * fontMetrics().width(' '));
}

void MainWindow::on_loadButton_clicked()
{
    // select file path with a dialogue
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), "./", tr("Basic programs (*.basic)"));

    Basic::getInstance().loadFile(fileName);
}

void MainWindow::codeAppendRow(QString str) {
    ui->codeDisplay->append(str);
}

void MainWindow::statementAppendRow(QString str) {
    ui->statementDisplay->append(str);
}

void MainWindow::resultAppendRow(QString str) {
    ui->resultDisplay->append(str);
}

void MainWindow::on_clearButton_clicked()
{
    Basic::getInstance().reset();
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

    if (!onInputStmt) {
        Basic::getInstance().handleRawInstruction(str);
    } else {
        bool isNumber = false;
        int num = str.toInt(&isNumber);
        if (!isNumber) {
            return;
        } else {
            // emit signal to interpreter
        }
    }
}

void MainWindow::on_runButton_clicked()
{
    Basic::getInstance().interpret();
}

void MainWindow::disableInput() {
    ui->runButton->setDisabled(true);
    ui->clearButton->setDisabled(true);
    ui->loadButton->setDisabled(true);
    ui->console->setDisabled(true);
}

void MainWindow::enableInput() {
    ui->runButton->setDisabled(false);
    ui->clearButton->setDisabled(false);
    ui->loadButton->setDisabled(false);
    ui->console->setDisabled(false);
}

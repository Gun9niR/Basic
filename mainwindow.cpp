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
    , isRunning(false), ui(new Ui::MainWindow), onInputStmt(false)
{
    ui->setupUi(this);
    ui->statementDisplay->setTabStopWidth(4 * fontMetrics().width(' '));
}

void MainWindow::on_loadButton_clicked()
{
    // select file path with a dialogue
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), "./", tr("All(*.*)"));

    if (!fileName.isEmpty()) {
        Basic::getInstance().loadFile(fileName);
    }
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
    Basic::getInstance().clearEnvironment();
    clearDisplays();
}

void MainWindow::clickClearButton() {
    on_clearButton_clicked();
}

void MainWindow::clickLoadButton() {
    on_loadButton_clicked();
}

void MainWindow::clearDisplays() {
    ui->codeDisplay->clear();
    ui->resultDisplay->clear();
    ui->statementDisplay->clear();
    ui->errorDisplay->clear();
}

void MainWindow::on_console_returnPressed()
{
    QString str = ui->console->text().trimmed();
    ui->console->clear();

    if (!onInputStmt) {
        Basic::getInstance().handleRawInstruction(str);
    } else {
        bool isNumber = false;
        str = str.mid(2);
        int num = str.toInt(&isNumber);
        if (!isNumber) {
            emit sendInput(std::numeric_limits<int>::quiet_NaN());
        } else {
            emit sendInput(num);
        }
    }
}

void MainWindow::clickRunButton() {
    on_runButton_clicked();
}

void MainWindow::clearStatement() {
    ui->statementDisplay->clear();
}

void MainWindow::on_runButton_clicked()
{
    clearResult();
    clearStatement();
    clearError();
    isRunning = true;
    Basic::getInstance().interpret();
    isRunning = false;
}

void MainWindow::disableInput() {
    ui->runButton->setDisabled(true);
    ui->clearButton->setDisabled(true);
    ui->loadButton->setDisabled(true);
    ui->saveButton->setDisabled(true);
    ui->console->setDisabled(true);
}

void MainWindow::enableInput() {
    ui->runButton->setDisabled(false);
    ui->clearButton->setDisabled(false);
    ui->loadButton->setDisabled(false);
    ui->saveButton->setDisabled(false);
    ui->console->setDisabled(false);
}

void MainWindow::waitInput() {
    ui->console->setText("? ");
    onInputStmt = true;
    ui->console->setDisabled(false);
}

void MainWindow::finishInput() {
    onInputStmt = false;
    ui->console->clear();
    if (isRunning) {
        ui->console->setDisabled(true);
    }
}

void MainWindow::on_console_cursorPositionChanged(int oldPos, int newPos)
{
    if (onInputStmt && newPos < 2) {
        auto currentText = ui->console->text();
        if (currentText.length() > 2) {
            ui->console->setReadOnly(true);
        } else {
            ui->console->setText("? ");
        }

    } else {
        ui->console->setReadOnly(false);
    }
}

void MainWindow::clearResult() {
    ui->resultDisplay->clear();
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save file"), "./", tr("All(*.*)"));

    QString str = ui->codeDisplay->toPlainText();
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(str.toUtf8());
    file.close();
}

void MainWindow::errorAppendRow(QString str) {
    ui->errorDisplay->append(str);
}

void MainWindow::clearError() {
    ui->errorDisplay->clear();
}

void MainWindow::scrollErrorDisplayToTop() {
    ui->errorDisplay->moveCursor(QTextCursor::Start);
}

void MainWindow::clearCode() {
    ui->codeDisplay->clear();
}

void MainWindow::on_helpButton_clicked()
{
    Basic::getInstance().runCommand(CommandType::HELP);
}

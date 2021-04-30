#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Basic.h"

MainWindow& MainWindow::getInstance() {
    static MainWindow w;
    return w;
}

MainWindow::~MainWindow() {
    delete ui;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , state(State::IDLE), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statementDisplay->setTabStopWidth(4 * fontMetrics().width(' '));
    this->setWindowTitle("GuiBasic");

    QDesktopWidget desktop;

    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();
    int screenWidth = desktop.screen()->width();
    int screenHeight = desktop.screen()->height();

    this->setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);
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

void MainWindow::codeAppendRow(const QString& str) {
    ui->codeDisplay->append(str);
}

void MainWindow::statementAppendRow(const QString& str) {
    ui->statementDisplay->append(str);
}

void MainWindow::resultAppendRow(const QString& str) {
    ui->resultDisplay->append(str);
}

void MainWindow::environmentAppendRow(const QString& str) {
    ui->environmentDisplay->append(str);
}


void MainWindow::on_clearButton_clicked()
{
    Basic& basic = Basic::getInstance();
    basic.reset();
    basic.clearEnvironment();
    clearDisplays();
}


void MainWindow::clickRunButton() {
    on_runButton_clicked();
}

void MainWindow::clickLoadButton() {
    on_loadButton_clicked();
}

void MainWindow::clickClearButton() {
    on_clearButton_clicked();
}

void MainWindow::clickSaveButton() {
    on_saveButton_clicked();
}

void MainWindow::clickHelpButton() {
    on_helpButton_clicked();
}

void MainWindow::clickDebugButton() {
    on_debugButton_clicked();
}

void MainWindow:: clearDisplays() {
    ui->codeDisplay->clear();
    ui->resultDisplay->clear();
    ui->statementDisplay->clear();
    ui->errorDisplay->clear();
    ui->environmentDisplay->clear();
}

void MainWindow::on_console_returnPressed()
{
    QString str = ui->console->text().trimmed();
    ui->console->clear();

    if (state != State::INPUT) {
        clearRuntimeDisplays();
        Basic::getInstance().handleRawInstruction(str);
    } else {
        str = str.mid(2);
        emit sendInput(str);
    }
}

void MainWindow::clearStatement() {
    ui->statementDisplay->clear();
}

void MainWindow::clearEnvironment() {
    ui->environmentDisplay->clear();
}

void MainWindow::clearRuntimeDisplays() {
    clearResult();
    clearStatement();
    clearError();
}

void MainWindow::on_runButton_clicked()
{
    setRunningModeUI();

    if (state == State::IDLE) {
        clearResult();
        clearStatement();
        clearError();
        state = State::RUN;
        Basic::getInstance().interpretAll();
    } else {
        state = State::RUN;
        Basic::getInstance().interpretRest();
    }

    state = State::IDLE;
    setIdleModeUI();
}

void MainWindow::setRunningModeUI() {
    clearResult();
    clearStatement();
    clearError();
    this->setWindowTitle("GuiBasic (Running)");
    ui->runButton->setDisabled(true);
    ui->clearButton->setDisabled(true);
    ui->loadButton->setDisabled(true);
    ui->saveButton->setDisabled(true);
    ui->console->setDisabled(true);
    ui->debugButton->setDisabled(true);
}

void MainWindow::setIdleModeUI() {
    ui->debugButton->setText("调试(DEBUG)");
    this->setWindowTitle("GuiBasic");
    ui->runButton->setDisabled(false);
    ui->clearButton->setDisabled(false);
    ui->loadButton->setDisabled(false);
    ui->saveButton->setDisabled(false);
    ui->console->setDisabled(false);
    ui->debugButton->setDisabled(false);
}

void MainWindow::setDebugModeUI() {
    clearResult();
    clearStatement();
    clearError();
    ui->debugButton->setText("单步执行(STEP)");
    this->setWindowTitle("GuiBasic (Debugging)");
    ui->clearButton->setDisabled(true);
    ui->loadButton->setDisabled(true);
    ui->saveButton->setDisabled(true);
    ui->console->setDisabled(true);
}

void MainWindow::waitInput() {
    ui->console->setText("? ");
    prevState = state;
    state = State::INPUT;
    ui->console->setDisabled(false);
}

void MainWindow::finishInput() {
    state = prevState;
    ui->console->clear();
    if (state == State::RUN || state == State::DEBUG) {
        ui->console->setDisabled(true);
    }
}

void MainWindow::finishDebug() {
    state = State::IDLE;
    setIdleModeUI();
    Basic::getInstance().finishDebug();
}

void MainWindow::on_console_cursorPositionChanged(int oldPos, int newPos)
{
    if (state == INPUT && newPos < 2) {
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

void MainWindow::errorAppendRow(const QString& str) {
    ui->errorDisplay->append(str);
}

void MainWindow::scrollErrorDisplayToTop() {
    ui->errorDisplay->moveCursor(QTextCursor::Start);
}

void MainWindow::clearResult() {
    ui->resultDisplay->clear();
}

void MainWindow::clearError() {
    ui->errorDisplay->clear();
}

void MainWindow::clearCode() {
    ui->codeDisplay->clear();
}

void MainWindow::on_helpButton_clicked() {
    clearError();
    errorAppendRow(HELP_MESSAGE);
    scrollErrorDisplayToTop();
}

QTextCursor MainWindow::getCodeDisplayerCursor() {
    return QTextCursor(ui->codeDisplay->document());
}

void MainWindow::on_debugButton_clicked() {
    if (state == State::IDLE) {
        state = State::DEBUG;
        setDebugModeUI();
        Basic::getInstance().startDebug();
    } else {
        Basic::getInstance().debugStep();
    }
}

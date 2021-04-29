#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "consts.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool isRunning;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    MainWindow(MainWindow &other) = delete;
    void operator=(const MainWindow &) = delete;
    static MainWindow& getInstance();

private slots:
    void on_loadButton_clicked();

    void on_clearButton_clicked();

    void on_console_returnPressed();

    void on_runButton_clicked();

    void on_console_cursorPositionChanged(int arg1, int arg2);

    void on_saveButton_clicked();

    void on_helpButton_clicked();

public:
    void codeAppendRow(QString str);

    void statementAppendRow(QString str);

    void resultAppendRow(QString str);

    void errorAppendRow(QString str);

    void clickClearButton();

    void clickLoadButton();

    void clickRunButton();

    void clearDisplays();

    void clearResult();

    void clearCode();

    void clearStatement();

    void clearError();

    void scrollErrorDisplayToTop();

signals:
    void sendInput(int);

    void sendInvalidInput();

public:
    void disableInput();

    void enableInput();

    void waitInput();

    void finishInput();

    void setCodeDisplayHighlight(QList<QTextEdit::ExtraSelection>&);

    QTextCursor getCodeDisplayerCursor();
private:
    Ui::MainWindow *ui;

    bool onInputStmt;
};
#endif // MAINWINDOW_H

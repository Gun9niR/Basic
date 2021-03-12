#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
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

public:
    void codeAppendRow(QString str);

    void statementAppendRow(QString str);

    void resultAppendRow(QString str);

    void clickClearButton();

    void clickLoadButton();

    void clearDisplays();

    void clearResult();

signals:
    void sendInput(int);

public:
    void disableInput();

    void enableInput();

    void waitInput();

    void finishInput();

private:
    Ui::MainWindow *ui;

    bool onInputStmt;
};
#endif // MAINWINDOW_H

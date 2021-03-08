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

public slots:
    void codeAppendRow(QString str);

    void statementAppendRow(QString str);

    void resultAppendRow(QString str);

    void clickClearButton();

    void clearDisplays();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

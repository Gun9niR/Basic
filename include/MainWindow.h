#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "consts.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    typedef enum {
        RUN, DEBUG, IDLE, INPUT
    } State;

private:
    Ui::MainWindow *ui;
    State state, prevState;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void disableAllButtons();

    void enableAllButtons();

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

    void on_debugButton_clicked();

public:
    void codeAppendRow(const QString& str);

    void statementAppendRow(const QString& str);

    void resultAppendRow(const QString& str);

    void errorAppendRow(const QString& str);

    void environmentAppendRow(const QString& str);

    void clickRunButton();

    void clickLoadButton();

    void clickClearButton();

    void clickHelpButton();

    void clickSaveButton();

    void clickDebugButton();

    void clearDisplays();

    void clearRuntimeDisplays();

    void clearResult();

    void clearCode();

    void clearStatement();

    void clearError();

    void clearEnvironment();

    void scrollErrorDisplayToTop();

    void setRunningModeUI(bool);

    void setIdleModeUI();

    void setDebugModeUI(bool);

    void setInputModeUI();

    void waitInput();

    void finishInput();

    void finishDebug();

    QTextCursor getCodeDisplayerCursor();

signals:
    void sendInput(const QString&);
};
#endif // MAINWINDOW_H

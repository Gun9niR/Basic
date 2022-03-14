QT       += \
    core gui \
    concurrent \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/Basic.cpp \
    src/Environment.cpp \
    src/Exception.cpp \
    src/Expr.cpp \
    src/Interpreter.cpp \
    src/MainWindow.cpp \
    src/Parser.cpp \
    src/Scanner.cpp \
    src/Stmt.cpp \
    src/Token.cpp \
    src/Value.cpp \
    src/consts.cpp \
    src/main.cpp

HEADERS += \
    include/Basic.h \
    include/Environment.h \
    include/Exception.h \
    include/Expr.h \
    include/Interpreter.h \
    include/MainWindow.h \
    include/Parser.h \
    include/Scanner.h \
    include/Stmt.h \
    include/Token.h \
    include/Value.h \
    include/consts.h \
    include/util.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    programs/fibonacci.basic \
    programs/infiloop \
    programs/test.basic \
    programs/test_scan.basic

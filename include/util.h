#ifndef UTIL_H
#define UTIL_H

#include "consts.h"

inline void setCursorY(QTextCursor &cursor, int y) {
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor, y);
}

inline bool isInputString(const QString& inputStr) {
    int len = inputStr.length();
    if (len < 2) {
        return false;
    }
    QString content = inputStr.mid(1, len - 2);

    return !(content.contains('"') || content.contains('\'')) &&
            ((inputStr.startsWith('"') && inputStr.endsWith('"')) ||
            (inputStr.startsWith('\'') && inputStr.endsWith('\'')));
}

inline void showMessage(const QString& title, const QString& content) {
    QMessageBox::information(nullptr, title, content,
                             QMessageBox::Yes, QMessageBox::Yes);
}

inline int getDigits(int x) {
    int ret = 0;
    while (x) { ++ret; x /= 10; }
    return ret;
}

#endif // UTIL_H

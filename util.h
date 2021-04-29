#ifndef UTIL_H
#define UTIL_H

#include "consts.h"

inline void setCursorY(QTextCursor &cursor, int y) {
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, y);
}

inline bool isInputString(const QString& inputStr) {
    int len = inputStr.length();
    if (len < 2) {
        return false;
    }
    QStringRef content(&inputStr, 1, len - 2);

    return !(content.contains('"') || content.contains('\'')) &&
            ((inputStr.startsWith('"') && inputStr.endsWith('"')) ||
            (inputStr.startsWith('\'') && inputStr.endsWith('\'')));
}
#endif // UTIL_H

#ifndef UTIL_H
#define UTIL_H

#include "consts.h"

inline void setCursorY(QTextCursor &cursor, int y) {
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, y);
}
#endif // UTIL_H

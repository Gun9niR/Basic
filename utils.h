#ifndef UTILS_H
#define UTILS_H

int getDigits(int x) {
    int ret = 0;

    while (x) {
        ++ret;
        x /= 10;
    }

    return ret;
}

#endif // UTILS_H

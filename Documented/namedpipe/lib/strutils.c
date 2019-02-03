#include "strutils.h"

void join(char *dest, const char *path1, const char *path2) {
        int slashes = 0;
        if (path1[strlen(path1) - 1] == '/') slashes ++;
        if (path2[0] == '/') slashes ++;

        if (slashes > 1) {
                memmove(dest, path1, strlen(path1) - 1);
                memmove(dest + strlen(path1) - 1, path2, strlen(path2));
        }
        else if (slashes == 0) {
                memmove(dest, path1, strlen(path1));
                *(dest + strlen(path1)) = '/';
                memmove(dest + strlen(path1) + 1, path2, strlen(path2));
        }
        else {
                memmove(dest, path1, strlen(path1));
                memmove(dest + strlen(path1), path2, strlen(path2));
        }
}

void divide(const char *origin, char *out1, char delim, char *out2) {
        int delimIndex = (int)(strchr(origin, delim) - origin);

        memcpy(out1, origin, delimIndex);
        memcpy(out2, origin + delimIndex + 1, strlen(origin) - delimIndex);
}

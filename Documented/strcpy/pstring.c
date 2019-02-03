#include "pstring.h"

char * pstrcpy(char * __restrict destination, char * __restrict source) {
        if (destination == NULL) {
                // destination is not allocated.
                return NULL;
        }

        char * origin = source;
        while(*destination++ = *source++);

        return origin;
}

#ifndef _FONT_H
#define _FONT_H

/**
 * Bitmap font.
 * Version 1.0 20190526
 * Powered by font-maker (https://github.com/potados99/font-maker)
 */

const unsigned int font[28][24] = {
    {
        /* a */
        0x000000, 0x000000, 0x000000, 0x007F00,
        0x01C100, 0x030180, 0x040180, 0x080180,
        0x180180, 0x100180, 0x100080, 0x200080,
        0x200080, 0x2000C0, 0x2001C0, 0x200140,
        0x200360, 0x200230, 0x300418, 0x18380C,
        0x0FE000, 0x000000, 0x000000, 0x000000
    },
    {
        /* b */
        0x000000, 0x010000, 0x010000, 0x010000,
        0x010000, 0x010000, 0x010000, 0x010000,
        0x010000, 0x013F80, 0x01C0C0, 0x018060,
        0x010020, 0x010020, 0x010020, 0x010020,
        0x010020, 0x010020, 0x010020, 0x010020,
        0x0100E0, 0x010180, 0x01FE00, 0x000000
    },
    {
        /* c */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x007800, 0x038780, 0x0600C0, 0x040040,
        0x080000, 0x180000, 0x100000, 0x100000,
        0x100000, 0x100000, 0x080000, 0x080040,
        0x0C0040, 0x0600C0, 0x038180, 0x00FF00
    },
    {
        /* d */
        0x000000, 0x000000, 0x000080, 0x000080,
        0x000080, 0x000080, 0x000080, 0x000080,
        0x000080, 0x000080, 0x000080, 0x007C80,
        0x01CF80, 0x030080, 0x060080, 0x040080,
        0x040080, 0x040080, 0x040080, 0x040080,
        0x020180, 0x030380, 0x01FEC0, 0x000000
    },
    {
        /* e */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x003C00, 0x01E700, 0x030180, 0x020080,
        0x0600C0, 0x040040, 0x0400C0, 0x07FF80,
        0x040000, 0x060000, 0x020000, 0x030000,
        0x01C180, 0x007F80, 0x000000, 0x000000
    },
    {
        /* f */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000E00,
        0x001B00, 0x001900, 0x001000, 0x001000,
        0x001000, 0x00FE00, 0x001000, 0x001000,
        0x001000, 0x001000, 0x001000, 0x001000,
        0x001000, 0x001000, 0x001000, 0x000000
    },
    {
        /* g */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x003E00, 0x006380, 0x00C080, 0x008040,
        0x008040, 0x008040, 0x008040, 0x00C0C0,
        0x0079C0, 0x000F40, 0x004040, 0x004040,
        0x004080, 0x006180, 0x001F00, 0x000000
    },
    {
        /* h */
        0x000000, 0x000000, 0x010000, 0x010000,
        0x010000, 0x010000, 0x010000, 0x010000,
        0x010000, 0x010000, 0x013E00, 0x016300,
        0x01C180, 0x010080, 0x010080, 0x010080,
        0x010080, 0x010080, 0x010080, 0x010080,
        0x010080, 0x010080, 0x010080, 0x000000
    },
    {
        /* i */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x001000, 0x001000,
        0x000000, 0x000000, 0x003000, 0x001000,
        0x001000, 0x001000, 0x001000, 0x001000,
        0x001000, 0x001000, 0x001000, 0x001000,
        0x001000, 0x001000, 0x001800, 0x000000
    },
    {
        /* j */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000800,
        0x000800, 0x000000, 0x000C00, 0x000800,
        0x000800, 0x000800, 0x000800, 0x000800,
        0x000800, 0x000800, 0x000800, 0x020800,
        0x031800, 0x01F000, 0x000000, 0x000000
    },
    {
        /* k */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x008000, 0x008000, 0x008000, 0x008000,
        0x008080, 0x008180, 0x008300, 0x008600,
        0x008C00, 0x009800, 0x00B000, 0x00F000,
        0x00C800, 0x008C00, 0x008600, 0x008300,
        0x008100, 0x008180, 0x008080, 0x000000
    },
    {
        /* l */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x007000,
        0x001000, 0x001000, 0x001000, 0x001000,
        0x001000, 0x001000, 0x001000, 0x001000,
        0x001000, 0x001000, 0x001000, 0x001000,
        0x001000, 0x001000, 0x001C00, 0x000000
    },
    {
        /* m */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x00E380, 0x03BEC0, 0x010840,
        0x010840, 0x010840, 0x010840, 0x010840,
        0x010840, 0x010840, 0x010840, 0x000000
    },
    {
        /* n */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x003C00,
        0x01E600, 0x00C300, 0x008100, 0x008100,
        0x008100, 0x008100, 0x008100, 0x008100,
        0x008100, 0x008100, 0x008100, 0x000000
    },
    {
        /* o */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x007E00,
        0x018300, 0x010100, 0x020180, 0x020080,
        0x020080, 0x020080, 0x020080, 0x020080,
        0x010180, 0x00FF00, 0x000000, 0x000000
    },
    {
        /* p */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x003E00, 0x006300, 0x004080,
        0x004080, 0x004080, 0x004080, 0x004180,
        0x007F00, 0x004000, 0x004000, 0x004000,
        0x004000, 0x004000, 0x004000, 0x000000
    },
    {
        /* q */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x007800, 0x00CE00, 0x010300, 0x030100,
        0x020100, 0x020100, 0x020100, 0x030300,
        0x018700, 0x007900, 0x000100, 0x000100,
        0x000100, 0x000100, 0x000100, 0x000100
    },
    {
        /* r */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x004F00, 0x005800,
        0x007000, 0x006000, 0x004000, 0x004000,
        0x004000, 0x004000, 0x004000, 0x004000,
        0x004000, 0x004000, 0x004000, 0x000000
    },
    {
        /* s */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x007C00, 0x00C600, 0x018300, 0x010100,
        0x010000, 0x018000, 0x00C000, 0x007C00,
        0x000600, 0x000100, 0x000100, 0x000100,
        0x010300, 0x018600, 0x00FC00, 0x000000
    },
    {
        /* t */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x001000, 0x001000, 0x001000, 0x001000,
        0x00FE00, 0x001000, 0x001000, 0x001000,
        0x001000, 0x001000, 0x001000, 0x001000,
        0x001000, 0x001800, 0x000F00, 0x000000
    },
    {
        /* u */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x020080, 0x020080, 0x020080,
        0x020080, 0x020080, 0x020080, 0x020080,
        0x020080, 0x020080, 0x020080, 0x030180,
        0x01C380, 0x00FE80, 0x000000, 0x000000
    },
    {
        /* v */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x020040,
        0x020040, 0x0300C0, 0x010080, 0x018180,
        0x008100, 0x008100, 0x00C300, 0x004200,
        0x006600, 0x003400, 0x001800, 0x000000
    },
    {
        /* w */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x020840, 0x021840, 0x021040, 0x021040,
        0x021040, 0x021080, 0x021080, 0x031180,
        0x01BB00, 0x00EE00, 0x000000, 0x000000
    },
    {
        /* x */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x040080,
        0x060180, 0x038300, 0x00C600, 0x006C00,
        0x003800, 0x007800, 0x00CC00, 0x018400,
        0x030600, 0x060300, 0x040180, 0x000000
    },
    {
        /* y */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x010100, 0x010100, 0x010100, 0x018100,
        0x008300, 0x00C200, 0x004600, 0x006400,
        0x001C00, 0x001800, 0x003000, 0x002000,
        0x004000, 0x00C000, 0x008000, 0x000000
    },
    {
        /* z */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x07FF00,
        0x000300, 0x000600, 0x000C00, 0x003800,
        0x006000, 0x00C000, 0x018000, 0x030000,
        0x060000, 0x07FF80, 0x000000, 0x000000
    },
    {
        /* . */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x030000, 0x030000, 0x000000, 0x000000
    },
    {
        /* space */
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000,
        0x000000, 0x000000, 0x000000, 0x000000
    }
};

static inline int font_index(char c) {
    /**
     * ASCII
     * alphabet: 97(a) ~ 122(z)
     * space: 32
     * dot: 46
     */
    
    if (c == 32) {
        /**
         * space
         */
        return 27;
    }
    else if (c == 46) {
        /**
         * dot
         */
        return 26;
    }
    else if (c >= 97 && c <= 122) {
        /**
         * alphabet
         */
        return c - 97;
    }
    else {
        return -1;
    }
}

#endif /* _FONT_H */
#pragma once

#include "color.hpp"

#ifndef FUNIT_DEFAULT_BG_COLOR
#define FUNIT_DEFAULT_BG_COLOR (int) 0x000000
#endif

#ifndef FUNIT_DEFAULT_FG_COLOR
#define FUNIT_DEFAULT_FG_COLOR (int) 0xFFFFFF
#endif

#ifndef FUNIT_DEFAULT_CHAR
#define FUNIT_DEFAULT_CHAR 0x0
#endif

namespace tren {

    /**
     * Terminal frame pixel
     */
    struct FrameUnit
    {
        char m_char = FUNIT_DEFAULT_CHAR;
        color m_bg = FUNIT_DEFAULT_BG_COLOR;
        color m_fg = FUNIT_DEFAULT_FG_COLOR;
    };
}
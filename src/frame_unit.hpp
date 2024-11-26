#pragma once

#include "color.hpp"

#ifndef FUNIT_DEFAULT_COLOR
#define FUNIT_DEFAULT_COLOR (int) 0xFFFFFF
#endif

#ifndef FUNIT_DEFAULT_CHAR
#define FUNIT_DEFAULT_CHAR 0x20
#endif

namespace tren {

    /**
     * Terminal frame pixel
     */
    struct FrameUnit
    {
        char m_char = FUNIT_DEFAULT_CHAR;
        color m_color = FUNIT_DEFAULT_COLOR;
    };
}
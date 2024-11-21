#include "color.hpp"

namespace tren {

    color::color() : color(0, 0, 0)
    {
    }

    color::color(unsigned short r, unsigned short g, unsigned short b)
        : r(r), g(g), b(b)
    {
    }

    color::color(unsigned int hex)
        : r((hex >> 16) & 0xFF), g((hex >> 8) & 0xFF), b(hex & 0xFF)
    {
    }

    color color::of(unsigned int hex) {
        return color(hex);
    }

    bool color::operator==(const color& rhs)
    {
        return this->r == rhs.r && this->g == rhs.g && this->b == rhs.b;
    }

    bool color::operator!=(const color& rhs)
    {
        return !(*this == rhs);
    }

    bool operator==(const color& lhs, const color& rhs)
    {
        return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
    }

    bool operator!=(const tren::color& lhs, const tren::color& rhs)
    {
        return !(lhs == rhs);
    }
}
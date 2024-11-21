#pragma once

namespace tren {
    /**
     * Pixel color
     */
    struct color {
        unsigned short r = 0;
        unsigned short g = 0;
        unsigned short b = 0;

        color();
        color(unsigned short r, unsigned short g, unsigned short b);
        color(unsigned int hex);

        /**
         * Convert from hex to color
         */
        static color of(unsigned int hex);

        bool operator==(const color& rhs);
        bool operator!=(const color& rhs);

        friend bool operator==(const color& lhs, const color& rhs);
        friend bool operator!=(const color& lhs, const color& rhs);
    };
}

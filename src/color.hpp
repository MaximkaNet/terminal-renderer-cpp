#pragma once

/**
 * Pixel color
 */
struct color {
    unsigned short r = 0, g = 0, b = 0;

    /**
     * Convert from hex to color
     */
    static color hex(unsigned int hex);

    bool operator==(const color& rhs);
    bool operator!=(const color& rhs);

    friend bool operator==(const color& lhs, const color& rhs);
    friend bool operator!=(const color& lhs, const color& rhs);
};
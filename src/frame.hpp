#ifndef RENDERER_FRAME_HPP // include guard
#define RENDERER_FRAME_HPP
#include <vector>

#include "frame_unit.hpp"
#include "image.hpp"

/**
 * Class represents single frame
 */
class Frame {
    // Frame width and height
    unsigned int m_width, m_height;
    // Frame buffer
    std::vector<FrameUnit> m_buffer;
public:

    /**
     * Create screen
     */
    Frame(unsigned int w, unsigned int h);

    /**
     * Clear buffer
     */
    ~Frame();

    /**
     * Create rectangle
     */
    void rect(int x, int y, unsigned int w, unsigned int h, char ch, color bg, color fg);

    /**
     * Create rectangle using predefined unit
     */
    void rect(int x, int y, unsigned int w, unsigned int h, FrameUnit& f_unit);

    /**
     * Draw image
     */
    void draw_image(int x, int y, const Image& img);

    /**
     * Set text
     */
    void set_text(int x, int y, std::string text);

    ///**
    // * Get frame unit
    // */
    //FrameUnit get_unit(unsigned int x, unsigned int y) const;

    ///**
    //* Set frame unit on the specific point
    //*/
    //void set_unit(unsigned int x, unsigned int y, const FrameUnit& u);

    /**
     * Clear screen
     */
    void clear();

    /**
     * Get width
     */
    unsigned int get_width() const;

    /**
     * Get height
     */
    unsigned int get_height() const;

    /**
     * Get frame buffer
     */
    std::vector<FrameUnit> get_buffer() const;

    /**
     * Compare two frames and get frame units that differ
     */
    std::vector<FrameUnit> compare(const Frame& other);
};
#endif //! RENDERER_FRAME_HPP
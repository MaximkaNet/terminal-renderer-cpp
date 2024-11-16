#include "renderer.hpp"

#include <fstream>

color color::hex(unsigned int hex) {
    return {
        (unsigned short)((hex >> 16) & 0xFF),
        (unsigned short)((hex >> 8) & 0xFF),
        (unsigned short)(hex & 0xFF)
    };
}

bool color::operator==(const color& rhs)
{
    return this->r == rhs.r && this->g == rhs.g && this->b == rhs.b;
}

bool color::operator!=(const color& rhs)
{
    return !(*this == rhs);
}

bool operator==(const color& lhs, const color& rhs) {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

bool operator!=(const color& lhs, const color& rhs) {
    return !(lhs == rhs);
}

FrameUnit::FrameUnit(char ch, color bg, color fg, unsigned int x, unsigned int y)
    : m_char(ch), m_x(x), m_y(y) {
    m_bg = bg;
    m_fg = fg;
}

FrameUnit::FrameUnit(char ch, color bg, unsigned int x, unsigned int y) 
    : FrameUnit(ch, bg, color::hex(DEFAULT_FOREGROUND_COLOR), x, y) {
}

FrameUnit::FrameUnit(char ch, unsigned int x, unsigned int y) 
    : FrameUnit(ch, color::hex(DEFAULT_BACKGROUND_COLOR), color::hex(DEFAULT_FOREGROUND_COLOR), x, y) {}

FrameUnit::~FrameUnit() {
    
}

void FrameUnit::set_x(unsigned int x)
{
    m_x = x;
}

void FrameUnit::set_y(unsigned int y)
{
    m_y = y;
}

void FrameUnit::set_position(unsigned int x, unsigned int y)
{
    m_x = x;
    m_y = y;
}

void FrameUnit::reset() {
    m_char = DEFAULT_FRAME_UNIT_CHAR;
    m_bg = color::hex(DEFAULT_BACKGROUND_COLOR);
    m_fg = color::hex(DEFAULT_FOREGROUND_COLOR);
}

void FrameUnit::merge(FrameUnit& rhs)
{
    m_bg = rhs.m_bg;
    m_fg = rhs.m_fg;
    m_char = rhs.m_char;
}

void FrameUnit::set_bg(color bg) {
    this->m_bg = bg;
}

void FrameUnit::set_fg(color fg) {
    this->m_fg = fg;
}

void FrameUnit::set_char(char ch) {
    this->m_char = ch;
}

std::string FrameUnit::compile() const {
    std::string u;

    // Compile foreground color
    u += "\033[38:2::";
    u += std::to_string(m_fg.r);
    u += ":";
    u += std::to_string(m_fg.g);
    u += ":";
    u += std::to_string(m_fg.b);
    u += 'm';

    // Compile background color
    u += "\033[48:2::";
    u += std::to_string(m_bg.r);
    u += ":";
    u += std::to_string(m_bg.g);
    u += ":";
    u += std::to_string(m_bg.b);
    u += 'm';

    /*if (!m_fg_ptr && !m_bg_ptr) {
        u += "\033[0m";
    }*/

    u += m_char;

    u += "\033[0m";

    return u;
}

std::string FrameUnit::compile_pos() const
{
    std::string pos = "\033[";
    pos += std::to_string(m_y + 1);
    pos += ';';
    pos += std::to_string(m_x + 1);
    pos += 'H';
    return pos;
}

bool FrameUnit::operator==(const FrameUnit& rhs) const {
    return m_x == rhs.m_x && m_y == rhs.m_y
        && m_char == rhs.m_char
        && m_fg == rhs.m_fg && m_bg == rhs.m_bg;
}

bool FrameUnit::operator!=(const FrameUnit& rhs) const {
    return !(*this == rhs);
}

FrameUnit& FrameUnit::operator=(const FrameUnit& rhs) {

    if (this == &rhs) return *this; // self guard

    this->m_x = rhs.m_x;
    this->m_y = rhs.m_y;
    this->m_char = rhs.m_char;
    this->m_bg = rhs.m_bg;
    this->m_fg = rhs.m_fg;

    return *this;
}

FrameUnit& FrameUnit::operator+=(const FrameUnit& rhs) {
    this->m_char = rhs.m_char;
    this->m_bg = rhs.m_bg;
    this->m_fg = rhs.m_fg;
    return *this;
}

Frame::Frame(unsigned int w, unsigned int h) {
    this->m_width = w;
    this->m_height = h;
    for (size_t j = 0; j < h; j++) {
        for (size_t i = 0; i < w; i++) {
            m_buffer.push_back(FrameUnit(DEFAULT_FRAME_UNIT_CHAR, i, j));
        }
    }
}

Frame::~Frame() {}

void Frame::rect(int x, int y, unsigned int w, unsigned int h, char ch, color bg, color fg)
{
    this->rect(x, y, w, h, FrameUnit(ch, bg, fg, 0, 0));
}

void Frame::rect(int x, int y, unsigned int w, unsigned int h, FrameUnit& f_unit) {
    int pos_x = x;
    int pos_y = y;
    for (unsigned int j = 0; j < h; j++) {
        if (pos_y > (int) m_height - 1) break;
        else if (pos_y < 0) continue;
        for (unsigned int i = 0; i < w; i++) {
            pos_x = x + i;
            // Pixel by x axis on screen?
            if (pos_x > (int) m_width - 1) break;
            else if (pos_x < 0) continue;

            unsigned int pos = pos_x + pos_y * m_width;
            m_buffer[pos].merge(f_unit);
        }
    }
}

void Frame::draw_image(int x, int y, const Image& img)
{
    unsigned int w = img.get_width();
    unsigned int h = img.get_height();
    auto img_units = img.get_frame_units();

    for (unsigned int j = 0; j < h; j++) {
        for (unsigned int i = 0; i < w; i++) {
            // Get positon of pixel
            int pos_x = i + x;
            int pos_y = j + y;
            // Pixel on screen ?
            if (pos_x < 0 || pos_y < 0 || pos_x > m_width - 1 || pos_y > m_height - 1) 
                continue;
            // Calculate indexes
            unsigned int index = pos_x + pos_y * m_width;
            unsigned int img_index = i + j * w;
            // Insert frame unit from image to frame buffer
            // m_buffer[index] = img_units[img_index]; // cannot be applyed to non-same coordinates
            m_buffer[index] += img_units[img_index];
        }
    }
}

void Frame::set_text(int x, int y, std::string text)
{
    int pos_x = x;
    int pos_y = y;
    for (const char ch: text) {
        if (ch == '\n') {
            pos_y++;
            pos_x = x;
            continue;
        }
        if (pos_x > m_width - 1 || pos_x < 0 || pos_y < 0) continue;
        if (pos_y > (int) m_height - 1) break;
        unsigned int pos = pos_y * m_width + pos_x;
        m_buffer[pos] = FrameUnit(ch, pos_x, pos_y);
        pos_x++;
    }
}

//FrameUnit Frame::get_unit(unsigned int x, unsigned int y) const {
//    if(x >= m_width || y >= m_height) return ;
//    return m_buffer[x + y * m_width];
//}

void Frame::clear() {
    for(auto& unit: m_buffer) {
        // reset unit
        unit.reset();
    }
}

unsigned int Frame::get_width() const
{
    return m_width;
}

unsigned int Frame::get_height() const
{
    return m_height;
}

std::vector<FrameUnit> Frame::get_buffer() const
{
    return m_buffer;
}

std::vector<FrameUnit> Frame::compare(const Frame& other) {
    if (m_width != other.m_width && m_height != other.m_height)
        throw std::exception("Frames must have same sizes");

    if (m_buffer.size() != m_width * m_height)
        throw std::exception("Buffer has another dimention");

    std::vector<FrameUnit> out;

    for (size_t j = 0; j < m_height; j++) {
        for (size_t i = 0; i < m_width; i++) {
            size_t pos = i + (m_width * j);
            if (m_buffer[pos] != other.m_buffer[pos]) {
                out.push_back(other.m_buffer[pos]);
            }
        }
    }
    return out;
}

void TerminalRenderer::set_width(unsigned int w)
{
    m_width = w;
}

void TerminalRenderer::set_height(unsigned int h)
{
    m_height = h;
}

TerminalRenderer::TerminalRenderer() : TerminalRenderer(0, 0) {}

TerminalRenderer::TerminalRenderer(unsigned int w, unsigned int h)
{
    this->set_width(w);
    this->set_height(h);
}

TerminalRenderer::~TerminalRenderer()
{
    if (m_current) delete m_current;
    if (m_prev) delete m_prev;
}

void TerminalRenderer::resize(unsigned int w, unsigned int h) {
    if (m_current) delete m_current;
    m_current = nullptr;
    this->set_width(w);
    this->set_height(h);
}

unsigned int TerminalRenderer::get_width() const {
    return m_width;
}

unsigned int TerminalRenderer::get_height() const {
    return m_height;
}

Frame* TerminalRenderer::new_frame()
{
    if (m_prev) delete m_prev;
    m_prev = m_current;
    m_current = new Frame(m_width, m_height);
    return m_current;
}

Frame* TerminalRenderer::get_current() const {
    return m_current;
}

void TerminalRenderer::render() {
    if (m_current == nullptr) return;

    std::stringstream ss;
    std::vector<FrameUnit> updated_units = m_prev != nullptr ? m_prev->compare(*m_current) : m_current->get_buffer();
    for (const FrameUnit& u : updated_units) {
        ss << u.compile_pos() << u.compile();
    }
    printf(ss.str().c_str());
}

Image::Image() : m_width(0), m_height(0)
{
}

Image::Image(std::string path) : Image() {
    if (path_exists(path)) {
        read(path);
    }
    else {
        std::string msg = "Cannot open image: ";
        msg += path;
        throw std::exception(msg.c_str());
    }
}

Image::~Image() {
    // Clear colors
    /*for (auto& u : m_frame_units) {
        u.destroy_colors();
    }*/
}

void Image::load(std::string path)
{
    if (!path_exists(path)) {
        std::string msg = "Cannot open image: ";
        msg += path;
        throw std::exception(msg.c_str());
    }
    read(path);
}

void Image::read(std::string path) {
    std::ifstream f;
    f.open(path, std::ios::binary);
    if (f.fail()) {
        f.close();
        return;
    }

    // Read image size

    f.read(reinterpret_cast<char*>(&m_width), sizeof m_width);
    f.read(reinterpret_cast<char*>(&m_height), sizeof m_height);

    // Read image data

    for (int j = 0; j < m_height; j++) {
        for (int i = 0; i < m_width; i++) {
            color bg_col;
            color fg_col;
            unsigned char ch = 0;

            f.read(reinterpret_cast<char*>(&ch), sizeof ch);
            // background
            f.read(reinterpret_cast<char*>(&bg_col), sizeof color);
            // foreground
            f.read(reinterpret_cast<char*>(&fg_col), sizeof color);

            m_frame_units.push_back(FrameUnit(ch, bg_col, fg_col, i, j));
        }
    }

    f.close();
}

bool Image::path_exists(std::string p) {
    std::ifstream f;
    f.open(p, std::ios::binary);
    if (f.fail()) {
        f.close();
        return false;
    }
    f.close();
    return true;
}

std::vector<FrameUnit> Image::get_frame_units() const {
    return m_frame_units;
}

unsigned int Image::get_width() const {
    return m_width;
}

unsigned int Image::get_height() const {
    return m_height;
}
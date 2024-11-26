#include "utils.hpp"

std::vector<ComparedFrameUnit> compareBuffers(int width, int height, tren::FrameUnit*& buff, tren::FrameUnit*& virt_buff) {
	std::vector<ComparedFrameUnit> out;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {

			int pos = i + j * width;

			tren::FrameUnit* real = buff + pos;
			tren::FrameUnit* virt = virt_buff + pos;

			if (!areFrameUnitsEqual(*real, *virt)) {
				out.push_back(ComparedFrameUnit{ i, j, *virt });
			}
		}
	}

	return out;
}

bool areFrameUnitsEqual(const tren::FrameUnit& l, const tren::FrameUnit& r) {
	return l.m_char == r.m_char && l.m_color == r.m_color;
}

std::string compileFrameUnit(const tren::FrameUnit& ref, int x, int y, int offX, int offY)
{
	std::string u = "\033[" + compilePos(x + offX, y + offY) + "H";

	/*const tren::color& bg = ref.m_bg;
	const tren::color& fg = ref.m_fg;*/

	// Compile foreground color
	u += "\033[38:2::" + compileColor(ref.m_color) + "m";
	// Compile background color
	//u += "\033[48:2::" + compileColor(bg) + "m";

	u += ref.m_char;
	u += "\033[0m";

	return u;
}

std::string compilePos(int x, int y) {
	return std::to_string(y) + ";" + std::to_string(x);
}

std::string compileColor(const tren::color& color) {
	std::string s;
	s += std::to_string(color.r);
	s += ":";
	s += std::to_string(color.g);
	s += ":";
	s += std::to_string(color.b);
	return s;
}

#include "config.cpp"

#include <iostream>
#include <terminal/renderer.hpp>
#include <terminal/utils.hpp>

#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

void drawRect(int x, int y, int w, int h, char ch, tren::color bg, tren::color fg) {
	tren::PixelDef pixelDef;

	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			pixelDef.unit = tren::FrameUnit();
			pixelDef.unit.m_char = ch;
			pixelDef.unit.m_bg = bg;
			pixelDef.unit.m_fg = fg;
			pixelDef.x = x + k;
			pixelDef.y = y + j;

			tren::drawPixel(pixelDef);
		}
	}
}

struct Rect {
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	char ch = 0;
	tren::color bg;
	tren::color fg;
};

int main() {

	tren::init();
	tren::raw(true);
	tren::attrOn(ATTR_ALT_SCREEN);
	tren::attrOff(ATTR_SH_CURSOR);

	tren::TextDef textDef;

	tren::PixelDef pixelDef;

	std::mutex mtx;

	std::vector<Rect> rects = {
		Rect{2, 3, 2, 2, '#'},
		Rect{5, 2, 3, 3, '@'},
		Rect{5, 10, 1, 1, '@'}
	};

	std::vector<tren::color> colors = {
		0x00b4d8,
		0xe9c46a,
		0x283618,
		0xffe8d6,
		0xe63946,
		0xffb703,
		0x0f4c5c,
		0xe36414,
		0xfb8b24,
		0x9a031e,
		0x5f0f40
	};
	
	int step = 0;
	while (step < 500)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		std::lock_guard<std::mutex> l(mtx);

		tren::clear();

		for (Rect& rect : rects) {
			drawRect(rect.x, rect.y, rect.w, rect.h, rect.ch, rect.bg, rect.fg);
			rect.x++;
		}

		textDef.content = "Current step: " + std::to_string(step);

		tren::drawText(textDef);

		tren::refresh();

		Rect rect;
		rect.x = rand() % 10;
		rect.y = rand() % 50;
		rect.w = rand() % 30;
		rect.h = rand() % 10;
		rect.ch = rand() % 10 + 97;
		rect.fg = colors[rand() % colors.size()];

		rects.push_back(rect);

		step++;
	}

	tren::attrOff(ATTR_ALT_SCREEN);
	tren::attrOn(ATTR_SH_CURSOR);
	tren::raw(false);
	tren::endwin();

	return 0;
}
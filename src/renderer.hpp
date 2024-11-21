#pragma once

#include "frame_unit.hpp"

/**
* Terminal renderer namespace
*/
namespace tren {

	/**
	* Initialize the screen
	*/
	void init();

	/**
	* Initalize the screen
	*/
	void init(int w, int h);

	/**
	* Compare virtual screen and real screen
	* than draw sceen changes on the real screen
	*/
	void refresh();

	/**
	* Clear real and virtual buffer
	*/
	void endwin();

} // tren
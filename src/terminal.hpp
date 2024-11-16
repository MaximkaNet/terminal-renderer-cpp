/**
* Terminal manager
*/

#include <iostream>
#include <vector>
#include <string>

namespace terminal {
	/**
	 * Set raw mode for terminal
	 */
	void raw(bool enable);

	/**
	 * Switch to alternate screen
	 */
	void alternate_screen(bool enable);

	/**
	 * Display cursor
	 */
	void display_cursor(bool enable);

	/**
	 * Get window size
	 * 
	 * @returns pair (columns/width, lines/height)
	 */
	std::pair<unsigned short, unsigned short> get_win_size();
};
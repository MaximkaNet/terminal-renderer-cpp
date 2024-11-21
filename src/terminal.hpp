#pragma once

/**
* Terminal manager
*/

#include <utility>

// Alternate screen
#define ATTR_ALT_SCREEN 1049
// Show cursor
#define ATTR_SH_CURSOR 25

namespace tren {
	/**
	 * Set raw mode for terminal
	 */
	void raw(bool enable);

	/**
	* Enable attribute
	*/
	void attrOn(int attr);

	/**
	* Disable attribute
	*/
	void attrOff(int attr);

	/**
	 * Get window size
	 * 
	 * @returns pair (columns, lines)
	 */
	std::pair<int, int> getScreenSize();
}
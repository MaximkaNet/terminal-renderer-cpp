#include "terminal.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif
void terminal::raw(bool enable) {
	#ifndef _WIN32
	static struct termios orig_term;
	if(enable) {
		tcgetattr(STDIN_FILENO, &orig_term);
		// atexit(disableRawMode);
		
		struct termios raw = orig_term;
		raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON | ICRNL);
		raw.c_oflag &= ~(OPOST);
		raw.c_cflag |= (CS8);
		
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	} else {
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_term);
	}
	#else
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);

	if (enable) {
		mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
	}
	else {
		mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
	}

	SetConsoleMode(hStdin, mode);
	#endif
}

void terminal::alternate_screen(bool enable) {
	std::cout << "\033[?1049" << (enable ? "h" : "l") << std::flush; 
}


void terminal::display_cursor(bool enable) {
	std::cout << "\033[?25" << (enable ? "h" : "l") << std::flush;
}

std::pair<unsigned short, unsigned short> terminal::get_win_size() {
	unsigned short cols, rows;
	#ifndef _WIN32
	winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		// Error getting terminal size ...
		// std::cerr << "Error getting terminal size" << std::endl;
		w.ws_col = 0;
		w.ws_row = 0;
	}
	cols = w.ws_col;
	rows = w.ws_row;
	#else
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	#endif
	return std::make_pair(cols, rows);
}
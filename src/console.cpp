// Functions for interacting with the console
// EX - Printing and enabling ansi Codes

#include <windows.h>
#include <string>
#include <iostream>

namespace console {
    void enableAnsiCodes() {
        DWORD l_mode;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleMode(hStdout, &l_mode);
        SetConsoleMode(hStdout, l_mode | 0x0004 | 0x0008);
    }

    // Prints text with color using ansi codes
    void debugPrint(const std::string& text, int colorCode, const std::string& stringEnd = "\n") {
        std::cout << "\x1B[" << colorCode << "m" << text << "\033[0m" << stringEnd;
    }

    // Prints text using DebugPrint and exits the program after a pause
    void errorPrint(const std::string& text, int colorCode, int exitCode = 0){
        debugPrint(text, colorCode);
        if (exitCode != 0) exit(exitCode);
    }
}
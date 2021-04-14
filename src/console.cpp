// Functions for interacting with the console //
// EX - Printing and enabling ansi Codes      //

#include <windows.h>
#include <string>
#include <iostream>
#include <utility>
#include <conio.h>

namespace console {
    void enableAnsiCodes() {
        DWORD l_mode;
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleMode(hStdout, &l_mode);
        SetConsoleMode(hStdout, l_mode | 0x0004 | 0x0008);
    }

    // Prints text with color using ansi codes
    void debugPrint(const std::string& text, int colorCode, std::string stringEnd = "\n") {
        std::cout << "\x1B[" << colorCode << "m" << text << "\033[0m" << stringEnd;
    }

    // Used DebugPrint to print some text then waits for the user to press a key
    void waitForKeypress(const std::string& text, int colorCode) {
        debugPrint(text, colorCode, "");
        std::cin.get();
    }

    // Prints text using DebugPrint and exits the program after a pause
    void errorPrint(const std::string& text, int colorCode, int exitCode){
        debugPrint(text, colorCode);
        exit(exitCode);
    }
}
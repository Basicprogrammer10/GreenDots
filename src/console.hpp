#ifndef GREENDOTS_CONSOLE_HPP
#define GREENDOTS_CONSOLE_HPP
namespace console {
    void enableAnsiCodes();
    void debugPrint(const std::string& text, int colorCode, std::string stringEnd = "\n");
    void errorPrint(const std::string& text, int colorCode, int exitCode);
}
#endif
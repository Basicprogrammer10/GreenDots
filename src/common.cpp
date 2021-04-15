// Common misc functions used in multiple places

#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

namespace common {
    // Split a string into a vector by a certain char
    std::vector<std::string> tokenize(std::string const &str, const char delim) {
        std::vector<std::string> out;
        size_t start;
        size_t end = 0;

        while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
        return out;
    }

    // Remove quotes and newlines from config values
    std::string cleanConfigString(const std::string& configString) {
        std::vector<std::string> quotesSplit = tokenize(configString, '"');
        std::string final;
        if (quotesSplit.size() >= 2) final = quotesSplit[1];

        return final;
    }

    // Overwrite a files content
    bool updateFile(const std::string &fileName, const std::string &text) {
        std::fstream fileHandler;
        std::string myLine;
        fileHandler.open(fileName, std::ios::in | std::ios::out);
        if (fileHandler.fail()) return false;
        fileHandler << text;
        fileHandler.close();

        return true;
    }

    // Check if file exists
    bool exists(const std::string &name) {
        if (name.empty()) return false;
        struct stat buffer{};
        return (stat(name.c_str(), &buffer) == 0);
    }

    // Returns the current date as a string (YYYY-MM-DD)
    std::string getDateAsString() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        std::string time = std::to_string(now->tm_year + 1900) + "-" +
               std::to_string(now->tm_mon + 1) + "-"
               + std::to_string(now->tm_mday);

        return time;
    }

    void sleep(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}
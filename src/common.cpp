#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <iostream>

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

    // Check if file exists
    bool exists(const std::string &name) {
        if (name.empty()) return false;
        struct stat buffer{};
        return (stat(name.c_str(), &buffer) == 0);
    }
}
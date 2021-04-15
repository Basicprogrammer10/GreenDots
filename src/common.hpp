#ifndef GREENDOTS_COMMON_HPP
#define GREENDOTS_COMMON_HPP
#include <vector>

namespace common {
    std::vector <std::string> tokenize(std::string const &str, const char delim);
    std::string cleanConfigString(const std::string& configString);
    bool exists(const std::string &name);
}
#endif

#ifndef GREENDOTS_COMMON_HPP
#define GREENDOTS_COMMON_HPP
namespace common {
    std::vector <std::string> tokenize(std::string const &str, const char delim);
    std::string cleanConfigString(const std::string& configString);
}
#endif

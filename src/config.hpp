#ifndef GREENDOTS_CONFIG_HPP
#define GREENDOTS_CONFIG_HPP
namespace config {
    bool checkForConfig(const std::string &name);
    bool createConfigFile(const std::string& name, const std::string& data);
}
#endif
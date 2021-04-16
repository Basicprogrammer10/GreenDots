#ifndef GREENDOTS_CONFIG_HPP
#define GREENDOTS_CONFIG_HPP

#include <vector>

namespace config {
    bool checkForConfig(const std::string &name);
    bool createConfigFile(const std::string& name, const std::vector<std::string>& data);
    std::string readConfig(const std::string& name);
    std::string getConfigValueFromKey(const std::string& configString, const std::string& key);
}
#endif
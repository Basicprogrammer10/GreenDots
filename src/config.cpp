#include <string>
#include <fstream>

namespace config {
    // Check if configFile has been created
    // Returns True / False
    bool checkForConfig(const std::string& name) {
        std::ifstream file;
        file.open(name);
        if(!file) return false;
        return true;
    }
}
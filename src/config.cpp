// Functions to work with Confnose Files

#include <string>
#include <fstream>

namespace config {
    // Check if configFile has been created
    bool checkForConfig(const std::string& name) {
        std::ifstream file;
        file.open(name);
        if(!file) return false;
        return true;
    }

    // Crate config file and supply it with starter data
    bool createConfigFile(const std::string& name, const std::string& data) {
        std::ofstream outfile (name);
        if (outfile.fail()) return false;

        outfile << data << std::endl;
        outfile.close();

        return true;
    }
}
// Functions to work with Confnose Files

#include <string>
#include <fstream>
#include <vector>

#include "common.hpp"

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

    // Read config file and return it as a string
    std::string readConfig(const std::string& name) {
        std::ifstream file(name, std::ios::binary | std::ios::ate);
        std::string fullFile;
        std::string line;
        if (file.fail()) return "";

        std::vector<char> buffer(file.tellg());
        file.seekg(0, std::ios::beg);
        while (std::getline(file,line)) fullFile += line += "\n";
        file.close();

        return fullFile;
    }

    // Parse the output of readConfig as a string and get value of the key
    std::string getConfigValueFromKey(const std::string& configString, std::string key) {
        std::vector<std::string> config = common::tokenize(configString, '=');
        std::string output;
        for (int i = 0; i < config.size(); i++) if (config[i] == key || config[i] == key + " ") output = config[i + 1];
        output = common::cleanConfigString(output);

        return output;
    }
}
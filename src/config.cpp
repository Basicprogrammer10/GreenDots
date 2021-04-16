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
    bool createConfigFile(const std::string& name, const std::vector<std::string>& data) {
        std::string outData;
        for (auto & i : data) outData += i + " = \"\"\n";

        return common::createFile(name, outData);
    }

    // Read config file and return it as a string
    std::string readConfig(const std::string& name) {
        std::ifstream file(name, std::ios::binary | std::ios::ate);
        std::string fullFile;
        std::string line;
        if (file.fail()) return "";

        std::vector<char> buffer(static_cast<const unsigned int>(file.tellg()));
        file.seekg(0, std::ios::beg);
        while (std::getline(file,line)) fullFile += line += "\n";
        file.close();

        return fullFile;
    }

    // Parse the output of readConfig as a string and get value of the key
    std::string getConfigValueFromKey(const std::string& configString, const std::string& key) {
        std::vector<std::string> lines = common::tokenize(configString, '\n');
        std::vector<std::string> config;
        std::string output;

        for (auto & line : lines) {
            std::vector<std::string> split = common::tokenize(line, '=');
            config.insert(config.end(), split.begin(), split.end());
        }

        for (int i = 0; i < config.size(); i++) if (config[i] == key || config[i] == key + " ") output = config[i + 1];
        output = common::cleanConfigString(output);

        return output;
    }
}
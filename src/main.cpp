#include <iostream>

#include "console.hpp"
#include "git.hpp"
#include "config.hpp"
#include "common.hpp"

#define version "0.0.3"
#define configFile "config.confnose"

int main() {
    std::string defaultConfig = "gitFolder = \"\"\n"
                                "dailyFile = \"\"";

    console::enableAnsiCodes();
    console::debugPrint("\x1B[1;32m[*] Welcome to Basicprogrammer10's GreenDots! ", 32, "");
    console::debugPrint(version, 35);

    console::debugPrint("[*] Checking for GIT", 34, " ");
    bool gitInstalled = git::checkForGit();
    if (!gitInstalled) console::errorPrint("[ FAILED ]", 31, -1);
    console::debugPrint("[ SUCCESS ]", 32);

    console::debugPrint("[*] Checking for ConfigFile", 34, " ");
    bool configFileCreated = config::checkForConfig(configFile);
    if (!configFileCreated) {
        console::debugPrint("[ NOT FOUND ]", 31);
        console::debugPrint("[*] Creating ConfigFile", 36, " ");
        if (!config::createConfigFile(configFile, defaultConfig)) console::errorPrint("[ FAILED ]", 31, -1);
        console::debugPrint("[ SUCCESS ]", 32);
        console::debugPrint("[*] Go edit the config file then re run this program", 35);
        return 0;
    }
    console::debugPrint("[ FOUND ]", 32);

    console::debugPrint("[*] Reading Config File", 34, " ");
    std::string config = config::readConfig(configFile);
    if (config.empty()) console::errorPrint("[ FAILED ]", 31, -1);
    console::debugPrint("[ SUCCESS ]", 32);

    console::debugPrint("[*] Validating Git Repo Location", 34, " ");
    std::string gitFolder = config::getConfigValueFromKey(config, "gitFolder");
    bool isValidRepo = git::checkIfGitRepo(gitFolder);
    if (!isValidRepo) console::errorPrint("[ FAILED ]", 31, -1);
    console::debugPrint("[ SUCCESS ]", 32);

    console::debugPrint("[*] Validating daily File", 34, " ");
    std::string dailyFile = gitFolder + "\\" + config::getConfigValueFromKey(config, "dailyFile");
    bool isFileCreated = common::exists(dailyFile);
    if (!isFileCreated) console::errorPrint("[ NOT FOUND ]", 31, -1);
    console::debugPrint("[ FOUND ]", 32);

    return 0;
}

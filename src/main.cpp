// Main function that is run first

#include <iostream>

#include "console.hpp"
#include "git.hpp"
#include "config.hpp"
#include "common.hpp"

#define version "0.0.6"
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
    if (!isFileCreated) {
        console::debugPrint("[ NOT FOUND ]", 31);
        console::debugPrint("[*] Creating daily File", 36, " ");
        bool createdDailyFile = config::createConfigFile(dailyFile, "");
        if (!createdDailyFile) console::errorPrint("[ FAILED ]", 31, -1);
    }
    console::debugPrint("[ SUCCESS ]", 32);

    std::vector<std::string> loadingAnimation = {"/", "-", "\\", "|"};
    std::string pastDate;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        for (auto & i : loadingAnimation) {
            console::debugPrint("\033[0G[" + i + "]", 36, "");
            common::sleep(500);
        }
        if (common::getDateAsString() != pastDate) {
            pastDate = common::getDateAsString();
            console::debugPrint(" " + pastDate + "\n\x1B[34m[*] Writing to daily File", 36, " ");
            bool appendToFile =  common::updateFile(dailyFile, common::getDateAsString());
            if (!appendToFile) console::errorPrint("[ FAILED ]", 31, 0);
            else console::debugPrint("[ SUCCESS ]", 32);

            console::debugPrint("[*] Committing to Git", 34, " ");
            bool commitRepoSuccess = git::commitRepo(gitFolder, "Testing");
            if (!commitRepoSuccess) console::errorPrint("[ FAILED ]", 31, 0);
            else console::debugPrint("[ SUCCESS ]", 32);

            console::debugPrint("[*] Pushing to Git", 34, " ");
            bool pushRepoSuccess = git::pushRepo(gitFolder);
            if (!pushRepoSuccess) console::errorPrint("[ FAILED ]", 31, 0);
            else console::debugPrint("[ SUCCESS ]", 32);
        }
        //break;
    }
#pragma clang diagnostic pop

    return 0;
}

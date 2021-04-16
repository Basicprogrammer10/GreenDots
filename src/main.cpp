#include <iostream>

#include "console.hpp"
#include "config.hpp"
#include "common.hpp"
#include "setup.hpp"

#define version "0.1.2"
#define configFile "config.confnose"

int main() {
    std::vector<std::string> defaultConfig = {"gitFolder", "dailyFile"};
    std::vector<std::string> loadingAnimation = {"/", "-", "\\", "|"};
    std::string pastDate;

    console::enableAnsiCodes();
    console::debugPrint("\x1B[1;32m[*] Welcome to Basicprogrammer10's GreenDots! ", 32, "");
    console::debugPrint(version, 35, "\n\n");

    setup::checkForGit();
    setup::checkForConfigFile(configFile, defaultConfig);
    std::string config = setup::readConfigFile(configFile);
    std::string gitFolder = setup::validateGitRepo(config);
    std::string dailyFile = setup::validateDailyFile(gitFolder, config);

    while (true) {
        for (auto &i : loadingAnimation) {
            console::debugPrint("\033[1A[" + i + "]", 36);
            common::sleep(500);
        }
        if (common::getDateAsString() == pastDate) continue;
        pastDate = common::getDateAsString();
        setup::writeDailyFile(pastDate, dailyFile);
        setup::commitToGit(gitFolder, pastDate);
        setup::pushToGit(gitFolder);
    }
}
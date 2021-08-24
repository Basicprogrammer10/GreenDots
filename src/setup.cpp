// Functions to setup stuff...
// Function names are good enough descriptions lol

#include <iostream>

#include "console.hpp"
#include "git.hpp"
#include "config.hpp"
#include "common.hpp"
#include "setup.hpp"

namespace setup {
    void checkForGit() {
        console::debugPrint("[*] Checking for GIT", 34, " ");
        bool gitInstalled = git::checkForGit();
        if (!gitInstalled) console::errorPrint("[ FAILED ]", 31, -1);
        console::debugPrint("[ SUCCESS ]", 32);
    }

    void checkForConfigFile(const std::string &configFile, const std::vector<std::string> &defaultConfig) {
        console::debugPrint("[*] Checking for ConfigFile", 34, " ");
        bool configFileCreated = config::checkForConfig(configFile);
        if (!configFileCreated) {
            console::debugPrint("[ NOT FOUND ]", 31);
            console::debugPrint("[*] Creating ConfigFile", 36, " ");
            if (!config::createConfigFile(configFile, defaultConfig))
                console::errorPrint("[ FAILED ]", 31, -1);
            console::debugPrint("[ SUCCESS ]", 32);
            console::debugPrint("[*] Go edit the config file then re run this program", 35);
            exit(0);
        }
        console::debugPrint("[ FOUND ]", 32);
    }

    std::string readConfigFile(const std::string &configFile) {
        console::debugPrint("[*] Reading Config File", 34, " ");
        std::string config = common::cleanUserInput(config::readConfig(configFile));
        if (config.empty()) console::errorPrint("[ FAILED ]", 31, -1);
        console::debugPrint("[ SUCCESS ]", 32);
        return config;
    }

    std::string validateGitRepo(const std::string &config) {
        console::debugPrint("[*] Validating Git Repo Location", 34, " ");
        std::string gitFolder = config::getConfigValueFromKey(config, "gitFolder");
        bool isValidRepo = git::checkIfGitRepo(gitFolder);
        if (!isValidRepo) console::errorPrint("[ FAILED ]", 31, -1);
        console::debugPrint("[ SUCCESS ]", 32);
        return gitFolder;
    }

    std::string validateDailyFile(const std::string &gitFolder, const std::string &config) {
        console::debugPrint("[*] Validating daily File", 34, " ");
        std::string dailyFile = gitFolder + "\\" + config::getConfigValueFromKey(config, "dailyFile");
        bool isFileCreated = common::exists(dailyFile);
        if (!isFileCreated) {
            console::debugPrint("[ NOT FOUND ]", 31);
            console::debugPrint("[*] Creating daily File", 36, " ");
            bool createdDailyFile = common::createFile(dailyFile, "");
            if (!createdDailyFile) console::errorPrint("[ FAILED ]", 31, -1);
        }
        console::debugPrint("[ SUCCESS ]", 32, "\n\n");
        return dailyFile;
    }

    void writeDailyFile(const std::string &pastDate, const std::string &dailyFile) {
        console::debugPrint("\033[1A\033[4C" + pastDate + "\n\x1B[34m[*] Writing to daily File", 36, " ");
        bool appendToFile = common::updateFile(dailyFile, common::getDateAsString());
        if (!appendToFile) console::errorPrint("[ FAILED ]", 31, 0);
        else console::debugPrint("[ SUCCESS ]", 32);
    }

    void commitToGit(const std::string &gitFolder, const std::string &pastDate) {
        console::debugPrint("[*] Committing to Git", 34, " ");
        bool commitRepoSuccess = git::commitRepo(gitFolder, pastDate);
        if (!commitRepoSuccess) console::errorPrint("[ FAILED ]", 31, 0);
        else console::debugPrint("[ SUCCESS ]", 32);
    }

    void pushToGit(const std::string &gitFolder) {
        console::debugPrint("[*] Pushing to Git", 34, " ");
        bool pushRepoSuccess = git::pushRepo(gitFolder);
        if (!pushRepoSuccess) console::errorPrint("[ FAILED ]", 31, 0);
        else console::debugPrint("[ SUCCESS ]", 32, "\n\n");
    }

    void setCommitSigning(bool value) {
        git::setCommitSigning(value);
    }

    void reEnableCommitSigning(const std::string& config) {
        std::string configValue = config::getConfigValueFromKey(config, "enableCommitSigning");
        if (configValue == "true") git::setCommitSigning(false);
    }
}
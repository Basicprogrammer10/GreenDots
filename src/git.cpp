// Code for interacting with GIT

#include <string>

#include "common.hpp"

namespace git {
    // Check if GIT is installed normally - returns true if so
    bool checkForGit() {
        std::string command = "git --version " + common::getOsNullPipe();
        if (!common::runSystemCommand(command)) return false;
        return true;
    }

    // Use the git command to check if a folder is a valid
    bool checkIfGitRepo(const std::string &folder) {
        if (folder.empty()) return false;
        if (!common::exists(folder)) return false;
        std::string nullPipe = common::getOsNullPipe();
        std::string command = "cd " + folder + " " + nullPipe + " && git status " + nullPipe;
        if (!common::runSystemCommand(command)) return false;
        return true;
    }

    // Commits all changes in git repo
    bool commitRepo(const std::string &folder, const std::string &message) {
        std::string nullPipe = common::getOsNullPipe();
        std::string command = "cd " + folder + " " + nullPipe +
                              " && git add -A && git commit -m \"" + message + "\" " + nullPipe;
        if (!common::runSystemCommand(command)) return false;
        return true;
    }

    // Commits all changes in git repo
    bool pushRepo(const std::string &folder) {
        std::string nullPipe = common::getOsNullPipe();
        std::string command = "cd " + folder + " " + nullPipe + " && git push " + nullPipe;
        if (!common::runSystemCommand(command)) return false;
        return true;
    }
}
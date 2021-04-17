// Code for interacting with GIT

#include <string>

#include "common.hpp"

namespace git {
    // Check if GIT is installed normally - returns true if so
    bool checkForGit() {
        std::string command = "git --version " + common::getOsNullPipe();
        return common::runSystemCommand(command);
    }

    // Use the git command to check if a folder is a valid
    bool checkIfGitRepo(const std::string &folder) {
        if (folder.empty()) return false;
        if (!common::exists(folder)) return false;
        std::string nullPipe = common::getOsNullPipe();
        std::string command = "cd " + folder + " " + nullPipe + " && git status " + nullPipe;
        return common::runSystemCommand(command);
    }

    // Commits all changes in git repo
    bool commitRepo(const std::string &folder, const std::string &message) {
        std::string nullPipe = common::getOsNullPipe();
        std::string command = "cd " + folder + " " + nullPipe +
                              " && git add -A && git commit -m \"" + message + "\" " + nullPipe;
        return common::runSystemCommand(command);
    }

    // Commits all changes in git repo
    bool pushRepo(const std::string &folder) {
        std::string nullPipe = common::getOsNullPipe();
        std::string command = "cd " + folder + " " + nullPipe + " && git push " + nullPipe;
        return common::runSystemCommand(command);
    }
}
// Code for interacting with GIT

#include <cstdlib>
#include <string>

#include "common.hpp"

namespace git {
    // Check if GIT is installed normally - returns true if so
    bool checkForGit() {
        std::string command = "git --version >nul 2>&1";
        int exitCode = system(command.c_str());
        if (exitCode != 0) return false;
        return true;
    }

    // Use the git command to check if a folder is a valid
    // Pipe to /dev/null for linux
    bool checkIfGitRepo(const std::string& folder) {
        if (folder.empty()) return false;
        if (!common::exists(folder)) return false;
        std::string command = "cd " + folder + " >nul 2>&1 && git status" + " >nul 2>&1";
        int result = system(command.c_str());
        if (result != 0) return false;
        return true;
    }
}
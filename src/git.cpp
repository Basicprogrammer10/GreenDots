// Code for interacting with GIT //

#include <cstdlib>
#include <string>

namespace git {
    // Check if GIT is installed normally - returns true if so
    bool checkForGit() {
        std::string command = "git --version >nul 2>&1";
        int exitCode = system(command.c_str());
        if (exitCode != 0) return false;
        return true;
    }
}
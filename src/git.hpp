#ifndef GREENDOTS_GIT_HPP
#define GREENDOTS_GIT_HPP
namespace git {
    bool checkForGit();
    bool checkIfGitRepo(const std::string& folder);
}
#endif

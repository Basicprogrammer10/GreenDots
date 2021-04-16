#ifndef GREENDOTS_GIT_HPP
#define GREENDOTS_GIT_HPP
namespace git {
    bool checkForGit();

    bool checkIfGitRepo(const std::string &folder);

    bool commitRepo(const std::string &folder, const std::string &message);

    bool pushRepo(const std::string &folder);
}
#endif

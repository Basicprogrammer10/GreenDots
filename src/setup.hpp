#ifndef GREENDOTS_SETUP_HPP
#define GREENDOTS_SETUP_HPP
namespace setup {
    void checkForGit();

    void checkForConfigFile(const std::string &configFile, const std::vector<std::string> &defaultConfig);

    std::string readConfigFile(const std::string &configFile);

    std::string validateGitRepo(const std::string &config);

    std::string validateDailyFile(const std::string &gitFolder, const std::string &config);

    void writeDailyFile(const std::string &pastDate, const std::string &dailyFile);

    void commitToGit(const std::string &gitFolder, const std::string &pastDate);

    void pushToGit(const std::string &gitFolder);
}
#endif

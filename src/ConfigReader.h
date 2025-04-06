#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <vector>

class ConfigReader {

    std::string _config_path;

public:
    ConfigReader() = default;
    ConfigReader(std::string cofig_path);
    std::string GetValue(std::string prefix);
    int GetWindowHeight();
    int GetWindowWidth();
    float GetXSpeed();
    float GetYSpeed();
    float GetLogoXScale();
    float GetLogoYScale();
    float GetXPosition();
    float GetYPosition();
    std::string GetFontPath();
    float GetFontSize();
    std::string GetTexturePath(std::string tName);
    std::string GetInitialTextureName();
    std::vector<std::string> GetAllLogoNames();
    std::vector<float> GetLogoColors();
    std::string GetPauseText();
};

#endif //CONFIG_READER_H
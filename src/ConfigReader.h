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
    float GetRotationSpeed();
    float GetPlayerSize();
    std::string GetFontPath();
    float GetFontSize();
    std::vector<float> GetPlayerColors();
    int GetFrameRate();
    int GetCoolDownCoeff();
    int GetKillPoints();
    int GetMeteorsCount();
    float GetMeteorsSpeedCoeff();
    float GetBulletXSize();
    float GetBulletYSize();
    float GetBulletSpeedCoeff();
};

#endif //CONFIG_READER_H
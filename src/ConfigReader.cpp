#include "ConfigReader.h"
#include <string>
#include <unistd.h>  // Для getcwd
#include <limits.h>  // Для PATH_MAX
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

using namespace std;

ConfigReader::ConfigReader(std::string config_path) {
    // char cwd[PATH_MAX];
    // if (getcwd(cwd, sizeof(cwd)) != nullptr) {
    //     cout << "Current working directory: " << cwd << endl;
    // }

    _config_path = config_path;
}

std::string ConfigReader::GetValue(std::string prefix) {
    ifstream config_reader(_config_path);

    if(!config_reader.is_open()) {
        cout << "Oops, config is not found\n";
        exit(-1);
    }

    string line;
    if(config_reader.is_open()) {
        while (getline(config_reader, line))
        {
            if (line.find(prefix) != string::npos) {
                size_t pos = line.find(prefix);
                config_reader.close();
                return line.substr(pos + 1 + prefix.size());
            }
        }
    }
    config_reader.close();
    return "";
}

int ConfigReader::GetWindowWidth() {
    string winSizeStr = GetValue("K_Window"), width;
    stringstream ss(winSizeStr);
    getline(ss, width, ' ');
    return stoi(width);
}

int ConfigReader::GetWindowHeight() {
    string winSizeStr = GetValue("K_Window"), width, height;
    stringstream ss(winSizeStr);
    getline(ss, width, ' ');
    getline(ss, height);
    return stoi(height);
}

float ConfigReader::GetRotationSpeed() {
    string speedStr = GetValue("K_RotationSpeed"), rSpeed;
    stringstream ss(speedStr);
    getline(ss, rSpeed, ' ');
    return stof(rSpeed);
}

float ConfigReader::GetPlayerSize() {
    string sizeStr = GetValue("K_PlayerSize"), size;
    stringstream ss(sizeStr);
    getline(ss, size, ' ');
    return stof(size);
}

string ConfigReader::GetFontPath() {
    string fontStr = GetValue("K_Font"), fPath;

    stringstream ss(fontStr);
    getline(ss, fPath, ' ');
    return fPath;
}

float ConfigReader::GetFontSize() {
    string fontStr = GetValue("K_Font"), fPath, fSize;

    stringstream ss(fontStr);
    getline(ss, fPath, ' ');
    getline(ss, fSize);

    return stof(fSize);
}

int ConfigReader::GetFrameRate() {
    string frameRateStr = GetValue("K_FrameRate"), frameRate;
    stringstream ss(frameRateStr);
    getline(ss, frameRate, ' ');
    return stoi(frameRate);
}

int ConfigReader::GetCoolDownCoeff() {
    string coolDownCoeffStr = GetValue("K_CoolDownCoeff"), coolDownCoeff;
    stringstream ss(coolDownCoeffStr);
    getline(ss, coolDownCoeff, ' ');
    return stoi(coolDownCoeff);
}

int ConfigReader::GetKillPoints() {
    string killPointsStr = GetValue("K_KillPoints"), killPoints;
    stringstream ss(killPointsStr);
    getline(ss, killPoints, ' ');
    return stoi(killPoints);
}

int ConfigReader::GetMeteorsCount() {
    string meteorsCountStr = GetValue("K_MeteorsCount"), meteorsCount;
    stringstream ss(meteorsCountStr);
    getline(ss, meteorsCount, ' ');
    return stoi(meteorsCount);
}

float ConfigReader::GetMeteorsSpeedCoeff() {
    string meteorsSpeedCoeffStr = GetValue("K_MeteorsSpeedCoeff"), meteorsSpeedCoeff;
    stringstream ss(meteorsSpeedCoeffStr);
    getline(ss, meteorsSpeedCoeff, ' ');
    return stof(meteorsSpeedCoeff);
}

std::vector<float> ConfigReader::GetPlayerColors() {
    std::vector<float> playerColors;
    std::istringstream stream(GetValue("K_PlayerColors"));
    std::string playerColor;

    while (stream >> playerColor) {
        playerColors.push_back(stof(playerColor));
    }

    return playerColors;
}

float ConfigReader::GetBulletXSize() {
    string bulletSizeStr = GetValue("K_BulletSize"), bulletXSize;
    stringstream ss(bulletSizeStr);
    getline(ss, bulletXSize, ' ');
    return stof(bulletXSize);
}

float ConfigReader::GetBulletYSize() {
    string bulletSizeStr = GetValue("K_BulletSize"), bulletXSize, bulletYSize;
    stringstream ss(bulletSizeStr);
    getline(ss, bulletXSize, ' ');
    getline(ss, bulletYSize);
    return stof(bulletYSize);
}

float ConfigReader::GetBulletSpeedCoeff() {
    string bulletSpeedCoeffStr = GetValue("K_BulletSpeedCoeff"), bulletSpeedCoeff;
    stringstream ss(bulletSpeedCoeffStr);
    getline(ss, bulletSpeedCoeff, ' ');
    return stof(bulletSpeedCoeff);
}
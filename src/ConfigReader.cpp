#include "ConfigReader.h"
#include <string>
#include <unistd.h>  // Для getcwd
#include <limits.h>  // Для PATH_MAX
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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
    string winSizeStr = GetValue("Window"), width;
    stringstream ss(winSizeStr);
    getline(ss, width, ' ');
    return stoi(width);
}

int ConfigReader::GetWindowHeight() {
    string winSizeStr = GetValue("Window"), width, height;
    stringstream ss(winSizeStr);
    getline(ss, width, ' ');
    getline(ss, height);
    return stoi(height);
}

float ConfigReader::GetXSpeed() {
    string speedStr = GetValue("Speed"), xSpeed;
    stringstream ss(speedStr);
    getline(ss, xSpeed, ' ');
    return stof(xSpeed);
}

float ConfigReader::GetYSpeed() {
    string speedStr = GetValue("Speed"), xSpeed, ySpeed;
    stringstream ss(speedStr);
    getline(ss, xSpeed, ' ');
    getline(ss, ySpeed);
    return stof(ySpeed);
}

float ConfigReader::GetLogoXScale() {
    string scaleStr = GetValue("Scale"), xScale;
    stringstream ss(scaleStr);
    getline(ss, xScale, ' ');
    return stof(xScale);
}

float ConfigReader::GetLogoYScale() {
    string scaleStr = GetValue("Scale"), xScale, yScale;
    stringstream ss(scaleStr);
    getline(ss, xScale, ' ');
    getline(ss, yScale);
    return stof(yScale);
}

float ConfigReader::GetXPosition() {
    string positionStr = GetValue("Position"), xPosition;
    stringstream ss(positionStr);
    getline(ss, xPosition, ' ');
    return stof(xPosition);
}

float ConfigReader::GetYPosition() {
    string positionStr = GetValue("Position"), xPosition, yPosition;
    stringstream ss(positionStr);
    getline(ss, xPosition, ' ');
    getline(ss, yPosition);
    return stof(yPosition);
}

string ConfigReader::GetFontPath() {
    string fontStr = GetValue("Font"), fPath;

    stringstream ss(fontStr);
    getline(ss, fPath, ' ');
    return fPath;
}

float ConfigReader::GetFontSize() {
    string fontStr = GetValue("Font"), fPath, fSize;

    stringstream ss(fontStr);
    getline(ss, fPath, ' ');
    getline(ss, fSize);

    return stof(fSize);
}

std::string ConfigReader::GetTexturePath(std::string tName) {
    string textureStr = GetValue(tName), tPath;

    stringstream ss(textureStr);
    getline(ss, tPath, ' ');
    return tPath;
}

std::string ConfigReader::GetInitialTextureName() {
    string initialTextureStr = GetValue("InitialTexture"), tName;

    stringstream ss(initialTextureStr);
    getline(ss, tName, ' ');
    return tName;
}

std::vector<std::string> ConfigReader::GetAllLogoNames() {
    std::vector<std::string> logoNames;
    std::istringstream stream(GetValue("LogoNames"));
    std::string logoName;

    while (stream >> logoName) {
        logoNames.push_back(logoName);
    }

    return logoNames;
}

std::vector<float> ConfigReader::GetLogoColors() {
    std::vector<float> logoColors;
    std::istringstream stream(GetValue("LogoColors"));
    std::string logoColor;

    while (stream >> logoColor) {
        logoColors.push_back(stof(logoColor));
    }

    return logoColors;
}

std::string ConfigReader::GetPauseText() {
    string pauseTextStr = GetValue("PauseText"), pText;

    stringstream ss(pauseTextStr);
    getline(ss, pText, ' ');
    return pText;
}
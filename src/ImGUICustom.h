#ifndef IMGUICUSTOM_H
#define IMGUICUSTOM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "ConfigReader.h"

class ImGUICustom {
    std::vector<std::string> _items;
    int _selected_item;
    int _previous_item;
    ConfigReader& _configReader;
    char _inputBuffer[256];
    float _speedValue;
    float _scaleValue;

public:
    ImGUICustom() = default;
    ImGUICustom(sf::RenderWindow& window, ConfigReader& configReader);

    void ProcessEvent(const sf::Window &window, const sf::Event &event);
    void UpdateGui();
    void Render(sf::RenderWindow &window);
    void Update(sf::RenderWindow &window, sf::Time dt);
    void SetInputBuffer(std::string text);
    void ShutDown();
};

#endif //IMGUICUSTOM_H
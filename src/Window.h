#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "ImGUICustom.h"
#include "DrawableEntity.h"

#include "ConfigReader.h"

class Window {
    sf::RenderWindow _window;

    sf::Clock _deltaClock;

    bool _isRun = true, _isPause = false;
    ConfigReader& _configReader;

    std::shared_ptr<ImGUICustom> _imGui;
    std::vector<std::shared_ptr<DrawableEntity>> _drawableEntities;

    void Initialize();

    void UpdateUserInput();
    void UpdateLogic();
    void UpdateGui();
    void Render();

public:
    Window(const unsigned int wWidth, const unsigned int wHeight, ConfigReader& configReader);
    
    void Run();
};

#endif //WINDOW_H

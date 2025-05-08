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

#include "World.hpp"
#include "Text.h"
#include "SystemsManager.hpp"

#include "systems/InitSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/RotationSystem.hpp"
#include "systems/ShootingSystem.hpp"
#include "systems/DetectCollisionSystem.hpp"
#include "systems/ProcessCollisionSystem.hpp"
#include "systems/PoopCollectorSystem.hpp"
#include "systems/MeteorSpawnSystem.hpp"
#include "systems/ScoreSystem.hpp"

class Window {
    sf::RenderWindow _window;

    sf::Clock _deltaClock;

    bool _isRun = true, _isPause = false;
    ConfigReader& _configReader;

    std::shared_ptr<ImGUICustom> _imGui;
    std::vector<std::shared_ptr<DrawableEntity>> _drawableEntities;

    World _world;
    SystemsManager _systems;


    void Initialize();

    void UpdateUserInput();
    void UpdateLogic();
    void UpdateGui();
    void Render();

public:
    Window(const unsigned int wWidth, const unsigned int wHeight, ConfigReader& configReader);
    std::string scoreText;
    sf::Font font;
    std::shared_ptr<Text> text;

    void Run();
};

#endif //WINDOW_H

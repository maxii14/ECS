#include "Window.h"
#include "ConfigReader.cpp"
#include "World.hpp"
#include "SystemsManager.hpp"
#include "systems/InitSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/RotationSystem.hpp"
#include <fstream>
#include <string>


using namespace std;

int main()
{
    cout << "AAAAAAAAAAAAAAAAA";
    setlocale(LC_ALL, "");
    cout << "AAAAAAAAAAAAAAAAA";
    ConfigReader configReader("../config.txt");
    const int wWidth = configReader.GetWindowWidth();
    const int wHeight = configReader.GetWindowHeight();

    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "LR2");
    window.setFramerateLimit(60);
    // Window window(wWidth, wHeight, configReader);
    // window.Run();
    World world(window);

    SystemsManager systems(world);
    systems.AddInitializer(std::make_shared<InitSystem>(world));
    systems.AddSystem(std::make_shared<MovementSystem>(world));
    systems.AddSystem(std::make_shared<RenderSystem>(world));
    systems.AddSystem(std::make_shared<RotationSystem>(world));

    while (window.isOpen()) {
        systems.Update(window);
    }

    return 0;
}
#include "Window.h"
#include "ConfigReader.cpp"
#include "World.hpp"
#include "SystemsManager.hpp"
#include "systems/InitSystem.hpp"
#include "systems/MovementSystem.hpp"
#include <fstream>
#include <string>


using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    ConfigReader configReader("../config.txt");
    const int wWidth = configReader.GetWindowWidth();
    const int wHeight = configReader.GetWindowHeight();

    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "LR2");
    window.setFramerateLimit(60);
    World world;
    
    SystemsManager systems(world);
    // systems.AddInitializer(std::make_shared<InitSystem>(world));
    // systems.AddSystem(std::make_shared<MovementSystem>(world));
    // while (window.isOpen()) {
    //     systems.Update();
    // }

    // Window window(wWidth, wHeight, configReader);
    // window.Run();

    return 0;
}
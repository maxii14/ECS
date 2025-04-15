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
    cout << "AAAAAAAAAAAAAAAAA";
    setlocale(LC_ALL, "");
    cout << "AAAAAAAAAAAAAAAAA";
    ConfigReader configReader("../config.txt");
    const int wWidth = configReader.GetWindowWidth();
    const int wHeight = configReader.GetWindowHeight();

    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "LR2");
    window.setFramerateLimit(60);
    World world;

    SystemsManager systems(world);
    systems.AddInitializer(std::make_shared<InitSystem>(world));
    cout << systems._systems.size();
    systems.AddSystem(std::make_shared<MovementSystem>(world));
    cout << systems._systems.size();

    while (window.isOpen()) {
        systems.Update();
    }

    return 0;
}
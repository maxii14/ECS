#include "Window.h"

Window::Window(const unsigned int wWidth, const unsigned int wHeight, ConfigReader& configReader) :
    _configReader(configReader), _window(sf::VideoMode({wWidth, wHeight}), "LR2_Liubushkin-Borovik"),
    _world(_window), _systems(_world)
{
    auto desktop = sf::VideoMode::getDesktopMode();
    _window.setPosition({ (int) (desktop.size.x / 2 - wWidth / 2), (int) (desktop.size.y / 2 - wHeight / 2) });
    _window.setFramerateLimit(60);

    Initialize();
}

void Window::Initialize()
{
    _systems.AddInitializer(std::make_shared<InitSystem>(_world));
    _systems.AddSystem(std::make_shared<MovementSystem>(_world));
    _systems.AddSystem(std::make_shared<RenderSystem>(_world));
    _systems.AddSystem(std::make_shared<RotationSystem>(_world));
    _systems.AddSystem(std::make_shared<ShootingSystem>(_world));
    _systems.AddSystem(std::make_shared<MeteorSpawnSystem>(_world));
    _systems.AddSystem(std::make_shared<DetectCollisionSystem>(_world));
    _systems.AddSystem(std::make_shared<ProcessCollisionSystem>(_world));
    _systems.AddSystem(std::make_shared<PoopCollectorSystem>(_world));
  
}

void Window::Run()
{
    while (_isRun)
    {
        sf::Time delta = _deltaClock.restart();

        UpdateUserInput();
        Render();
    }

    _window.close();
}

void Window::UpdateUserInput()
{
    while (const std::optional event = _window.pollEvent())
    {
        // _imGui->ProcessEvent(_window, *event);

        if (event->is<sf::Event::Closed>())
        {
            _isRun = false;
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            std::wcout << L"Key pressed with code = " << sf::Keyboard::getDescription(keyPressed->scancode).toWideString() << "\n";
            
            _systems.NotifyKeyboardEvent(keyPressed->code);
        }
    }
}

void Window::UpdateLogic() {

}

void Window::UpdateGui()
{

}

void Window::Render()
{
    _window.clear();

    _systems.Update(_window);

    _window.display();
}

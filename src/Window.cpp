#include "Window.h"

Window::Window(const unsigned int wWidth, const unsigned int wHeight, ConfigReader& configReader) :
    _configReader(configReader)
{
    _window.create(sf::VideoMode({wWidth, wHeight}), "LR2_Liubushkin-Borovik");

    auto desktop = sf::VideoMode::getDesktopMode();
    _window.setPosition({ (int) (desktop.size.x / 2 - wWidth / 2), (int) (desktop.size.y / 2 - wHeight / 2) });
    _window.setFramerateLimit(60);

    Initialize();
}

void Window::Initialize()
{
    _imGui = std::make_shared<ImGUICustom>(_window, _configReader);
    _imGui->SetInputBuffer(_configReader.GetPauseText());

    // _drawableEntities.push_back(_logo);
    // _drawableEntities.push_back(_text);
}

void Window::Run()
{
    while (_isRun)
    {
        sf::Time delta = _deltaClock.restart();
        _imGui->Update(_window, delta);
        UpdateUserInput();
        UpdateGui();
        Render();
    }

    _window.close();
    _imGui->ShutDown();
}

void Window::UpdateUserInput()
{
    while (const std::optional event = _window.pollEvent())
    {
        _imGui->ProcessEvent(_window, *event);

        if (event->is<sf::Event::Closed>())
        {
            _isRun = false;
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            std::wcout << L"Key pressed with code = " << sf::Keyboard::getDescription(keyPressed->scancode).toWideString() << "\n";

            // if (keyPressed->code == sf::Keyboard::Key::Space)
            // {
            //     _isPause = !_isPause;
            // }
        }
    }
}

void Window::UpdateLogic()
{
}

void Window::UpdateGui()
{
   // _imGui->UpdateGui(_logo, _text);
}

void Window::Render()
{
    _window.clear();

    if (!_isPause) {
        UpdateLogic();
    }

    for (std::shared_ptr<DrawableEntity> drawableEntity : _drawableEntities) {
        if (drawableEntity->GetShouldDraw()) {
            _window.draw(*drawableEntity);
        }
    }

    _imGui->Render(_window);
    _window.display();
}

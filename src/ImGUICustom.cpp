#include "ImGUICustom.h"
#include <iostream>

ImGUICustom::ImGUICustom(sf::RenderWindow& window, ConfigReader& configReader) : 
    _configReader(configReader) 
{
    ImGui::SFML::Init(window);
    ImGui::GetStyle().ScaleAllSizes(1.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    _selected_item = 0;
    _previous_item = 0;
    _speedValue = configReader.GetXSpeed();
    _scaleValue = configReader.GetLogoXScale();
}

void ImGUICustom::ProcessEvent(const sf::Window &window, const sf::Event &event) {
    ImGui::SFML::ProcessEvent(window, event);
}

void ImGUICustom::UpdateGui() {
    ImGui::Begin("LR1");
    ImGui::Text("Press Space to pause");

    ImGui::End();
}

void ImGUICustom::Render(sf::RenderWindow &window) {
    ImGui::SFML::Render(window);
}

void ImGUICustom::Update(sf::RenderWindow &window, sf::Time dt) {
    ImGui::SFML::Update(window, dt);
}

void ImGUICustom::ShutDown() {
    ImGui::SFML::Shutdown();
}

void ImGUICustom::SetInputBuffer(std::string text) {
    strcpy (_inputBuffer, text.c_str());
}
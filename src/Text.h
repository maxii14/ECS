#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <string>


class Text {
    sf::Font _font;
    sf::Text _text = sf::Text(_font);
    float _fontSize;
    bool _shouldDraw;
    sf::Vector2f _position;

    void Transfer(const Text& other);
public:
    Text(
        const std::filesystem::path& fontPath,
        const sf::String text, const int fontSize
    );

    const int GetCharacterSize() const;
    void SetPosition(const sf::Vector2f position);
    void SetShouldDraw(bool shouldDraw);
    void SetText(std::string text);
    void Draw(sf::RenderTarget& target);
    int GetScore();
};

#endif //TEXT_H
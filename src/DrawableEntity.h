#ifndef DRAWABLE_ENTITY_H
#define DRAWABLE_ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>

class DrawableEntity : public sf::Drawable 
{
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual bool& GetShouldDraw() = 0;
    virtual ~DrawableEntity() = default;
};

#endif // DRAWABLE_ENTITY_H
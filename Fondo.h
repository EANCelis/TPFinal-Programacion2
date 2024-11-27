#pragma once
#include <SFML/Graphics.hpp>

class Fondo {
public:
    Fondo();
    void draw(sf::RenderTarget& target) const;

private:
    sf::Sprite _fondo;
    sf::Texture _texturaFondo;
};

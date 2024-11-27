#pragma once
#include <SFML/Graphics.hpp>
#include "Enemigo.h"


class EnemigoKamikaze : public Enemigo {
public:
    EnemigoKamikaze();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::FloatRect getBounds() const override;
    void setPosition(float x, float y);
    void reiniciarReloj();

private:
    sf::Sprite _enemy3;
    sf::Texture _textureEnemy3;


    float _velocidad;

    sf::Clock _reloj;
};

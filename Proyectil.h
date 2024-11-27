#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"


class Proyectil: public Colisionable{
public:
    Proyectil(float x, float y, int vel, const sf::Texture& texture, float escala);
    void update();
    sf::Vector2f getPosition() const; // Obtiene la posición actual del proyectil
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect getBounds() const; // Obtiene los límites del proyectil para colisiones

private:
    sf::Sprite _proyectil;
    float _velocidad;
};

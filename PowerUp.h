#pragma once
#include "SFML/Graphics.hpp"
#include "Colisionable.h"
class PowerUp: public Colisionable {
public:
    PowerUp(); // Constructor por defecto
    PowerUp(const sf::Texture& textura);
    void update();
    void draw(sf::RenderTarget& target) const;
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;
    bool estaActivo() const;
    void desactivar();
    void activar();
    void setTipo(int tipo);
    int getTipo() const;
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _velocidad; // Velocidad de caída
    bool _activo; // Estado del power up
    int _tipo;
};

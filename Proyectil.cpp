#include "Proyectil.h"


Proyectil::Proyectil(float x, float y, int vel, const sf::Texture& texture, float escala) {
    _proyectil.setTexture(texture);
    _proyectil.setPosition(x, y);
    _proyectil.setScale(escala, escala);
    _velocidad = vel;
}


void Proyectil::update() {
    _proyectil.move(0, _velocidad);
}


sf::Vector2f Proyectil::getPosition() const {
    return _proyectil.getPosition();
}


void Proyectil::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_proyectil, states);
}

sf::FloatRect Proyectil::getBounds() const {
    return _proyectil.getGlobalBounds();
}

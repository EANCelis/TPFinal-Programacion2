#include "Fondo.h"


Fondo::Fondo() {
    if (!_texturaFondo.loadFromFile("Recursos/bg.jpg")) {
        // exit (-1);
    }
    _fondo.setTexture(_texturaFondo);
    _fondo.setPosition(0, 0);
}


void Fondo::draw(sf::RenderTarget& target) const {
    target.draw(_fondo);
}

#include "PowerUp.h"
#include <iostream>
PowerUp::PowerUp() {
    _velocidad = 15.0f;
    _activo = false;
}
PowerUp::PowerUp(const sf::Texture& textura)  {
    _sprite.setTexture(textura);
    _sprite.setScale(0.25f, 0.25f);
    _sprite.setPosition(rand() % 800 + 100, 0);
    _velocidad = 5.0f;
    _activo = true;
}

void PowerUp::update() {
    if (_activo) {

        _sprite.move(0, _velocidad);

        // Verifica si ha salido de la pantalla
        if (_sprite.getPosition().y > 800) {
            desactivar();
        }
    }
}

void PowerUp::draw(sf::RenderTarget& target) const {
    target.draw(_sprite);
}

sf::FloatRect PowerUp::getBounds() const {
    return _sprite.getGlobalBounds();
}

bool PowerUp::estaActivo() const {
    return _activo;
}

void PowerUp::desactivar() {
    _activo = false;
}
void PowerUp::setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}
void PowerUp::activar(){
    _activo = true;
}
void PowerUp::setTipo(int tipo){
    _tipo = tipo;
}
int PowerUp::getTipo() const{
    return _tipo;
}

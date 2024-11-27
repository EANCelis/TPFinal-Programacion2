#include "EnemigoKamikaze.h"
#include <cstdlib>


EnemigoKamikaze::EnemigoKamikaze()
{
    if (!_textureEnemy3.loadFromFile("Recursos/3B.png")) {
       // exit (-1);
    }
    _enemy3.setTexture(_textureEnemy3);
    _enemy3.setScale(0.2f, 0.2f); // Ajustar escala si es necesario
    _estaVivo = false;
    _velocidad = 5.0f;
}

void EnemigoKamikaze::update() {
    // Si está vivo, mover hacia abajo
    if (_estaVivo) {
        _enemy3.move(0, _velocidad);

        // Comprueba si ha salido de la pantalla
        if (_enemy3.getPosition().y > 800) {
            _estaVivo = false;
        }
    }

    // Controla el tiempo de aparición
    if (_reloj.getElapsedTime().asSeconds() > 5.0f && !_estaVivo) {
        _enemy3.setPosition(rand() % 800 + 100, 0); // Aparece en la parte superior
        _estaVivo = true;
        _reloj.restart();
    }
}

void EnemigoKamikaze::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_estaVivo) {
        target.draw(_enemy3, states);
    }
}

sf::FloatRect EnemigoKamikaze::getBounds() const {
    return _enemy3.getGlobalBounds();
}

void EnemigoKamikaze::setPosition(float x, float y) {
    _enemy3.setPosition(x, y);
}

void EnemigoKamikaze::reiniciarReloj(){
    _reloj.restart();
}

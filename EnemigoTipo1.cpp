#include "EnemigoTipo1.h"
#include <iostream>
EnemigoTipo1::EnemigoTipo1()
{
    cargarTexturas();


    _direccion = sf::Vector2f(1.0f, 0.0f); // Inicialmente hacia la derecha
    _velocidad = 2.0f;
    _estaVivo = true;
}

void EnemigoTipo1::update() {
    // Cambiar dirección cada cierto tiempo
    if (_relojMovimiento.getElapsedTime().asSeconds() > 1.0f) {
        mover();
        _relojMovimiento.restart();
    }

    _enemy2.move(_direccion * _velocidad);


    verificarBordes();

    if (_relojDisparo.getElapsedTime().asSeconds() > 0.8f && puedeDisparar)
    {
        disparar(_texturaProyectil);
        _relojDisparo.restart(); // Reinicia el reloj de disparo
        puedeDisparar = false; // Después de disparar, se desactiva el disparo para este enemigo
    }

    for (auto& proyectil : _proyectiles)
    {
        proyectil.update();
    }
}

void EnemigoTipo1::mover() {
    // Cambiar aleatoriamente la dirección
    int randDireccion = rand() % 4; // 0: derecha, 1: izquierda, 2: arriba, 3: abajo
    switch (randDireccion) {
        case 0: _direccion = sf::Vector2f(1.0f, 0.0f); break; // Derecha
        case 1: _direccion = sf::Vector2f(-1.0f, 0.0f); break; // Izquierda
        case 2: _direccion = sf::Vector2f(0.0f, -1.0f); break; // Arriba
        case 3: _direccion = sf::Vector2f(0.0f, 1.0f); break; // Abajo

        /*case 0: _direccion.x =  1.0f; break;
        case 1: _direccion.x = -1.0f; break;
        case 2: _direccion.y = -1.0f; break;
        case 3: _direccion.y =  1.0f; break; */
    }
}
void EnemigoTipo1::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_estaVivo){
        target.draw(_enemy2, states);
    }
    for (const auto& proyectil : _proyectiles)
    {
        proyectil.draw(target, states);
    }
}
void EnemigoTipo1::setPosition(float x, float y){
    _enemy2.setPosition(x, y);
}
sf::FloatRect EnemigoTipo1::getBounds() const {
    return _enemy2.getGlobalBounds();
}
void EnemigoTipo1::disparar(const sf::Texture& _texturaProyectil)
{
    _proyectil.setTexture(_texturaProyectil);
    _proyectil.setScale(0.5f, 0.5f);

    Proyectil proyectil(_enemy2.getPosition().x + (_enemy2.getGlobalBounds().width / 2) - 15,
                        _enemy2.getPosition().y + _enemy2.getGlobalBounds().height,
                        10, _texturaProyectil, 0.4f); // Crear el proyectil del enemigo
    _proyectiles.push_back(proyectil); // Agregarlo al Vector de proyectiles
}
/*std::vector<Proyectil>& EnemigoTipo1::getProyectiles()
{
    return _proyectiles; // Devuelve el Vector de proyectiles
}*/
void EnemigoTipo1::cargarTexturas(){
    if (!_texturaProyectil.loadFromFile("Recursos/laserBulletEnemy.png"))
    {

    }
    if (!_textureEnemy2.loadFromFile("Recursos/6.png")) {

    }
    _enemy2.setTexture(_textureEnemy2);
    _enemy2.setScale(0.3f, 0.3f);

    _proyectil.setTexture(_texturaProyectil);
    _proyectil.setScale(0.3f, 0.3f);
}
void EnemigoTipo1::verificarBordes(){
    if (_enemy2.getPosition().x < 0) {
        _enemy2.setPosition(0, _enemy2.getPosition().y); // Limita a la izquierda
        _direccion.x = 1.0f; // Cambia la dirección hacia la derecha
    }
    if (_enemy2.getPosition().x + _enemy2.getGlobalBounds().width > 1000) {
        _enemy2.setPosition(1000 - _enemy2.getGlobalBounds().width, _enemy2.getPosition().y); // Limita a la derecha
        _direccion.x = -1.0f; // Cambia la dirección hacia la izquierda
    }

    if (_enemy2.getPosition().y < 0) {
        _enemy2.setPosition(_enemy2.getPosition().x, 0); // Limita arriba
        _direccion.y = 1.0f; // Cambia la dirección hacia abajo
    }
    if (_enemy2.getPosition().y + _enemy2.getGlobalBounds().height > 400) {
        _enemy2.setPosition(_enemy2.getPosition().x, 400 - _enemy2.getGlobalBounds().height); // Limita abajo
        _direccion.y = -1.0f; // Cambia la dirección hacia arriba
    }
}

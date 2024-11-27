#include "Boss.h"
#include "Enemigo.h"
#include <iostream>
Boss::Boss()
{
    cargarTexturas();

    _boss.setTexture(_textureBoss);
    _boss.setScale(1.0f, 1.0f);

    _proyectil.setTexture(_texturaProyectil);
    _proyectil.setScale(0.3f, 0.3f);


    _direccion = sf::Vector2f(1.0f, 0.0f); // Inicialmente hacia la derecha
    _velocidad = 2.0f;
    _estaVivo = false;
    _vidas = 10;
}

void Boss::update() {
    // Cambiar dirección cada cierto tiempo
    if (_relojMovimiento.getElapsedTime().asSeconds() > 1.0f) {
        mover();
        _relojMovimiento.restart();
    }

    _boss.move(_direccion * _velocidad);

    verificarBordes();

    if (_relojDisparo.getElapsedTime().asSeconds() > 1.0f && puedeDisparar)
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

void Boss::mover() {
    int randDireccion = rand() % 2; // 0: derecha, 1: izquierda
    switch (randDireccion) {
        case 0: _direccion = sf::Vector2f(2.0f, 0.0f); break; // Derecha
        case 1: _direccion = sf::Vector2f(-2.0f, 0.0f); break; // Izquierda
    }
}
void Boss::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_estaVivo){
        target.draw(_boss, states); // Dibuja el enemigo
    }
    for (const auto& proyectil : _proyectiles)
    {
        proyectil.draw(target, states);
    }
}
void Boss::setPosition(float x, float y){
    _boss.setPosition(x, y);
}
sf::FloatRect Boss::getBounds() const {
    return _boss.getGlobalBounds();
}
void Boss::disparar(const sf::Texture& _texturaProyectil)
{
    //_proyectil.setTexture(_texturaProyectil);
    _proyectil.setScale(0.5f, 0.5f);

    Proyectil proyectil(_boss.getPosition().x + (_boss.getGlobalBounds().width / 2) - 15,
                        _boss.getPosition().y + _boss.getGlobalBounds().height,
                        10, _texturaProyectil, 0.8f); // Crear el proyectil del enemigo
    _proyectiles.push_back(proyectil); // Agregarlo al Vector de proyectiles
}

void Boss::cargarTexturas(){
    if (!_texturaProyectil.loadFromFile("Recursos/laserBulletEnemy.png"))
    {

    }
    if (!_textureBoss.loadFromFile("Recursos/Boss.png")) {

    }
}
void Boss::verificarBordes(){
    if (_boss.getPosition().x < 0) {
        _boss.setPosition(0, _boss.getPosition().y); // Limita a la izquierda
        _direccion.x = 2.0f; // Cambia la dirección hacia la derecha
    }
    if (_boss.getPosition().x + _boss.getGlobalBounds().width > 1000) {
        _boss.setPosition(1000 - _boss.getGlobalBounds().width, _boss.getPosition().y); // Limita a la derecha
        _direccion.x = -2.0f; // Cambia la dirección hacia la izquierda
    }
}
void Boss::setEstaVivo(bool estado) {
    _estaVivo = estado;
}

bool Boss::getEstaVivo() const {
    return _estaVivo;
}
void Boss::restarVidas(){
    if(_vidas > 0){
        _vidas--;
    }
}
int Boss::getVidas() const{
    return _vidas;
}

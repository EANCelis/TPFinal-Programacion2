#include "Enemigo.h"
#include <cstdlib>
#include <ctime>

Enemigo::Enemigo()
{

    if (!_textureEnemy.loadFromFile("Recursos/Alien-Enemy.png"))
    {

    }
    _enemy.setTexture(_textureEnemy);
    _enemy.setScale(0.5f, 0.3f);
    //resetPosition(); // Reinicia la posición del enemigo

    if (!_texturaProyectil.loadFromFile("Recursos/laserBulletEnemy.png"))
    {

    }
    _proyectil.setTexture(_texturaProyectil);
    _proyectil.setScale(0.3f, 0.3f);

    _distanciaDerecha = 150.0f;
    _distanciaIzquierda = 10.0f;
    _moverDerecha = true;
}

/*void Enemigo::resetPosition()
{
    _enemy.setPosition(-100, -100); // Posiciona al enemigo fuera de la pantalla
}
*/
void Enemigo::setPosition(float x, float y)
{
    _enemy.setPosition(x, y);
    _posicionInicialX = x; // Guarda la posición inicial del enemigo
}
void Enemigo::setEstaVivo(bool estado)
{
    _estaVivo = estado;
}
bool Enemigo::getEstaVivo() const
{
    return _estaVivo;
}
void Enemigo::update()
{
    float velocidad = 2.0f;
    float distanciaRecorrida = _moverDerecha ? velocidad : -velocidad; // Determina la dirección del movimiento

    _enemy.move(distanciaRecorrida, 0); // Mueve al enemigo en el eje X

    mover();
    // Verifica si es momento de disparar
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

void Enemigo::disparar(const sf::Texture& _texturaProyectil)
{
    _proyectil.setTexture(_texturaProyectil);
    _proyectil.setScale(0.5f, 0.5f);

    Proyectil proyectil(_enemy.getPosition().x + (_enemy.getGlobalBounds().width / 2) - 15,
                        _enemy.getPosition().y + _enemy.getGlobalBounds().height,
                        10, _texturaProyectil, 0.4f); // Crear el proyectil del enemigo
    _proyectiles.push_back(proyectil); // Agregarlo al Vector de proyectiles

}

void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(_estaVivo){
        target.draw(_enemy, states);
    }
    for (const auto& proyectil : _proyectiles)
    {
        proyectil.draw(target, states);
    }
}

sf::FloatRect Enemigo::getBounds() const
{
    return _enemy.getGlobalBounds();
}

std::vector<Proyectil>& Enemigo::getProyectiles()
{
    return _proyectiles; // Devuelve el Vector de proyectiles
}

void Enemigo::mover()
{
    // Verifica si el enemigo ha alcanzado el límite de movimiento a la derecha
    if (_moverDerecha && (_enemy.getPosition().x - _posicionInicialX >= _distanciaDerecha) && _estaVivo == 1)
    {
        _moverDerecha = false; // Cambia la dirección a la izquierda
    }
    // Verifica si el enemigo ha alcanzado el límite de movimiento a la izquierda
    else if (!_moverDerecha && (_enemy.getPosition().x - _posicionInicialX <= -_distanciaIzquierda) && _estaVivo == 1)
    {
        _moverDerecha = true; // Cambia la dirección a la derecha
    }
}
void Enemigo::limpiarProyectiles() {
    _proyectiles.clear(); // Limpia el vector de proyectiles
}

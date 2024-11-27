#include "Jugador.h"
#include "Proyectil.h"
#include <algorithm>
#include <iostream>
Jugador::Jugador()
{

    if (!_textureNave.loadFromFile("Recursos/Alien-Scout.png"))
    {
        // exit (-1);
    }
    _nave.setTexture(_textureNave);
    _nave.setScale(0.6f, 0.6f);
    _nave.setPosition(500, 700);
    _velocidad = 6; // Velocidad de movimiento del jugador


    if (!_texturaProyectil.loadFromFile("Recursos/laserBullet.png"))
    {
        // exit (-1);
    }
    _ataquePowerUp = false;
    _estaInvulnerable = false;
}

sf::Vector2f Jugador::getPosicion() const
{
    return _nave.getPosition();
}

std::vector<Proyectil>& Jugador::getProyectiles()
{
    return _proyectiles; // Retornar el vector de proyectiles del jugador
}

void Jugador::update()
{


    if (_ataquePowerUp){
        ataquePowerUp();
    }
    else{
        ataqueNormal();
    }



// Movimiento del jugador hacia la izquierda
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    _nave.move(-_velocidad, 0);
}
// Movimiento del jugador hacia la derecha
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    _nave.move(_velocidad, 0);
}


if (_nave.getPosition().x < 0)
{
    _nave.setPosition(0, _nave.getPosition().y);
}

if (_nave.getPosition().x + _nave.getGlobalBounds().width > 1000)
{
    _nave.setPosition((1000 - _nave.getGlobalBounds().width), _nave.getPosition().y);
}




for (auto& proyectil : _proyectiles)
{
    proyectil.update();
}

// Eliminar proyectiles que han salido de la pantalla
for (int i = 0; i < _proyectiles.size(); )
{

    if (_proyectiles[i].getPosition().y < 0)
    {
        _proyectiles.erase(_proyectiles.begin() + i);
        //std::cout << "Elimine un proyectil" << std::endl;
    }
    else
    {
        i++;
    }
}

}
void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_nave, states);
    for (const auto& proyectil : _proyectiles)
    {
        proyectil.draw(target, states);
    }
}

sf::FloatRect Jugador::getBounds() const
{
    return _nave.getGlobalBounds();
}
void Jugador::ataquePowerUp()
{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _reloj.getElapsedTime().asSeconds() > 0.5f)
        {
            Proyectil proyectil1(
                _nave.getPosition().x + 50,
                _nave.getPosition().y - 10,
                -10, // Direccion
                _texturaProyectil, // textura del proyectil ya cargada
                0.25f  // Escala
            );

            Proyectil proyectil2(
                _nave.getPosition().x + 5,
                _nave.getPosition().y - 10,
                -10, // Direccion
                _texturaProyectil, // textura del proyectil ya cargada
                0.25f  // Escala
            );

            // Agregar el proyectil a la lista de proyectiles
            _proyectiles.push_back(proyectil1);
            _proyectiles.push_back(proyectil2);
            _reloj.restart();
        }


}
void Jugador::ataqueNormal()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _reloj.getElapsedTime().asSeconds() > 0.5f)
    {
        // Crear un nuevo proyectil en la posición del jugador
        Proyectil proyectil(
            _nave.getPosition().x + (_nave.getGlobalBounds().width / 2) -10,
            _nave.getPosition().y - 10,
            -10, // Direccion
            _texturaProyectil, // textura del proyectil ya cargada
            0.25f  // Escala
        );
        // Agregar el proyectil a la lista de proyectiles
        _proyectiles.push_back(proyectil);
        _reloj.restart();
    }
}
void Jugador::setPosition(float x, float y)
{
    _nave.setPosition(x, y);
}
void Jugador::limpiarProyectiles()
{
    _proyectiles.clear(); // Limpia el vector de proyectiles
}
void Jugador::setAtaquePowerUp(bool estado){
    _ataquePowerUp = estado;
}
void Jugador::setEstaInvulnerable(bool estado){
    _estaInvulnerable = estado;
}
bool Jugador::getEstaInvulnerable ()const{
    return _estaInvulnerable;
}
bool Jugador::getAtaquePowerUp() const{
    return _ataquePowerUp;
}

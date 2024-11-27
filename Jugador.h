#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Proyectil.h"
#include "Colisionable.h"

class Jugador : public sf::Drawable, public Colisionable{
public:
    Jugador();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getPosicion() const; // Retorna la posición del jugador
    std::vector<Proyectil>& getProyectiles(); // Retorna los proyectiles del jugador
    sf::FloatRect getBounds() const; // Retorna los límites del jugador
    void setPosition(float x, float y);
    void limpiarProyectiles();
    void setEstaInvulnerable(bool estado);
    void setAtaquePowerUp(bool estado);
    bool getEstaInvulnerable() const;
    bool getAtaquePowerUp() const;
private:
    sf::Sprite _nave;
    sf::Texture _textureNave;
    sf::Texture _texturaProyectil;
    int _velocidad; // Velocidad de movimiento del jugador
    sf::Clock _reloj; // Reloj para controlar el tiempo de disparo
    bool _ataquePowerUp;
    bool _estaInvulnerable;

    void ataqueNormal();
    void ataquePowerUp();
    std::vector<Proyectil> _proyectiles; // Vector de proyectiles
};

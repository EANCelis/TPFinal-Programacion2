#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include "Proyectil.h"
#include <vector>

// Clase que representa a los enemigos en el juego
class Enemigo : public sf::Drawable, public sf::Transformable, public Colisionable {
public:
    Enemigo();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Devuelve el área de colisión del enemigo
    sf::FloatRect getBounds() const override;

    // Reinicia la posición del enemigo a una posición fuera de la pantalla
    //void resetPosition();

    virtual void setPosition(float x, float y);
    virtual void limpiarProyectiles();
    virtual void mover();

    virtual void disparar(const sf::Texture& _texturaProyectil);


    std::vector<Proyectil>& getProyectiles();

    virtual void setEstaVivo(bool estado);
    virtual bool getEstaVivo() const;


    bool puedeDisparar = false;
    // Reloj para controlar el tiempo de disparo
    sf::Clock _relojDisparo;


protected:
    bool _estaVivo = true;
    std::vector<Proyectil> _proyectiles;


private:
    sf::Sprite _proyectil;
    sf::Sprite _enemy;
    sf::Texture _textureEnemy;
    sf::Texture _texturaProyectil;

    // Distancias de movimiento a la derecha e izquierda
    float _distanciaDerecha;
    float _distanciaIzquierda;


    float _posicionInicialX;


    bool _moverDerecha;




};

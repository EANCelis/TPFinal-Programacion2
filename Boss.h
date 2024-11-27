#pragma once
#include "SFML/Graphics.hpp"
#include "Enemigo.h"

class Boss: public Enemigo{
public:
    Boss();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void setPosition(float x, float y) override;
    void setEstaVivo(bool estado);
    bool getEstaVivo() const;
    void restarVidas();
    int getVidas() const;
private:
    float _velocidad;
    sf::Vector2f _direccion; // Dirección de movimiento
    sf::Clock _relojMovimiento; // Para controlar la frecuencia de cambio de dirección

    // Reloj para controlar el tiempo de disparo
    sf::Clock _relojDisparo;

    sf::Sprite _proyectil;
    sf::Texture _texturaProyectil;

    sf::Sprite _boss;
    sf::Texture _textureBoss;
    int _vidas;
    void mover() override; // Método que maneja el movimiento aleatorio
    void cargarTexturas();
    void disparar(const sf::Texture& _texturaProyectil) override;
    void verificarBordes();
};

#pragma once
#include "Enemigo.h"
class EnemigoTipo1 : public Enemigo {
public:
    EnemigoTipo1();

    void update();
    //void setDireccion(float direccion); // Para cambiar la dirección de movimiento
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Método para dibujar
    sf::FloatRect getBounds() const override;
    void setPosition(float x, float y);



private:
    float _velocidad; // Velocidad de movimiento
    sf::Vector2f _direccion; // Dirección de movimiento
    sf::Clock _relojMovimiento; // Para controlar la frecuencia de cambio de dirección

    // Reloj para controlar el tiempo de disparo
    sf::Clock _relojDisparo;

    sf::Sprite _proyectil;
    sf::Texture _texturaProyectil;

    sf::Sprite _enemy2;
    sf::Texture _textureEnemy2;

    void mover();
    void cargarTexturas();
    void disparar(const sf::Texture& _texturaProyectil);
    void verificarBordes();
};

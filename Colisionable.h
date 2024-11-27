#pragma once
#include <SFML/Graphics.hpp>

// Clase base que define la interfaz para objetos que pueden ser colisionables.
class Colisionable {
public:
    // Método virtual puro que debe ser implementado por las clases derivadas.
    // Devuelve los límites del objeto.
    virtual sf::FloatRect getBounds() const = 0;

    // Método que verifica si hay colisión entre este objeto y otro objeto que use la interfaz.
    bool colisiono(Colisionable &col) const;
};

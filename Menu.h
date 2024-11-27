#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Menu {
public:
    Menu(float ancho, float alto, const std::vector<std::string>& items);
    void draw(sf::RenderWindow &window);
    void moverArriba();
    void moverAbajo();
    int getItemSeleccionado();
private:
    std::vector<sf::Text> menuItems;
    int indiceItemSeleccionado;

    sf::Font font;
    sf::SoundBuffer buffer;
    sf::Sound sound;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

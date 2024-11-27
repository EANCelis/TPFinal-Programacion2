#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Inicio {
public:
    Inicio(sf::RenderWindow& window);
    void run();

private:
    sf::RenderWindow& _window;
    sf::Texture _startTexture;
    sf::Sprite _startSprite;
    sf::Font _font;
    sf::Font _fontTittle;
    sf::Text _title;
    sf::Text _pressAnyKey;
    sf::SoundBuffer backgroundBuffer; // Sonido de fondo
    sf::Sound backgroundSound; // Sonido de fondo

};

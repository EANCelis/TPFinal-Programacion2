#include "Inicio.h"
#include <iostream>

Inicio::Inicio(sf::RenderWindow& window) : _window(window) {
    if (!_startTexture.loadFromFile("Recursos/file2.png")) {
        std::cerr << "Error al cargar la imagen de inicio" << std::endl;
    }
    _startSprite.setTexture(_startTexture);

    if (!_font.loadFromFile("Recursos/Erikoji Demo.otf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
    }
    if (!_fontTittle.loadFromFile("Recursos/Midnight Brush.ttf")){

    }
    if (!backgroundBuffer.loadFromFile("Recursos/Inicio-Sound.ogg")) {
        std::cerr << "Error al cargar la música de fondo" << std::endl;
    }

    backgroundSound.setBuffer(backgroundBuffer);
    backgroundSound.setLoop(true); // Hacer que suene en bucle
    backgroundSound.play(); // Reproducir la música de fondo

    _title.setFont(_fontTittle);
    _title.setString("Galactic Defenders");
    _title.setCharacterSize(70);
    _title.setPosition(1000 / 2 - 470, 50);
    _title.setFillColor(sf::Color::Red);

    _pressAnyKey.setFont(_font);
    _pressAnyKey.setString("<Press any button>");
    _pressAnyKey.setCharacterSize(40);
    _pressAnyKey.setPosition(1000 / 2 - 130, 600);
    _pressAnyKey.setFillColor(sf::Color::White);
}

void Inicio::run() {
    bool isTextVisible = true;
    sf::Clock clock;

    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            if (event.type == sf::Event::KeyPressed) {
                return; // Salir de la pantalla de inicio
            }
        }

        if (clock.getElapsedTime().asSeconds() >= 0.5f) {
            isTextVisible = !isTextVisible;
            clock.restart();
        }

        _window.clear();
        _window.draw(_startSprite);
        _window.draw(_title);
        if (isTextVisible) {
            _window.draw(_pressAnyKey);
        }
        _window.display();
    }
}

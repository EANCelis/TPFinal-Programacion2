#include "Menu.h"
#include <iostream>

Menu::Menu(float ancho, float alto, const std::vector<std::string>& items) {
    if (!font.loadFromFile("Recursos/Game Creepy.otf")) {
        // exit (-1);
    }

    if (!buffer.loadFromFile("Recursos/Menu-Select.wav")) {
       // exit (-1);
    }
    sound.setBuffer(buffer);

    if (!backgroundTexture.loadFromFile("Recursos/file2.png")) {
        // exit (-1);
    }

    backgroundSprite.setTexture(backgroundTexture);

    /*menuItems.push_back(sf::Text("Play", font, 70));
    menuItems.push_back(sf::Text("Load Game", font, 70));
    menuItems.push_back(sf::Text("Exit", font, 70));
*/
    for (const auto& item : items) {
        menuItems.push_back(sf::Text(item, font, 70));
    }

    indiceItemSeleccionado = 0;

    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].setPosition(ancho / 2 - 100, alto / (menuItems.size() + 1) * (i + 1));
        menuItems[i].setFillColor(sf::Color::White);
    }

    menuItems[indiceItemSeleccionado].setFillColor(sf::Color::Red);
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
    for (const auto &item : menuItems) {
        window.draw(item);
    }
}

void Menu::moverArriba() {
    if (indiceItemSeleccionado - 1 >= 0) {
        menuItems[indiceItemSeleccionado].setFillColor(sf::Color::White);
        indiceItemSeleccionado--;
        sound.play();
        menuItems[indiceItemSeleccionado].setFillColor(sf::Color::Red);
    }
}

void Menu::moverAbajo() {
    if (indiceItemSeleccionado + 1 < menuItems.size()) {
        menuItems[indiceItemSeleccionado].setFillColor(sf::Color::White);
        indiceItemSeleccionado++;
        sound.play();
        menuItems[indiceItemSeleccionado].setFillColor(sf::Color::Red);
    }
}
int Menu::getItemSeleccionado(){
  return indiceItemSeleccionado;
}

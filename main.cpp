#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "Inicio.h"
#include "Menu.h"
#include "Gameplay.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Galactic Defenders", sf::Style::Close);
    srand(time(0));
    window.setFramerateLimit(60);
    sf::SoundBuffer bufferSelected;
    sf::Sound soundSelected;
    if (!bufferSelected.loadFromFile("Recursos/Selected-Item.wav"))
    {

    }
    soundSelected.setBuffer(bufferSelected);
    // Pantalla de inicio
    Inicio inicio(window);
    inicio.run();

    //bool main;

    // Menú
    std::vector<std::string> items = {"Play", "Load Game", "Exit"};
    Menu menu(1000, 800, items);
    soundSelected.play();
    while (window.isOpen())
    {
        bool main = 0;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::KeyPressed)
            {

                if (event.key.code == sf::Keyboard::Up)
                {
                    menu.moverArriba();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    menu.moverAbajo();
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    soundSelected.play();
                    int itemSeleccionado = menu.getItemSeleccionado();
                    switch (itemSeleccionado)
                    {
                    case 0:
                    {
                        std::cout << "Play" << std::endl;
                        Gameplay game(window);
                        game.run();
                        std::cout << "Termino el juego" << std::endl;
                        break;
                    }
                    case 1:
                    {
                        std::cout << "Load Game" << std::endl;

                        std::vector<std::string> slots = {"<Slot 1>", "<Slot 2>", "<Slot 3>", "<Slot 4>"};
                        Menu loadMenu(1000, 800, slots);

                        // Bucle para el menú de carga
                        while (!main)
                        {
                            sf::Event loadEvent;
                            while (window.pollEvent(loadEvent))
                            {
                                if (loadEvent.type == sf::Event::Closed)
                                {
                                    window.close();
                                    return 0;
                                }



                                if (loadEvent.type == sf::Event::KeyPressed)
                                {
                                    if (loadEvent.key.code == sf::Keyboard::Up)
                                    {
                                        loadMenu.moverArriba();
                                    }
                                    else if (loadEvent.key.code == sf::Keyboard::Down)
                                    {
                                        loadMenu.moverAbajo();
                                    }
                                    else if (loadEvent.key.code == sf::Keyboard::Enter)
                                    {
                                        soundSelected.play();
                                        int itemSeleccionado = loadMenu.getItemSeleccionado();
                                        std::string filename = "partidas.dat";
                                        Gameplay game(window);
                                        game.cargarEstado(filename, itemSeleccionado);
                                        game.run();
                                        main = 1;
                                        break;
                                    }
                                }
                            }

                            window.clear();
                            loadMenu.draw(window);
                            window.display();
                        }
                        break;
                    }
                    case 2:
                        std::cout << "Exit" << std::endl;
                        window.close();
                        //break;
                    }

                }
            }
        }
        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}

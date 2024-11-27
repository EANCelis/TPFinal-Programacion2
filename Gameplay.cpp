#include "Gameplay.h"
#include <cstdlib>
#include <ctime>
#include "Colisionable.h"
#include "Enemigo.h"
#include "Jugador.h"
#include "Proyectil.h"
#include "EnemigoTipo1.h"
#include "EnemigoKamikaze.h"
#include "PowerUp.h"
#include "EstadoDeJuego.h"
#include "Menu.h"
#include "iostream"

Gameplay::Gameplay(sf::RenderWindow& window): _juego(window)
{
    _gameOver = false;
    _nivelCambiado = false;
    _reiniciarNivel = false;
    _mostrarWinLevelTexto = false;
    _tiempoEspera = 5.0f;
    _enemigosTipo2Inicializados = false;
    cargarTexturas();
    inicializarPartidas();
    _puntos = 0;
    _vidas = 3;
    _nivel = 1;
    _estaInvulnerable = false;
    _ganoElJuego = false;
}
void Gameplay::run()
{
    std::cout << "Nivel cuando se runea: " << _nivel << std::endl;
    inicializarEnemigos();
    sf::Event event;
    while (_juego.isOpen())
    {

        while (_juego.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _juego.close();
            }
        }
        if (perdioElJuego() && !_gameOver)
        {

            _gameOver = true; // Cambia el estado a Game Over
            _relojGameOver.restart(); // Reinicia el temporizador

        }
        else if (ganoElJuego() && !_ganoElJuego)
        {

            _ganoElJuego = true;
            _relojVictoria.restart(); // Reinicia el temporizador para el mensaje de victoria

        }

        if (!_gameOver)
        {
            if (cambioDeNivel() && !_nivelCambiado)
            {
                _nivelCambiado = true; // Indica que ya se ha cambiado de nivel
                _mostrarWinLevelTexto = true; // Activa la visualización del texto
                _relojWinLevel.restart(); // Reinicia el temporizador
                _enemigosTipo2Inicializados = false;
            }
            else if (!cambioDeNivel())
            {
                _nivelCambiado = false; // Solo restablece si no hay cambio
            }

            // Verifica si el texto debe ocultarse después de un tiempo
            if (_mostrarWinLevelTexto)
            {
                if (_relojWinLevel.getElapsedTime().asSeconds() > 5.0f)
                {
                    _mostrarWinLevelTexto = false;
                    _nivel++;
                    std::cout << "Cambiando de nivel de " << _nivel << " a " << (_nivel + 1) << std::endl;
                    preguntarGuardar();
                    reiniciarNivel();
                    inicializarEnemigos();
                }
            }
            else
            {
                update();
            }

            _juego.clear();
            draw(_juego, sf::RenderStates::Default);
            _juego.display();
        }
        else
        {
            if (_relojGameOver.getElapsedTime().asSeconds() > _tiempoEspera)
            {
                return; // Regresa al menú
            }
        }
        if (ganoElJuego() && _ganoElJuego)
        {
            if (_relojVictoria.getElapsedTime().asSeconds() < 10.0f)
            {
                _juego.clear();
                draw(_juego, sf::RenderStates::Default);
                _juego.display();
            }
            else
            {
                _ganoElJuego = false;
                return; // Regresa al menú
            }
        }
    }
}


void Gameplay::inicializarEnemigos()
{
    //_jugador.setPosition(500, 700);
    std::cout << "Dibujando nivel: " << _nivel << std::endl;
    const int columnas = 9; // Total de enemigos tipo 1
    const float espacioEntreNaves = 50.0f;
    const float inicioY = 50.0f; // Posición Y inicial de los enemigos

    // Inicializa enemigos tipo 1
    if(_nivel == 1)
    {
        for (int j = 0; j < columnas; j++)
        {
            _enemigos[j].setPosition(j * (50 + espacioEntreNaves), inicioY + (10 + espacioEntreNaves));
            _enemigos[j].setEstaVivo(1);
        }
        _cantEnemigos = columnas;

    }

    else if (_nivel == 2 && !_enemigosTipo2Inicializados)
    {
        // Inicializa enemigos tipo 1
        for (int j = 0; j < columnas; j++)
        {
            _enemigos[j].setPosition(j * (50 + espacioEntreNaves), inicioY + (10 + espacioEntreNaves));
            _enemigos[j].setEstaVivo(1);
        }
        const int enemigosTipo2 = 4; // Número de enemigos tipo 2
        for (int x = 0; x < enemigosTipo2; x++)
        {
            _enemigosTipo2[x].setPosition(rand() % 800 + 100, 50);
            _enemigosTipo2[x].setEstaVivo(1);
        }
        _cantEnemigos = columnas + enemigosTipo2;
        _enemigosTipo2Inicializados = true;
    }
    else if (_nivel == 3 && !_enemigosTipo2Inicializados)
    {
        // Inicializa enemigos tipo 1
        for (int j = 0; j < columnas; j++)
        {
            _enemigos[j].setPosition(j * (50 + espacioEntreNaves), inicioY*2 + (10 + espacioEntreNaves));
            _enemigos[j].setEstaVivo(1);
        }
        const int enemigosTipo2 = 4; // Número de enemigos tipo 2
        for (int x = 0; x < enemigosTipo2; x++)
        {
            _enemigosTipo2[x].setPosition(rand() % 800 + 100, 50); // Posición aleatoria
            _enemigosTipo2[x].setEstaVivo(1);
        }
        _cantEnemigos = columnas + enemigosTipo2 + 1;
        _enemigosTipo2Inicializados = true;

        _boss.setPosition(1000/2, 20);
        _boss.setEstaVivo(1);
    }

}
void Gameplay::asignarDisparoEnemigoAleatorio()
{


    for(int i=0; i<9; i++)
    {
        int columnaAleatoria = rand() % 9;
        if (_enemigos[columnaAleatoria].getEstaVivo())
        {
            _enemigos[columnaAleatoria].puedeDisparar = true;
            return;
        }
    }


}
void Gameplay::asignarDisparoBoss()
{
    int random = rand() % 2;
    if (random ==1 && _boss.getEstaVivo())
    {
        _boss.puedeDisparar = true;
    }
}
void Gameplay::asignarDisparoEnemigoAleatorioEnemigoTipo1()
{

    for (int x=0; x<4; x++)
    {
        int columnaAleatoria = rand() % 4;
        if (_enemigosTipo2[columnaAleatoria].getEstaVivo())
        {
            _enemigosTipo2[columnaAleatoria].puedeDisparar = true;
            break;
        }

    }

}


void Gameplay::update()
{

    if (_boss.getEstaVivo() && _boss.getVidas() == 0)
    {
        _boss.setEstaVivo(0);
        _cantEnemigos--;
    }
    if (_jugador.getEstaInvulnerable() && _relojInvulnerabilidad.getElapsedTime().asSeconds() > 3.0f)
    {
        _jugador.setEstaInvulnerable(0);
    }

    if (_jugador.getAtaquePowerUp() && _relojAtaquePowerUp.getElapsedTime().asSeconds() > 3.0f)
    {
        _jugador.setAtaquePowerUp(0);
    }

    if (perdioElJuego() || ganoElJuego())
    {
        //std::cout << "Game Over" << std::endl;
        return; // Termina el juego
    }
    _jugador.update();

    for (int i = 0; i < 2; i++)
    {
        _enemigosTipo3[i].update();
    }

    for (int i=0; i<9; i++)
    {
        _enemigos[i].update();
    }

    if (_nivel > 1 && _enemigosTipo2Inicializados)
    {
        for(int x=0; x<4; x++)
        {
            _enemigosTipo2[x].update();
        }
        if (relojAsignacionTipo1.getElapsedTime().asSeconds() > 1.0f)
        {
            asignarDisparoEnemigoAleatorioEnemigoTipo1();
            relojAsignacionTipo1.restart();
        }

    }
    if (_boss.getEstaVivo())
    {
        _boss.update();
    }
    _powerUp.update();

    //std::cout << "Esta atacando con powerup en: " << _jugador.getAtaquePowerUp() << std::endl;

    if (!_jugador.getEstaInvulnerable())
    {
        verificarColisionProyectilEnemigoTipo1YJugador();
        verificarColisionProyectilesEnemigoYJugador();
        verificarColisionEnemigoKamikazeYJugador();
        verificarColisionProyectilBossYJugador();
        //_relojInvulnerabilidad.restart();

    }

    verificarColisionProyectilesJugadorYBoss();
    verificarColisionProyectilesJugadorYEnemigo();
    verificarColisionProyectilesJugadorYEnemigos2();
    verificarColisionProyectilesJugadorYKamikaze();
    verificarColisionJugadorYPowerUp();



    if (_relojGeneracionPowerUp.getElapsedTime().asSeconds() > 9.0f)
    {
        generarPowerUp();
        _relojGeneracionPowerUp.restart();
    }



    // Asigna nuevo disparo a un enemigo cada cierto tiempo

    if (relojAsignacion.getElapsedTime().asSeconds() > 0.8f)
    {
        asignarDisparoEnemigoAleatorio();
        asignarDisparoBoss();
        relojAsignacion.restart();
    }

    _puntosTexto.setString(std::to_string(_puntos));

}
void Gameplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    _fondo.draw(target);
    _jugador.draw(target, states);
    for (int i=0; i<9; i++)
    {
        _enemigos[i].draw(target, states);
    }
    if (_nivel > 1 && _enemigosTipo2Inicializados)
    {
        for(int x=0; x<4; x++)
        {
            _enemigosTipo2[x].draw(target, states);
        }

    }
    if(_nivel == 3 && _boss.getEstaVivo())
    {
        _boss.draw(target, states);
    }
    dibujarVidas(target, states);
    target.draw(_puntosTexto);

    if (_powerUp.estaActivo())
    {
        _powerUp.draw(target);
    }
    for (int i = 0; i < 2; i++)
    {
        _enemigosTipo3[i].draw(target, states);
    }

    if(_jugador.getEstaInvulnerable())
    {
        dibujarEscudoPowerUp(target, states);
    }
    if (perdioElJuego())
    {
        target.draw(_gameOverTexto);
    }
    if (ganoElJuego())
    {
        target.draw(_winGameTexto);
    }
    if (_mostrarWinLevelTexto && _nivel < 3)
    {
        target.draw(_winLevelTexto);
    }
}

void Gameplay::verificarColisionProyectilEnemigoTipo1YJugador()
{
    if (_relojColisionProyectilesTipo1.getElapsedTime().asSeconds() > 1.5f)
    {
        for (int j = 0; j < 4; j++)
        {
            if (_enemigosTipo2[j].getEstaVivo())
            {
                auto& proyectiles = _enemigosTipo2[j].getProyectiles();
                //std::cout << "Total de proyectiles en enemigo " << j << ": " << proyectiles.size() << std::endl;

                for (int k = 0; k < proyectiles.size(); k++)
                {
                    if (proyectiles[k].colisiono(_jugador))
                    {
                        restarVidas();
                        proyectiles.erase(proyectiles.begin() + k);
                        _relojColisionProyectilesTipo1.restart();
                        k--;
                    }
                }
            }
        }
    }
}
void Gameplay::verificarColisionProyectilBossYJugador()
{
    if (_boss.getEstaVivo())
    {
        auto& proyectiles = _boss.getProyectiles();
        for (int x=0; x<proyectiles.size(); x++)
        {
            if(proyectiles[x].colisiono(_jugador))
            {
                restarVidas();
                proyectiles.erase(proyectiles.begin() + x);
                x--;
            }
        }
    }
}
void Gameplay::verificarColisionEnemigoKamikazeYJugador()
{
    if (_relojColisionKamikaze.getElapsedTime().asSeconds() > 5.0f)
    {
        for (int x=0; x<2; x++)
        {
            if (_enemigosTipo3[x].colisiono(_jugador))
            {
                restarVidas();
                _enemigosTipo3[x].setEstaVivo(0);
                _relojColisionKamikaze.restart();
            }
        }
    }
}
void Gameplay::verificarColisionProyectilesEnemigoYJugador()
{
    if (_relojColisionProyectiles.getElapsedTime().asSeconds() > 1.0f)
    {
        for (int j = 0; j < 9; j++)
        {
            if (_enemigos[j].getEstaVivo())
            {
                auto& proyectiles = _enemigos[j].getProyectiles(); // Obtengo los proyectiles del enemigo

                for (int k = 0; k < proyectiles.size(); k++)
                {
                    if (proyectiles[k].colisiono(_jugador))
                    {
                        restarVidas();
                        proyectiles.erase(proyectiles.begin() + k);
                        _relojColisionProyectiles.restart();
                        k--;
                    }
                }
            }
        }


    }

}

void Gameplay::verificarColisionProyectilesJugadorYKamikaze()
{
    // Obtengo los proyectiles del jugador
    auto& proyectiles = _jugador.getProyectiles();


    for (int i = 0; i < proyectiles.size(); i++)
    {



        for (int k = 0; k < 2; k++)
        {
            if (_enemigosTipo3[k].getEstaVivo() && proyectiles[i].colisiono(_enemigosTipo3[k]))
            {
                aumentarPuntos(rand() % 51 + 20); // Aumento los puntos
                _enemigosTipo3[k].setEstaVivo(0); // Marco al enemigo kamikaze como no vivo
                proyectiles.erase(proyectiles.begin() + i); // Elimino el proyectil
                i--; // Ajusto el índice
                break; // Salgo del bucle de enemigos
            }
        }

    }
}
void Gameplay::verificarColisionProyectilesJugadorYBoss()
{
    auto& proyectiles = _jugador.getProyectiles();
    for (int x=0; x<proyectiles.size(); x++)
    {
        if(_boss.getEstaVivo() && proyectiles[x].colisiono(_boss))
        {
            _boss.restarVidas();
            proyectiles.erase(proyectiles.begin() + x);
            x--;
            std::cout << "Colisiono con el BOSS" << std::endl;
            break;
        }
    }
}
void Gameplay::verificarColisionProyectilesJugadorYEnemigos2()
{
    // Obtengo los proyectiles del jugador
    auto& proyectiles = _jugador.getProyectiles();

    // Recorro cada proyectil del jugador
    for (int i = 0; i < proyectiles.size(); i++)
    {


        for (int k = 0; k < 4; k++)   // Suponiendo que hay 4 enemigos
        {
            if (_enemigosTipo2[k].getEstaVivo() && proyectiles[i].colisiono(_enemigosTipo2[k]))
            {
                aumentarPuntos(rand() % 121 + 70); // Aumento los puntos
                _enemigosTipo2[k].setEstaVivo(0); // Marco al enemigo como no vivo
                _cantEnemigos--;
                proyectiles.erase(proyectiles.begin() + i); // Elimino el proyectil
                i--;
                break; // Salimos del bucle de enemigos
            }
        }
    }
}
void Gameplay::verificarColisionProyectilesJugadorYEnemigo()
{
    // Obtengo los proyectiles del jugador
    auto& proyectiles = _jugador.getProyectiles();

    // Recorro cada proyectil del jugador
    for (int i = 0; i < proyectiles.size(); i++)
    {

        // Recorro los enemigos
        for (int k = 0; k < 9; k++)
        {
            if (_enemigos[k].getEstaVivo() && proyectiles[i].colisiono(_enemigos[k]))
            {
                aumentarPuntos(rand() % 51 + 50); // Aumento los puntos
                _cantEnemigos--;
                _enemigos[k].setEstaVivo(0); // Marco al enemigo como no vivo
                proyectiles.erase(proyectiles.begin() + i); // Elimino el proyectil
                i--;
                break;
            }
        }

    }
}

int Gameplay::getPuntos() const
{
    return _puntos;

}
int Gameplay::getVidas() const
{
    return _vidas;
}
void Gameplay::aumentarPuntos(int p)
{
    _puntos+=p;
}
void Gameplay::restarVidas()
{
    if (_vidas > 0)
    {
        _vidas--;
    }
}
void Gameplay::dibujarVidas(sf::RenderTarget& target, sf::RenderStates states) const
{

// Dibujar corazones o vidas perdidas
    sf::Sprite vidaSprite;
    for (int x = 0; x < 3; x++)
    {
        if (x < _vidas)
        {
            vidaSprite = _corazonSprite;
        }
        else
        {
            vidaSprite = _corazonPerdidoSprite;
        }
        vidaSprite.setPosition(10 + x * 50, 10); // Ajusta la posición
        target.draw(vidaSprite, states); // Dibuja el sprite
    }
}

bool Gameplay::perdioElJuego() const
{
    return _vidas < 1;
}
void Gameplay::verificarColisionJugadorYPowerUp()
{

    if (_powerUp.estaActivo())
    {
        if (_powerUp.colisiono(_jugador) && _powerUp.getTipo() == 0)
        {
            aumentarVidas();
            _powerUp.desactivar();

        }
        else if(_powerUp.colisiono(_jugador) && _powerUp.getTipo() == 1)
        {
            _jugador.setEstaInvulnerable(1);
            std::cout << "Esta invulnerable: " << _jugador.getEstaInvulnerable() << std::endl;
            _relojInvulnerabilidad.restart();
            _powerUp.desactivar();
        }
        else if(_powerUp.colisiono(_jugador) && _powerUp.getTipo() == 2)
        {
            _jugador.setAtaquePowerUp(1);
            _relojAtaquePowerUp.restart();
            _powerUp.desactivar();
        }
        else
        {
            _powerUp.update();
        }
    }

}
void Gameplay::dibujarEscudoPowerUp(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite escudoSprite;
    escudoSprite.setTexture(_texturaArmaduraPowerUp);
    escudoSprite.setPosition(_jugador.getPosicion().x + 10, _jugador.getPosicion().y - 50);
    escudoSprite.setScale(0.2f, 0.2f);
    target.draw(escudoSprite, states);
}
void Gameplay::generarPowerUp()
{
    if (!_powerUp.estaActivo())
    {
        int randPowerUp = rand() % 3;
        std::cout << "random : " << randPowerUp << std::endl;
        switch (randPowerUp)
        {
        case 0:
            _powerUp = PowerUp(_texturaCorazonPowerUp);
            _powerUp.setTipo(randPowerUp);
            break;
        case 1:
            _powerUp = PowerUp(_texturaArmaduraPowerUp);
            _powerUp.setTipo(randPowerUp);
            break;
        case 2:
            _powerUp = PowerUp(_texturaAtaquePowerUp);
            _powerUp.setTipo(randPowerUp);
            break;
        }

        _powerUp.activar();
    }
}
void Gameplay::cargarTexturas()
{
    if (!_texturaCorazonPowerUp.loadFromFile("Recursos/corazon.png"))
    {
    }
    if (!_texturaArmaduraPowerUp.loadFromFile("Recursos/armadura.png"))
    {

    }
    if (!_texturaAtaquePowerUp.loadFromFile("Recursos/ataque.png"))
    {

    }
    if (!bufferSelected.loadFromFile("Recursos/Selected-Item.wav"))
    {

    }
    soundSelected.setBuffer(bufferSelected);
    if (!_corazonTexture.loadFromFile("Recursos/0.png"))
    {

    }
    _corazonSprite.setTexture(_corazonTexture);

    _corazonSprite.setScale(0.5f, 0.5f);

    if (!_corazonPerdidoTexture.loadFromFile("Recursos/2.png"))
    {

    }
    _corazonPerdidoSprite.setTexture(_corazonPerdidoTexture);
    _corazonPerdidoSprite.setScale(0.5f, 0.5f);

    // Cargar fuente para el texto
    if (!_font.loadFromFile("Recursos/Midnight Brush.ttf"))
    {

    }
    _puntosTexto.setFont(_font);
    _puntosTexto.setCharacterSize(12);
    _puntosTexto.setFillColor(sf::Color::White);
    _puntosTexto.setPosition(150, 10);

    // Inicializa el texto de Game Over
    _gameOverTexto.setFont(_font);
    _gameOverTexto.setCharacterSize(50);
    _gameOverTexto.setFillColor(sf::Color::Red);
    _gameOverTexto.setString("Game Over");
    _gameOverTexto.setPosition(300, 300);

    // Inicializa el texto de Game Over
    _winGameTexto.setFont(_font);
    _winGameTexto.setCharacterSize(50);
    _winGameTexto.setFillColor(sf::Color::Red);
    _winGameTexto.setString("GALACTIC CHAMPION!");
    _winGameTexto.setPosition(100, 300);

    // Inicializa el texto de Game Over
    _winLevelTexto.setFont(_font);
    _winLevelTexto.setCharacterSize(40);
    _winLevelTexto.setFillColor(sf::Color::Red);
    _winLevelTexto.setString("Level Cleared!");
    _winLevelTexto.setPosition(260, 300);
}
void Gameplay::aumentarVidas()
{
    if (_vidas > 0 && _vidas < 3)
    {
        _vidas++;
    }
}
void Gameplay::guardarEstado(const std::string& archivo, int slot)
{
    EstadoDeJuego estado;
    estado.setPuntos(getPuntos());
    estado.setVidas(getVidas());
    estado.setNivel(getNivel());
    std::cout << "Puntos: " << estado.getPuntos() << ", vidas: " << estado.getVidas() << " Nivel: " << getNivel() <<  std::endl;
    estado.guardar(archivo, slot);

}

void Gameplay::cargarEstado(const std::string& archivo, int slot)
{
    EstadoDeJuego estado;
    estado.cargar(archivo, slot);
    _puntos = estado.getPuntos();
    _vidas = estado.getVidas();
    _nivel = estado.getNivel();
    std::cout << "Puntos: " << estado.getPuntos() << ", vidas: " << estado.getVidas() << " Nivel: " << getNivel() <<  std::endl;
}
void Gameplay::preguntarGuardar()
{

    bool preguntaActiva = true;


    sf::Text preguntaTexto;
    preguntaTexto.setFont(_font);
    preguntaTexto.setCharacterSize(25);
    preguntaTexto.setFillColor(sf::Color::White);
    preguntaTexto.setString("Presiona S para guardar o N para no guardar");
    preguntaTexto.setPosition(80, 300);

    while (preguntaActiva)
    {
        sf::Event saveEvent;
        while (_juego.pollEvent(saveEvent))
        {
            if (saveEvent.type == sf::Event::Closed)
            {
                _juego.close();
                return;
            }

            if (saveEvent.type == sf::Event::KeyPressed)
            {
                if (saveEvent.key.code == sf::Keyboard::S)
                {
                    soundSelected.play();
                    preguntaActiva = false;

                    std::vector<std::string> slots = {"<Slot 1>", "<Slot 2>", "<Slot 3>", "<Slot 4>"};
                    Menu saveMenu(_juego.getSize().x, _juego.getSize().y, slots);

                    while (true)
                    {
                        sf::Event saveEvent;
                        while (_juego.pollEvent(saveEvent))
                        {
                            if (saveEvent.type == sf::Event::Closed)
                            {
                                _juego.close();
                                return;
                            }

                            if (saveEvent.type == sf::Event::KeyPressed)
                            {
                                if (saveEvent.key.code == sf::Keyboard::Up)
                                {
                                    saveMenu.moverArriba();
                                }
                                else if (saveEvent.key.code == sf::Keyboard::Down)
                                {
                                    saveMenu.moverAbajo();
                                }
                                else if (saveEvent.key.code == sf::Keyboard::Enter)
                                {
                                    soundSelected.play();
                                    int itemSeleccionado = saveMenu.getItemSeleccionado();
                                    std::string archivo = "partidas.dat";
                                    guardarEstado(archivo, itemSeleccionado); // Guarda el estado
                                    return;
                                }
                            }
                        }

                        _juego.clear();
                        saveMenu.draw(_juego);
                        //_juego.draw(preguntaTexto);
                        _juego.display();
                    }
                }
                else if (saveEvent.key.code == sf::Keyboard::N)
                {
                    preguntaActiva = false;
                }
            }
        }


        _juego.clear();
        _juego.draw(preguntaTexto);
        _juego.display();
    }
}

bool Gameplay::ganoElJuego() const
{
    return (_nivel == 3 && _cantEnemigos <= 0);
}
bool Gameplay::cambioDeNivel() const
{
    if((_nivel < 3) && _cantEnemigos <= 0)
    {
        return true;
    }
    return false;

}
int Gameplay::getNivel() const
{
    return _nivel;
}
void Gameplay::inicializarPartidas()
{
    const std::string archivo = "partidas.dat";
    FILE* file = fopen(archivo.c_str(), "rb");
    if (!file)
    {
        EstadoDeJuego estado;
        estado.inicializarArchivo(archivo, 4); // Inicializa 4 slots por defecto
    }
    else
    {
        fclose(file);
    }
}
void Gameplay::reiniciarNivel()
{

    for (int i = 0; i < 9; i++)
    {
        _enemigos[i].setEstaVivo(0);
        _enemigos[i].limpiarProyectiles();
    }


    for (int i = 0; i < 4; i++)
    {
        _enemigosTipo2[i].setEstaVivo(0);
        _enemigosTipo2[i].limpiarProyectiles();
    }


    for (int i = 0; i < 2; i++)
    {
        _enemigosTipo3[i].setEstaVivo(0);
        _enemigosTipo3[i].reiniciarReloj();
    }


    _jugador.setPosition(500, 700);
    _jugador.limpiarProyectiles();

    _powerUp.desactivar();


    _enemigosTipo2Inicializados = false;

    relojAsignacionTipo1.restart();
    _relojGeneracionPowerUp.restart();
    relojAsignacion.restart();


}

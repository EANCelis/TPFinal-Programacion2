#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Fondo.h"
#include "Jugador.h"
#include "Enemigo.h"
#include "EnemigoTipo1.h"
#include "EnemigoKamikaze.h"
#include "PowerUp.h"
#include "Boss.h"

class Gameplay : public sf::Drawable
{
public:
    Gameplay(sf::RenderWindow& window);
    void run();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    int getPuntos() const;
    int getVidas() const;
    int getNivel() const;
    void guardarEstado(const std::string& archivo, int slot);
    void cargarEstado(const std::string& archivo, int slot);



private:
    sf::Clock _relojGameOver; // Temporizador para Game Over
    bool _gameOver;

    bool _mostrarWinLevelTexto; // Bandera para saber si mostrar el texto
    sf::Clock _relojWinLevel; // Temporizador para el texto de "Level Cleared!"

    bool _enemigosTipo2Inicializados = false;
    bool _reiniciarNivel;

    float _tiempoEspera;
    int _nivel;
    int _cantEnemigos;
    Fondo _fondo;
    Jugador _jugador;
    Enemigo _enemigos[9];
    EnemigoTipo1 _enemigosTipo2[4];
    EnemigoKamikaze _enemigosTipo3[2];
    Boss _boss;

    bool _nivelCambiado;
    bool _ganoElJuego;

    PowerUp _powerUp;
    PowerUp _aux;
    sf::SoundBuffer bufferSelected;
    sf::Sound soundSelected;

    sf::RenderWindow& _juego;

    sf::Font _font;
    sf::Text _gameOverTexto;
    sf::Text _winGameTexto;
    sf::Text _winLevelTexto;

    bool _estaInvulnerable;

    sf::Sprite _corazonSprite;
    sf::Texture _corazonTexture;
    sf::Texture _corazonPerdidoTexture; // Textura para vida perdida
    sf::Sprite _corazonPerdidoSprite; // Sprite para vida perdida

    sf::Texture _texturaCorazonPowerUp;
    sf::Texture _texturaArmaduraPowerUp;
    sf::Texture _texturaAtaquePowerUp;

    int _vidas;
    int _puntos;
    sf::Text _puntosTexto;

    sf::Clock _relojColisionProyectiles; // Reloj para controlar la verificación de colisiones
    sf::Clock _relojColisionProyectilesTipo1;
    sf::Clock _relojColisionKamikaze;
    sf::Clock relojAsignacion;
    sf::Clock relojAsignacionTipo1;
    sf::Clock _relojGeneracionPowerUp; // Reloj para controlar la generación de power ups
    sf::Clock _relojVictoria;
    sf::Clock _relojInvulnerabilidad;
    sf::Clock _relojAtaquePowerUp;

    void reiniciarNivel();
    void inicializarEnemigos(); // Inicializa la posición de los enemigos
    bool cambioDeNivel() const;
    void preguntarGuardar();
    void aumentarPuntos(int p);
    void restarVidas();
    bool perdioElJuego() const;
    void inicializarPartidas();

    void dibujarEscudoPowerUp(sf::RenderTarget& target, sf::RenderStates states) const;
    void dibujarVidas(sf::RenderTarget& target, sf::RenderStates states) const;
    void inicializarTextoGameOver();

    void aumentarVidas();
    void cargarTexturas();

    bool ganoElJuego() const;
    void verificarColisionProyectilesJugadorYEnemigo();
    void verificarColisionProyectilesJugadorYEnemigos2();
    void verificarColisionProyectilesJugadorYKamikaze();
    void verificarColisionProyectilesEnemigoYJugador();
    void verificarColisionEnemigoKamikazeYJugador();
    void verificarColisionProyectilEnemigoTipo1YJugador();
    void verificarColisionProyectilBossYJugador();
    void verificarColisionProyectilesJugadorYBoss();

    void asignarDisparoBoss();
    void asignarDisparoEnemigoAleatorio(); // Método que asigna un disparo a un enemigo
    void asignarDisparoEnemigoAleatorioEnemigoTipo1();

    void verificarColisionJugadorYPowerUp();
    void generarPowerUp(); // Método para generar un power up
};

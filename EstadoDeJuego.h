#pragma once
#include <string>

class EstadoDeJuego {
public:
    EstadoDeJuego();

    void inicializarArchivo(const std::string& archivo,int tam);

    //void guardar(const std::string& archivo) const;
    void guardar(const std::string& archivo, int slot) const;

    //void cargar(const std::string& archivo);
    void cargar(const std::string& archivo, int slot);
    int getPuntos() const { return _puntos; }
    int getVidas() const { return _vidas; }
    int getNivel() const {return _nivel;}

    void setPuntos(int puntos) { _puntos = puntos; }
    void setVidas(int vidas) { _vidas = vidas; }
    void setNivel(int nivel) {_nivel = nivel;}

private:
    int _puntos;
    int _vidas;
    int _nivel;
};

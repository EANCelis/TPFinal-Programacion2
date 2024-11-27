#include "EstadoDeJuego.h"
#include <cstdio>
#include <cstring>
#include <iostream>
EstadoDeJuego::EstadoDeJuego(){
    _puntos = 0;
    _vidas = 3;
    _nivel = 1;
}
/*void EstadoDeJuego::guardar(const std::string& archivo) const
{
    FILE* pFile = fopen(archivo.c_str(), "ab");
    if (pFile)
    {
        fwrite(this, sizeof(EstadoDeJuego), 1, pFile);
        fclose(pFile);
    }
}*/
void EstadoDeJuego::guardar(const std::string& archivo, int slot) const {
    FILE* file = fopen(archivo.c_str(), "rb+"); // Abrir en modo lectura y escritura
    if (file) {
        fseek(file, slot * sizeof(EstadoDeJuego), SEEK_SET); // Moverse a la posición del slot
        fwrite(this, sizeof(EstadoDeJuego), 1, file);
        fclose(file);
    }
    else{
        std::cout << "No se pudo abrir el archivo para guardar =(" << std::endl;
        //exit (-1);
    }
}

/*void EstadoDeJuego::cargar(const std::string& archivo)
{
    FILE* pFile = fopen(archivo.c_str(), "rb");
    if (pFile)
    {
        fread(this, sizeof(EstadoDeJuego), 1, pFile);
        fclose(pFile);
    }
}
*/
void EstadoDeJuego::cargar(const std::string& archivo, int slot) {
    FILE* file = fopen(archivo.c_str(), "rb");
    if (file) {
        fseek(file, slot * sizeof(EstadoDeJuego), SEEK_SET); // Moverse a la posición del slot
        fread(this, sizeof(EstadoDeJuego), 1, file);
        fclose(file);
    }
    else{
        std::cout << "No se pudo abrir el archivo para cargar =(" << std::endl;
        //exit (-1);
    }
}
void EstadoDeJuego::inicializarArchivo(const std::string& archivo,int tam){
    FILE* pFile = fopen(archivo.c_str(), "wb");
    if (pFile)
    {
        for (int x=0; x<tam; x++){
            fwrite(this, sizeof(EstadoDeJuego), 1, pFile);
        }
        fclose(pFile);
    }
}

# TP Final Programación 2 | Juego 2D: Galactic Defenders

Galactic Defender es un juego de disparos 2D donde el jugador controla una nave espacial para destruir enemigos y evitar que se acerquen. El objetivo es sobrevivir a los ataques enemigos mientras recoges potenciadores y aumentas tu puntaje. El juego incluye múltiples niveles, power-ups, y la posibilidad de guardar y cargar el progreso.
Características

    Colisión entre proyectiles y enemigos: Los proyectiles del jugador pueden destruir enemigos y aumentar el puntaje.
    Power-ups: El jugador puede recoger power-ups que le otorgan beneficios como vidas extra, invulnerabilidad o potenciadores de ataque.
    Guardado y carga de partidas: Los jugadores pueden guardar su progreso y cargarlo en una sesión futura.
    Niveles y enemigos: El jugador enfrenta a diferentes tipos de enemigos que se vuelven más difíciles a medida que avanza.
    Pantalla de Game Over y mensajes: El juego tiene pantallas para cuando el jugador pierde o completa un nivel.
    
Uso

    Controles:
        Teclas de flecha: Mover la nave del jugador.
        Espacio: Disparar proyectiles.
        S: Guardar el progreso del juego.
        N: No guardar el progreso y continuar jugando.

    Objetivos:
        Destruye a los enemigos para ganar puntos.
        Recoge power-ups para obtener ventajas (vidas extra, invulnerabilidad, ataque más fuerte).
        Supera niveles enfrentándote a enemigos cada vez más poderosos.
        Si pierdes todas las vidas, el juego termina.
        
Estructura del Código

Este repositorio contiene el código fuente principal del juego. A continuación se detalla la estructura de algunos archivos clave:

    Gameplay.cpp: Contiene la lógica principal del juego, incluyendo la detección de colisiones entre proyectiles, enemigos y el jugador, así como la gestión de puntuaciones y vidas.
    Jugador.cpp: Define la clase del jugador, incluyendo su movimiento, disparos y vida.
    Enemigo.cpp: Define la lógica para los enemigos, su movimiento y la gestión de colisiones con los proyectiles.
    PowerUp.cpp: Contiene la lógica de los power-ups, que afectan al jugador de diferentes maneras.
    EstadoDeJuego.cpp: Maneja la carga y el guardado del estado del juego, permitiendo que el jugador guarde su progreso.

Notas

    Dependencias: Este proyecto depende de SFML para gráficos y sonidos. Asegúrate de tener las librerías correctamente configuradas en tu sistema.
    Archivos de recursos: Este juego utiliza varios archivos de imagen y sonido que deben estar en la carpeta correcta para que el juego funcione correctamente.

![Captura desde 2024-11-26 19-35-39](https://github.com/user-attachments/assets/8e3bcfed-e4ee-47ec-be8e-c93fd75d4110)

![Captura desde 2024-11-26 19-35-59](https://github.com/user-attachments/assets/102d1a1a-cee3-4f39-a959-8c7368ee1c7d)

![Captura desde 2024-11-26 19-36-14](https://github.com/user-attachments/assets/2fc64a9e-9f22-40ab-a1c9-4254e1a2b554)



[Ver el video en Vimeo](https://vimeo.com/1033662102/ff2239574f?share=copy)








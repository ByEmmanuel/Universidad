#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

using namespace std;
using namespace sf;

class ondas_aleatorias{
private:

// float t = 0.0f;
    // float freq = 1.0f;
    // float amp = 50.0f;
    // float speed = 0.05f;

    float t; // rango 1.0 ≤ x ≤ 0.0
    float freq; //rango 0.0 ≤ x ≤ 30.0
    float speed; //rango 1.0 ≤ x ≤ 0.001
    float amp;  //rango 0.0 ≤ x ≤ 100.0

    // generador aleatorio
    mt19937 gen;
    uniform_real_distribution<float> dist_freq;
    uniform_real_distribution<float> dist_amp;
    uniform_real_distribution<float> dist_speed;

public:
    ondas_aleatorias()
        : 
        gen(random_device{}()),
        dist_freq(0.5f, 10.0f),
        dist_amp(20.0f, 100.0f),
        dist_speed(0.01f, 0.02f)
    {
        randomize();
    }
    void randomize(){
        freq = dist_freq(gen);
        amp = dist_amp(gen);
        speed = dist_speed(gen);
    }

    float get_freq() { return this->freq; }
    float get_amp() { return this->amp; }
    float get_speed() { return this->speed; }

};
    
int main() {
    RenderWindow window(VideoMode(800, 600), "Prueba SFML 2.6");
    window.setFramerateLimit(200);

    VertexArray wave(LinesStrip, 800);

    ondas_aleatorias ondas;

    float t = 0.0f;
    Clock clock;
    float change_interval = 3.0f; // cada 3 segundos cambia la onda
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Si pasó el intervalo, cambiamos parámetros
        if (clock.getElapsedTime().asSeconds() > change_interval) {
            ondas.randomize();
            clock.restart();
        }

        for (int x = 0; x < 800; x++) {
            float y = 300 + ondas.get_amp() * sin(2 * M_PI * ondas.get_freq() * (x / 800.0f) + t);
            wave[x].position = Vector2f(x, y);
            wave[x].color = Color::Cyan;
        }

        t += ondas.get_speed();

        window.clear(Color::Black);
        window.draw(wave);
        window.display();
    }

    return 0;
}
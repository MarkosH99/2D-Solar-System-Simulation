#include <SFML/Graphics.hpp>
#include "planet.h"
#include "physics.h"
#include <vector>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "Solar System | Test Run"); //Opens window
    window.setFramerateLimit(60);
    float au_to_px = 100.f;                // 1 AU = 22 pixels (fits Neptune)
    sf::Vector2f cameraAU = {0.f, 0.f};    // camera centered on the Sun
    sf::Vector2f screenCenter = {1280.f, 720.f};  // half of your window size

    auto worldToScreen = [&](sf::Vector2f worldAU) {
        sf::Vector2f p = (worldAU - cameraAU) * au_to_px;
        return sf::Vector2f(screenCenter.x + p.x, screenCenter.y + p.y);
    };

    float G = 4.0f * M_PI * M_PI;
    float softening = 1e-4f;
    const float SECONDS_PER_YEAR = 31557600.0f;
    float timeScale = 604800;    // speeds simulation to 1 week per second
    int substeps = 10;          // improves stability


    auto makePlanet = [&](const std::string& name, double mass, float a, sf::Color color, float visualRadius) {
    float v = std::sqrt(G / a);
    return Planet(name, mass, visualRadius, color, {a, 0.f}, {0.f, v});
};    

Planet sun   ("Sun", 1.0, 20.f, sf::Color(255,215,0), {0.f,0.f}, {0.f,0.f});
Planet mercury = makePlanet("Mercury", 1.66e-7, 0.387f, sf::Color(169,169,169), 6.f);
Planet venus   = makePlanet("Venus",   2.45e-6, 0.723f, sf::Color(255,200,150), 7.f);
Planet earth   = makePlanet("Earth",   3.00e-6, 1.000f, sf::Color(80,140,255),  8.f);
Planet mars    = makePlanet("Mars",    3.23e-7, 1.524f, sf::Color(255,80,80),   7.f);
Planet jupiter = makePlanet("Jupiter", 9.54e-4, 5.204f, sf::Color(200,150,100), 14.f);
Planet saturn  = makePlanet("Saturn",  2.86e-4, 9.582f, sf::Color(210,180,120), 12.f);
Planet uranus  = makePlanet("Uranus",  4.36e-5, 19.18f, sf::Color(147,184,190), 10.f);
Planet neptune = makePlanet("Neptune", 5.15e-5, 30.07f, sf::Color(100,149,237), 10.f);

    std::vector<Planet> bodies{sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune};

    //Game loop
    sf::Clock clock;
    bool paused = false;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
            paused = !paused;
            if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::LBracket) {  // [
                au_to_px *= 0.9f;   // zoom out
            }
            if (e.key.code == sf::Keyboard::RBracket) {  // ]
                au_to_px *= 1.1f;   // zoom in
            }
}

        }
        
        float dtSec = clock.restart().asSeconds();
if (dtSec > 1.0f / 30.0f) dtSec = 1.0f / 30.0f; // avoid jumps on lag frames

float dtYearsTotal = (dtSec * timeScale) / SECONDS_PER_YEAR;
float dtYears = dtYearsTotal / substeps;

if (!paused) {
    for (int s = 0; s < substeps; ++s) {
        Physics::stepNBody(bodies, dtYears, G, softening);
        for (auto& b : bodies) b.update(dtYears);
    }
}



        window.clear(sf::Color(12,14,24));

        std::vector<float> orbitA = {0.387f, 0.723f, 1.0f, 1.524f, 5.204f, 9.582f, 19.18f, 30.07f};
    for (float a : orbitA) {
        sf::CircleShape ring;
        ring.setFillColor(sf::Color::Transparent);
        ring.setOutlineThickness(1.f);                                  //creates outline of orbit trails
        ring.setOutlineColor(sf::Color(255, 255, 255, 50));
        float rpx = a * au_to_px;
        ring.setRadius(rpx);
        ring.setOrigin(rpx, rpx);
        ring.setPosition(screenCenter);
        window.draw(ring);
    }


        for (auto& b : bodies) b.draw(window, au_to_px, screenCenter, cameraAU);
        window.display();


    }
    return 0;
}

#include "planet.h"
#include <cmath>


Planet::Planet(const std::string& name, double mass, float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity)
: name(name), mass(mass), radius(radius), color(color), position(position), velocity(velocity)
{
    //visual shape of the planet
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
}

void Planet::update(float dt) {
    position += velocity * dt;
    shape.setPosition(position);
}

void Planet::draw(sf::RenderWindow& window,
                  float au_to_px,
                  sf::Vector2f screenCenter,
                  sf::Vector2f cameraAU)
{
    sf::Vector2f p = (position - cameraAU) * au_to_px;
    sf::Vector2f screenPos(screenCenter.x + p.x, screenCenter.y + p.y);

    float zoomScale = std::sqrt(std::max(au_to_px, 1.0f) / 120.0f);

    float base = radius * zoomScale;
    float minR = 2.0f, maxR = 16.0f;
    float visualR = std::clamp(base, minR, maxR);

    if (name == "Sun") {
        float sunBoost = 1.4f;
        visualR = std::clamp(base * sunBoost, 3.0f, 18.0f);
    }

    shape.setRadius(visualR);
    shape.setOrigin(visualR, visualR);
    shape.setPosition(screenPos);
    window.draw(shape);
}



void Planet::applyAcceleration(const sf::Vector2f& a, float dt) {
    velocity += a * dt;
}

// ----- Getters -----
sf::Vector2f Planet::getPosition() const { return position; }
sf::Vector2f Planet::getVelocity() const { return velocity; }
double Planet::getMass() const { return mass; }
float Planet::getRadius() const { return radius; }
std::string Planet::getName() const { return name; }
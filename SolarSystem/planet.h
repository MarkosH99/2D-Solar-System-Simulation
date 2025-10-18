#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Planet {
    private:
        double mass;
        sf::Vector2f position;
        sf::Vector2f velocity;
        float radius;
        sf::Color color;
        std::string name;
        sf::CircleShape shape;
    public:
        Planet(const std::string& name, double mass, float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity);

        void update(float dt);   //move planet
        void draw(sf::RenderWindow& window, float au_to_px, sf::Vector2f screenCenter, sf::Vector2f cameraAU);
        void applyAcceleration(const sf::Vector2f& a, float dt);

        //Getters
        sf::Vector2f getPosition() const;
        sf::Vector2f getVelocity() const;
        double getMass() const;
        float getRadius() const;
        std::string getName() const;

};
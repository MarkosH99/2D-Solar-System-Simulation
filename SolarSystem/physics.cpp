#include "physics.h"
#include "planet.h"
#include <SFML/System.hpp>
#include <cmath>
#include <vector>

namespace Physics {
    void stepNBody(std::vector<Planet>& bodies, float dt, float G, float softening) {
        const std::size_t n = bodies.size();
        std::vector<sf::Vector2f> acc(n, {0.f, 0.f});

        //1) compute accelerations from pairwise gravity
        for(std::size_t i = 0; i < n; i++) {
            const auto pi = bodies[i].getPosition();
            for(std::size_t j = 0; j < n; j++) {
                if (i == j) continue;
                const auto r = bodies[j].getPosition() - pi;
                const float d2 = r.x*r.x + r.y*r.y + softening*softening;
                const float invD = 1.0f / std::sqrt(d2);
                const float invD3 = invD * invD * invD;
                acc[i] += (G * static_cast<float>(bodies[j].getMass())) * r * invD3;
            }
        }

        for (std::size_t i = 0; i < bodies.size(); i++) {
    bodies[i].applyAcceleration(acc[i], dt);   // v_i += a_i * dt
}
    }
}
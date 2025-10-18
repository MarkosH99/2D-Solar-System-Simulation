#pragma once
#include <vector>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Planet;

namespace Physics {
    void stepNBody(std::vector<Planet>& bodies,
        float dt,
        float G = 1200.0f,      // gravitational strength
        float softening = 25.0f //avoids singularities
    );
}


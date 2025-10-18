# C++ 2D Solar System Simulation

A 2D n-body gravity simulation built with SFML, modeling the orbits of the 8 planets around the Sun using astronomical units (AU), years, and solar masses.

## Overview

This project simulates the Solar System in a 2D plane using Newton’s Law of Universal Gravitation.  
Planets move according to realistic orbital mechanics, with circular starting velocities and adjustable time scaling.  
Zoom and pan controls let you explore from Mercury to Neptune.

## Features

- Realistic n-body gravity with G = 4π² (AU³ / Msun·yr²)  
- All 8 planets (Mercury → Neptune)    
- Pause (Space)  
- Zoom in/out ([ ])  
- Scaled rendering: positions in AU → screen pixels  
- orbit rings  

## Physics Model

Newton’s law in vector form:

a_i = G Σ m_j (r_j - r_i) / |r_j - r_i|³

Integration (semi-implicit Euler):

v_i += a_i * dt  
x_i += v_i * dt

### Units
| Quantity | Unit |
|-----------|------|
| Distance | AU |
| Mass | Solar masses |
| Time | Years |

## Project Structure

```
SolarSystem/
 ┣━ main.cpp          → main loop, planet setup, events, drawing
 ┣━ planet.h / planet.cpp → Planet class (mass, position, velocity, draw)
 ┣━ physics.h / physics.cpp → Physics namespace (pairwise gravity)
```

## Controls

| Key | Action |
|-----|--------|
| [ / ] | Zoom out / in |
| Space | Pause simulation |
| Esc | Exit |

## Planet Initialization

Each planet starts at (a, 0) AU with circular velocity (0, √(G/a)).

Example:

```
Planet earth("Earth", 3.00e-6, 8.f, sf::Color(80,140,255),
             {1.0f, 0.f}, {0.f, std::sqrt(G / 1.0f)});
```

## Building & Running

### Dependencies
- SFML 2.6+
- C++17 or later

### Build (MSYS2 / GCC example)
```
g++ main.cpp planet.cpp physics.cpp -lsfml-graphics -lsfml-window -lsfml-system -o SolarSystem
./SolarSystem
```

### VS Code (Windows)
Press Ctrl + Shift + B to build and F5 to run.

## Tips

- Lower timeScale for slower orbits.
- Raise substeps for more stable motion.
- Use au_to_px ≈ 22 for full-system view; ~200 for inner planets.
- Planet radii are exaggerated for visibility.

## Future Ideas
- Add Pluto or moons    
- Add text labels (SFML Text) for planet names  
- Add energy or momentum readouts  
- Elliptical orbits
## License
MIT License — free to use and modify.

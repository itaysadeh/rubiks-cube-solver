#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"

#include "../Cube/cube.h"
#include "../Util/searchutil.h"
#include "../Util/randomnumgenerator.h"
#include "../Solver/Thistlethwaite/thistlethwaite.h"

#include <iostream>
#include <cstdint>
#include <string>

// renders the cube and handles user input
class Engine
{
public:
    Engine();

    void run();

private:
    // engine logic
    void init();
    void mainLoop();
    void pollEvents();

    void update();
    void render();

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_exit = false;

    SDL_Color m_colours[6];
    enum { W, O, G, R, B, Y };

    const uint32_t FPS = 60;
    const uint32_t FRAME_DELAY = 1000 / FPS;

    void renderFacelet(size_t ind);
    void setFaceletPos(size_t ind, int x, int y);

    // cube logic
    Rubiks m_cube;

    SDL_Rect m_facelets[48];
    SDL_Rect m_centreFacelets[6];
    uint8_t  m_faceletsColour[48];

    void scramble(size_t movesAmount);

    Thistlethwaite m_thistlethwaite;
};

#endif // ENGINE_H

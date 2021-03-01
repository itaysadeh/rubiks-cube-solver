#pragma once

#include "SDL.h"

#include "../Cube.h"
#include "../Util/MovesSimplifier.h"
#include "../Solver/Thistlethwaite/Thistlethwaite.h"

#include <iostream>
#include <cstdint>

class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
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

    const size_t FPS = 60;
    const size_t FRAME_DELAY = 1000 / FPS;

    void renderFacelet(size_t ind);
    void setFaceletPos(size_t ind, size_t x, size_t y);

    // cube logic
    Rubiks m_cube;

    SDL_Rect m_facelets[48];
    SDL_Rect m_centreFacelets[6];
    uint8_t  m_faceletsColour[48];

    void scramble(size_t movesAmount);

    Thistlethwaite m_thistlethwaite;
};
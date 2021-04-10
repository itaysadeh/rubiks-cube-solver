#include "engine.h"

Engine::Engine()
{
    init();
}

void Engine::run()
{
    mainLoop();
}

void Engine::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    
    // centre facelets
    for (size_t i = 0; i < 6; ++i)
    {
        SDL_SetRenderDrawColor(m_renderer, m_colours[i].r, m_colours[i].g, m_colours[i].b, 255);
        SDL_RenderFillRect(m_renderer, &m_centreFacelets[i]);
    }
    // all facelets
    for (size_t i = 0; i < 48; ++i)
    {
        renderFacelet(i);
    }

    SDL_RenderPresent(m_renderer);
}

void Engine::renderFacelet(size_t ind)
{
    uint8_t r = m_colours[m_faceletsColour[ind]].r;
    uint8_t g = m_colours[m_faceletsColour[ind]].g;
    uint8_t b = m_colours[m_faceletsColour[ind]].b;
    SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
    SDL_RenderFillRect(m_renderer, &m_facelets[ind]);
}

void Engine::update()
{
    // updates current cube state
    for (size_t i = 0; i < 48; ++i)
    {
        m_faceletsColour[i] = (uint8_t)m_cube.getColour(i);
    }
}

void Engine::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    m_window   = SDL_CreateWindow  ("Rubiks Cube Solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    constexpr int faceletSize = 55;

    for (size_t i = 0; i < 48; ++i)
    {
        m_facelets[i].h = faceletSize;
        m_facelets[i].w = faceletSize;
    }

    for (size_t i = 0; i < 6; ++i)
    {
        m_centreFacelets[i].h = faceletSize;
        m_centreFacelets[i].w = faceletSize;
    }

    // init colours
    m_colours[W] = { 255, 255, 255, 255};
    m_colours[O] = { 255, 120, 0, 255};
    m_colours[G] = { 0, 255, 0, 255 };
    m_colours[R] = { 255, 0, 0, 255 };
    m_colours[B] = { 0, 0, 255, 255 };
    m_colours[Y] = { 255, 255, 0, 255 };

    // init facelet positions on screen
    auto setFace = [&](size_t ind, int x_offset, int y_offset) {
        setFaceletPos(ind * 8 + 0, x_offset + faceletSize * 0, y_offset + faceletSize * 0);
        setFaceletPos(ind * 8 + 1, x_offset + faceletSize * 1, y_offset + faceletSize * 0);
        setFaceletPos(ind * 8 + 2, x_offset + faceletSize * 2, y_offset + faceletSize * 0);
        setFaceletPos(ind * 8 + 3, x_offset + faceletSize * 2, y_offset + faceletSize * 1);
        setFaceletPos(ind * 8 + 4, x_offset + faceletSize * 2, y_offset + faceletSize * 2);
        setFaceletPos(ind * 8 + 5, x_offset + faceletSize * 1, y_offset + faceletSize * 2);
        setFaceletPos(ind * 8 + 6, x_offset + faceletSize * 0, y_offset + faceletSize * 2);
        setFaceletPos(ind * 8 + 7, x_offset + faceletSize * 0, y_offset + faceletSize * 1);
    };

    setFace(W, faceletSize * 4, faceletSize * 1);
    setFace(O, faceletSize * 1, faceletSize * 4);
    setFace(G, faceletSize * 4, faceletSize * 4);
    setFace(R, faceletSize * 7, faceletSize * 4);
    setFace(B, faceletSize * 10, faceletSize * 4);
    setFace(Y, faceletSize * 4, faceletSize * 7);

    m_centreFacelets[W].x = faceletSize * 5;
    m_centreFacelets[W].y = faceletSize * 2;

    m_centreFacelets[O].x = faceletSize * 2;
    m_centreFacelets[O].y = faceletSize * 5;

    m_centreFacelets[G].x = faceletSize * 5;
    m_centreFacelets[G].y = faceletSize * 5;

    m_centreFacelets[R].x = faceletSize * 8;
    m_centreFacelets[R].y = faceletSize * 5;

    m_centreFacelets[B].x = faceletSize * 11;
    m_centreFacelets[B].y = faceletSize * 5;

    m_centreFacelets[Y].x = faceletSize * 5;
    m_centreFacelets[Y].y = faceletSize * 8;
}

void Engine::setFaceletPos(size_t ind, int x, int y)
{
    m_facelets[ind].x = x;
    m_facelets[ind].y = y;
}

void Engine::mainLoop()
{
    while (!m_exit)
    {
        uint32_t frameStart = SDL_GetTicks();

        pollEvents();
        update();
        render();
        
        uint32_t elapsedTime = SDL_GetTicks() - frameStart;

        if (FRAME_DELAY > elapsedTime)
        {
            SDL_Delay(FRAME_DELAY - elapsedTime);
        }
    }
}

void Engine::scramble(size_t movesAmount)
{
    using EMOVE = Rubiks::EMOVE;

    SearchUtil         searchUtil;
    RandomNumGenerator generator(1, 18);

    size_t movesPerformed = 0;

    EMOVE last = EMOVE::NO_MOVE;
    EMOVE curr = EMOVE::NO_MOVE;

    std::cout << "Scrambled with:" << std::endl;

    while (movesPerformed <= movesAmount)
    {

        curr = (EMOVE)generator.getNum();
        if (!searchUtil.isRedundant(curr, last))
        {
            m_cube.performMove(curr);
            if (movesPerformed == movesAmount / 2) std::cout << std::endl;
            std::cout << m_cube.getMoveName(curr);

            last = curr;
            movesPerformed++;
        }
    }
    std::cout << std::endl;
}

void Engine::pollEvents()
{
    SDL_Event ev;
    // user input
    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            // Quit
            m_exit = true;
            break;
        case SDL_KEYDOWN:
            // Keyboard
            uint8_t* keyState = (uint8_t*)SDL_GetKeyboardState(NULL);
            // R
            if (ev.key.keysym.sym == SDLK_r)
            {
                if (keyState[SDL_SCANCODE_LSHIFT])
                    m_cube.Rp();
                else if (keyState[SDL_SCANCODE_LCTRL])
                    m_cube.R2();
                else
                    m_cube.R();
            }
            // U
            if (ev.key.keysym.sym == SDLK_u)
            {
                if (keyState[SDL_SCANCODE_LSHIFT])
                    m_cube.Up();
                else if (keyState[SDL_SCANCODE_LCTRL])
                    m_cube.U2();
                else
                    m_cube.U();
            }
            // L
            if (ev.key.keysym.sym == SDLK_l)
            {
                if (keyState[SDL_SCANCODE_LSHIFT])
                    m_cube.Lp();
                else if (keyState[SDL_SCANCODE_LCTRL])
                    m_cube.L2();
                else
                    m_cube.L();
            }
            // F
            if (ev.key.keysym.sym == SDLK_f)
            {
                if (keyState[SDL_SCANCODE_LSHIFT])
                    m_cube.Fp();
                else if (keyState[SDL_SCANCODE_LCTRL])
                    m_cube.F2();
                else
                    m_cube.F();
            }
            // B
            if (ev.key.keysym.sym == SDLK_b)
            {
                if (keyState[SDL_SCANCODE_LSHIFT])
                    m_cube.Bp();
                else if (keyState[SDL_SCANCODE_LCTRL])
                    m_cube.B2();
                else
                    m_cube.B();
            }
            // D
            if (ev.key.keysym.sym == SDLK_d)
            {
                if (keyState[SDL_SCANCODE_LSHIFT])
                    m_cube.Dp();
                else if (keyState[SDL_SCANCODE_LCTRL])
                    m_cube.D2();
                else
                    m_cube.D();
            }
            // scramble
            if (ev.key.keysym.sym == SDLK_s)
            {
                scramble(50);
            }
            // reset
            if (ev.key.keysym.sym == SDLK_ESCAPE)
            {
                m_cube.resetCube();
            }
            // solve thistlethwaite
            if (ev.key.keysym.sym == SDLK_F1)
            {
                std::vector<Rubiks::EMOVE> result = m_thistlethwaite.solve(m_cube);
                for (const auto& move : result)
                {
                    m_cube.performMove(move);
                }
            }

            break;
        }
    }
}

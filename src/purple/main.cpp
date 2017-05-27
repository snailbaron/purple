#define SDL_MAIN_HANDLED

#include <iostream>
#include <exception>
#include <sdl.hpp>


int main()
{
    try {

    //sdl::init(SDL_INIT_VIDEO);

    auto window = sdl::createWindow("Test", 100, 100, 800, 600, 0);
    auto renderer = window->createRenderer(
        -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    window.reset();

    bool done = false;
    while (!done) {
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                done = true;
            }
        }

        renderer->setDrawColor(100, 100, 100, 255);
        renderer->clear();

        renderer->setDrawColor(0, 255, 0, 255);
        SDL_Rect rect { 100, 100, 200, 100 };
        renderer->fillRect(rect);

        renderer->present();

    }

    sdl::quit();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
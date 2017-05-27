#define SDL_MAIN_HANDLED

#include <iostream>
#include <exception>
#include <sdl_wrapper.hpp>

int main()
{
    try {
        sdl::init();

        auto window = sdl::createWindow("Test", 100, 100, 800, 600, 0);
        auto renderer = window->createRenderer(
            -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        auto testSurface = img::load("../../assets/test.png");
        auto size = testSurface->size();
        auto testTexture = renderer->createTextureFromSurface(testSurface);

        auto testFont = ttf::openFont("../../assets/fonts/fyodor/truetype/Fyodor-Bold.ttf", 25);
        auto textBitmap = testFont->renderUtf8Blended("Hello! Привет!", SDL_Color{0, 200, 200, 255});
        auto textSize = textBitmap->size();
        auto text = renderer->createTextureFromSurface(textBitmap);

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

            renderer->copy(
                testTexture,
                SDL_Rect{0, 0, size.w, size.h},
                SDL_Rect{120, 250, size.w, size.h});

            renderer->copy(
                text,
                SDL_Rect{0, 0, textSize.w, textSize.h},
                SDL_Rect{300, 240, textSize.w, textSize.h});

            renderer->present();

        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    sdl::quit();
    return 0;
}
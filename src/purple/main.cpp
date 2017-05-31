#include "core/core.hpp"
#include "view/player_view.hpp"
#include "view/log_view.hpp"
#include "game_timer.hpp"
#include "core/actor.hpp"

#include <sdl_wrapper.hpp>

#include <iostream>
#include <exception>
#include <memory>

const int GAME_FPS = 60;
const double GAME_SPF = 1.0 / GAME_FPS;

int main(int argc, char** argv)
{
    try {
        Core core;
        
        std::shared_ptr<PlayerView> view(new PlayerView());
        view->loadResources();
        core.attach(view);

        std::shared_ptr<View> logView(new LogView());
        core.attach(logView);

        auto camera = std::make_shared<Actor>();
        camera->name("camera");
        camera->emplaceComponent<ComponentType::Camera>();
        camera->emplaceComponent<ComponentType::Position>(WorldPoint(0, 0));
        core.spawn(camera);

        auto tree = std::make_shared<Actor>();
        tree->name("tree");
        tree->emplaceComponent<ComponentType::Position>(WorldPoint(0, 0));
        tree->emplaceComponent<ComponentType::Graphics>("bitmaps/tree.png");
        core.spawn(tree);

        auto girl = std::make_shared<Actor>();
        girl->name("girl");
        girl->emplaceComponent<ComponentType::Position>(WorldPoint(-2.0, 3.5));
        girl->emplaceComponent<ComponentType::Graphics>("animations/girl2.png");
        core.spawn(girl);

        bool done = false;
        GameTimer timer;
        while (!done) {
            SDL_Event evt;
            while (SDL_PollEvent(&evt)) {
                switch (evt.type) {
                    case SDL_QUIT:
                        done = true;
                        break;
                }
            }

            if (timer.advance(GAME_SPF)) {
                core.update(GAME_SPF);
                view->render();
            }
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
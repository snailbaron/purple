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

        core.loadTestLevel();

        bool done = false;
        GameTimer timer;
        while (!done) {
            if (!view->processInput()) {
                done = true;
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
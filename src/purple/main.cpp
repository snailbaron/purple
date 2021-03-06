#include "core/core.hpp"
#include "view/player_view.hpp"
#include "view/log_view.hpp"
#include "game_timer.hpp"
#include "core/actor.hpp"
#include <purple/input/input.hpp>
#include <purple/events.hpp>

#include <iostream>
#include <exception>
#include <memory>

const int GAME_FPS = 60;
const double GAME_SPF = 1.0 / GAME_FPS;

// Temporary solution. QuitEvent should be captured by the entity controlling
// game states, and initiate transition to some "Quit Game" state.
class GameEnder : public Listener<input::QuitEvent> {
public:
    bool timeToQuit() const { return _quit; }

private:
    void listen(const input::QuitEvent&)
    {
        _quit = true;
    }

    bool _quit = false;
};

int main(int argc, char** argv)
{
    try {
        Core core;

        std::shared_ptr<PlayerView> view(new PlayerView());
        view->loadResources();
        core.attach(view);

        std::shared_ptr<View> logView(new LogView());
        core.attach(logView);

        input::InputManager inputManager;
        view->subscribeToInput(inputManager);

        GameEnder ender;
        inputManager.subscribe<input::QuitEvent>(&ender);

        core.loadTestLevel();

        bool done = false;
        GameTimer timer;
        while (!ender.timeToQuit()) {
            inputManager.processInput();

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
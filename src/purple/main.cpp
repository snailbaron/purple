#include "core/game.hpp"
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
        Game core;
        input::InputManager inputManager;

        std::shared_ptr<Terminal> view(new Terminal());
        view->loadResources();
        view->attachTo(core);
        view->subscribeToInput(inputManager);

        std::shared_ptr<View> logView(new LogView());
        core.attach(logView);


        GameEnder ender;
        inputManager.subscribe<input::QuitEvent>(&ender);



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
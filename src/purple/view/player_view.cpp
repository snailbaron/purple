#include "player_view.hpp"

namespace {

Color BACKGROUND_COLOR { 100, 100, 100 };

}

PlayerView::PlayerView()
    : _canvas()
{
}

void PlayerView::update(double deltaSec)
{
}

void PlayerView::render()
{
    _canvas.clear(BACKGROUND_COLOR);
    _canvas.present();
}
#pragma once

#include "view.hpp"
#include "canvas.hpp"

class PlayerView : public View {
public:
    PlayerView();

    void update(double deltaSec) override;
    void render() override;

private:
    Canvas _canvas;
};
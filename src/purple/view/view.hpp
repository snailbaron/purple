#pragma once

class View {
public:
    virtual void update(double deltaSec) = 0;
    virtual void render() = 0;
};
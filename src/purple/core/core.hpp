#pragma once

#include "../view/view.hpp"
#include <vector>
#include <memory>
#include <functional>

class Core {
public:
    void attach(std::shared_ptr<View> view);
    void update(double deltaSec);


private:
    void forActiveViews(std::function<void(std::shared_ptr<View>)> action);

    std::vector<std::weak_ptr<View>> _views;
};
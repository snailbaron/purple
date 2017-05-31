#pragma once

#include "canvas.hpp"
#include <utils/variation.hpp>
#include <sdl_wrapper.hpp>
#include <map>
#include <string>
#include <memory>

enum class ResourceType {
    Bitmap,
    Animation,
};

IMPLEMENT_VARIATION(Resource, ResourceType)

//using NAME = Variation<ResourceType>;
//
//template <ResourceType ProvidedResourceType>
//    using ResourceOf =
//        typename VariationOf<ResourceType, ProvidedResourceType>;

#define RESOURCE(NAME) NEW_VARIATION(NAME ## Resource, ResourceType, ResourceType:: NAME)

RESOURCE(Bitmap) {
    BitmapResource(std::shared_ptr<sdl::Texture> texture, int width, int height)
        : texture(texture), width(width), height(height) {}

    std::shared_ptr<sdl::Texture> texture;
    int width;
    int height;
};

RESOURCE(Animation) {
    AnimationResource(
            std::shared_ptr<sdl::Texture> texture,
            int frameWidth,
            int frameHeight,
            int frameCount)
        : texture(texture)
        , frameWidth(frameWidth)
        , frameHeight(frameHeight)
        , frameCount(frameCount)
    { }

    std::shared_ptr<sdl::Texture> texture;
    int frameWidth;
    int frameHeight;
    int frameCount;
};

class ResourceStorage {
public:
    void loadGraphics(const Canvas& canvas, const std::string& location);
    void loadTestLevel();

    std::shared_ptr<Resource> graphics(const std::string& key) const;

private:
    std::shared_ptr<BitmapResource> loadBitmapResource(
        const Canvas& canvas, const std::string& path);
    std::shared_ptr<AnimationResource> loadAnimationResource(
        const Canvas& canvas, const std::string& path);

    std::map<std::string, std::shared_ptr<Resource>> _graphicalResources;
};
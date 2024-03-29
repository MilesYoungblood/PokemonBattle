//
// Created by Miles Youngblood on 12/5/2023.
//

#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() {
    this->graphics[typeid(Animation).hash_code()];
    this->graphics[typeid(Button).hash_code()];
    this->graphics[typeid(Panel).hash_code()];
    this->graphics[typeid(Rectangle).hash_code()];
    this->graphics[typeid(ResourceBar).hash_code()];
    this->graphics[typeid(SelectionBox).hash_code()];
    this->graphics[typeid(TextBox).hash_code()];
    this->graphics[typeid(Texture).hash_code()];
    this->graphics[typeid(TimedVisual).hash_code()];
}

void GraphicsEngine::update() {
    for (const auto &type : this->graphics) {
        std::vector<std::unique_ptr<Graphic>> &ref = this->graphics.at(type.first);
        for (long long i = 0; i < ref.size(); ++i) {
            if (ref.at(i)->isActive()) {
                ref.at(i)->update();
            }
            else {
                ref.erase(ref.cbegin() + i);
            }
        }
    }
}

void GraphicsEngine::render() {
    for (const auto &type : this->graphics) {
        for (const auto &graphic : type.second) {
            graphic->render();
        }
    }
}

void GraphicsEngine::clear() {
    for (auto &type : this->graphics) {
        type.second.clear();
    }
}

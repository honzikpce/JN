//
// Created by Honzik on 10.03.17.
//

#include "Shape.h"


namespace JN {

    Rect::Rect(glm::vec2 dims) {
        _dimensions = dims;
    }

    bool Rect::containsPoint(const glm::vec2 &point) {
        return (point.x >= _position.x &&
                point.x <= _position.x + _dimensions.x &&
                point.y >= _position.y &&
                point.y <= _position.y + _dimensions.y);
    }

    ///> defaults to no angle, red color
    void Rect::draw(DebugRenderer &renderer, float angle, Color color) {
        renderer.drawRectangle(glm::vec4(_position, _dimensions), angle, color);
    }


}
//
// Created by Honzik on 10.03.17.
//

#ifndef JN_SHAPE_H
#define JN_SHAPE_H


#include <glm/vec2.hpp>
#include "DebugRenderer.hpp"

namespace JN {

    class Shape {

        ///< Shape has the position always at left, bottom


    public:
        Shape() { /* empty */ };
        virtual ~Shape() { /* empty */ };

        virtual float getWidth() { return _dimensions.x; }
        virtual float getHeight() { return _dimensions.y; }
        virtual float getLeft() { return _position.x; }
        virtual float getRight() { return _position.x + _dimensions.x; }
        virtual float getTop() { return _position.y + _dimensions.y; }
        virtual float getBottom() { return _position.y; }

        void setPosition(glm::vec2 position) { _position = position; }

        // pure virtuals!
        virtual bool containsPoint(const glm::vec2 &point) = 0;
        virtual void draw(DebugRenderer &renderer, float angle, Color color) = 0;


    protected:
        glm::vec2 _position = glm::vec2();
        glm::vec2 _dimensions = glm::vec2();
    };


    class Rect : public Shape {
    public :
        Rect(glm::vec2 dims);

        bool containsPoint(const glm::vec2 &point) override;

        void draw(DebugRenderer &renderer, float angle=0.0f, Color color = {255, 0, 0, 255}) override;
    };


}


#endif //JN_SHAPE_H

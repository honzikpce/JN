//
// Created by Honzik on 12.01.17.
//

#ifndef DNAPLANTS_COLLECTABLEITEMS_H
#define DNAPLANTS_COLLECTABLEITEMS_H


#include <glm/vec2.hpp>
#include "SpriteBatch.hpp"
#include "ControlManager.hpp"
#include <boost/signals2/signal.hpp>
#include "Shape.h"

namespace JN {


enum class OriginX {
    left, center, right
};

enum class OriginY {
    bottom, center, top
};
class GameObject {

    typedef boost::signals2::signal<void (void *)> MouseEvent;

public:

    typedef MouseEvent::slot_type MouseEventSlotType;

    // sets the handlers for events
    boost::signals2::connection doOnClick(const MouseEventSlotType &slot);
    boost::signals2::connection doOnMouseOver(const MouseEventSlotType &slot);
    boost::signals2::connection doOnMouseOut(const MouseEventSlotType &slot);
    boost::signals2::connection doOnMouseDrop(const MouseEventSlotType &slot);

    GameObject();

    ///> sets position of the object and takes care of custom origin points
    virtual void setPosition(glm::vec2 position, OriginX originX = OriginX::center, OriginY originY = OriginY::bottom);
    glm::vec2 getPosition() { return m_position; }
    void update(JN::ControlManager & controlManager, JN::Camera2D &camera);
    virtual void draw(JN::SpriteBatch &spriteBatch);
    virtual ~GameObject();
    bool isFinished() { return m_isFinished; }
    bool isContainPoint(const glm::vec2 &point);
    void setCollisionBox(Shape * collisionBox) { m_collisionBox = collisionBox; }

protected:
    // pure virtuals
    virtual void doOnUpdate(JN::ControlManager & controlManager, JN::Camera2D &camera) = 0;

    // LAYOUT
    glm::vec2 m_position;
    glm::vec2 m_relativePosition = glm::vec2();
    glm::vec2 m_dims = glm::vec2();
    Shape * m_collisionBox = nullptr;

    // MOVEMENT
    glm::vec2 m_direction = glm::vec2();
    float m_speed = 0.0f;

    // EVENTS
    // must be a pointer cause boost::signal2 uses copy deleted constructor
    MouseEvent * m_onclick = nullptr;
    MouseEvent * m_onMouseOver= nullptr;
    MouseEvent * m_onMouseOut= nullptr;
    MouseEvent * m_onMouseDrop= nullptr;

    bool m_isMouseOver = false;
    bool m_isDragged = false;
    bool m_isDraggable = false;


    // APPEARANCE
    bool m_invertedTexture = false;
    JN::Color m_color = JN::Color();
    GLuint m_texture = 0;

    // STATES
    bool m_isFinished = false;

};

}
#endif //DNAPLANTS_COLLECTABLEITEMS_H

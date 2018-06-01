//
// Created by Honzik on 12.01.17.
//

#include "GameObject.h"

namespace JN {

    GameObject::GameObject()
{
    m_onclick = new MouseEvent();
    m_onMouseOver = new MouseEvent();
    m_onMouseOut = new MouseEvent();
    m_onMouseDrop = new MouseEvent();
}

void GameObject::setPosition(glm::vec2 position,
                             OriginX originX /* = OriginX::center*/,
                             OriginY originY /* = OriginY::bottom */) {
    m_position = position + glm::vec2(-(float)originX * m_dims.x / 2.0f, (float)originY * m_dims.y);
}

void GameObject::draw(JN::SpriteBatch &spriteBatch) {
    if (m_invertedTexture) {
        spriteBatch.draw(glm::vec4(m_relativePosition + m_position, m_dims),
                         glm::vec4(0.0f, 0.0f, -1.0f, 1.0f), m_texture, 1.0f, m_color);
    }
    else {
        spriteBatch.draw(glm::vec4(m_relativePosition + m_position, m_dims),
                         glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture, 1.0f, m_color);
    }
}

GameObject::~GameObject() {

    m_onclick->disconnect_all_slots();
    m_onMouseOver->disconnect_all_slots();
    m_onMouseOut->disconnect_all_slots();
    m_onMouseDrop->disconnect_all_slots();
}

void GameObject::update(JN::ControlManager &controlManager, JN::Camera2D &camera) {
// PROCESS INPUTS AND EVENTS
    glm::vec2 mouseCoords = camera.convertScreenToWorld(controlManager.getMouseCoords());
    bool isMouseOverNow = isContainPoint(mouseCoords);
    // is clicked inside flower box
    if (controlManager.isMouseClicked() && isMouseOverNow) {
        (*m_onclick)(this);
    }

    // mouse over event
    if (isMouseOverNow && !m_isMouseOver) {
        m_isMouseOver = true;
        (*m_onMouseOver)(this);
    }

    // mouse out event
    if (m_isMouseOver && !isMouseOverNow) {
        m_isMouseOver = false;
        (*m_onMouseOut)(this);
    }

    if (m_isDraggable) {
        // mouse dragging
        if (controlManager.isMouseDragged() &&
            isContainPoint(camera.convertScreenToWorld(controlManager.getMouseCoords()))) {
            m_isDragged = true;
        }

        // drop event
        if (m_isDragged && controlManager.isDragFinished()) {
            m_isDragged = false;
            (*m_onMouseDrop)(this);
        }
        // set position when dragged
        if (m_isDragged) {
            setPosition(
                    camera.convertScreenToWorld(controlManager.getMouseCoords()) - glm::vec2(0.0f, m_dims.y / 2.0f));
        }
    }

    doOnUpdate(controlManager, camera); ///< calls child's update
}


boost::signals2::connection GameObject::doOnClick(const GameObject::MouseEventSlotType &slot) {
    return m_onclick->connect(slot);
}

boost::signals2::connection GameObject::doOnMouseOver(const GameObject::MouseEventSlotType &slot) {
    return m_onMouseOver->connect(slot);
}

boost::signals2::connection GameObject::doOnMouseOut(const GameObject::MouseEventSlotType &slot) {
    return m_onMouseOut->connect(slot);
}

boost::signals2::connection GameObject::doOnMouseDrop(const GameObject::MouseEventSlotType &slot) {
    m_isDraggable = true;
    return m_onMouseDrop->connect(slot);
}


bool GameObject::isContainPoint(const glm::vec2 &point){
    return (m_collisionBox != nullptr && m_collisionBox->containsPoint(point));
}



}


#ifndef CHECKABLEBUTTON_HPP
#define CHECKABLEBUTTON_HPP

#include "autorobot.hpp"
#include "gameobject.hpp"
#include "obstacle.hpp"
#include "overlaywidget.hpp"
#include <QPushButton>

class CheckableButton : public QPushButton {
  public:
    enum ObjectType {
        AUTO,
        CONT,
        OBST
    };

    OverlayWidget *overlay;

    explicit CheckableButton(const QString &text, QWidget *parent = nullptr, ObjectType type = ObjectType::OBST)
        : QPushButton(text, parent), objType(type) {
        setCheckable(true);
        setMouseTracking(true); // Enable mouse tracking
    }

  protected:
    bool isPressed = false;
    ObjectType objType;

    QPoint getWidgetPos(QPoint localPos) {
        QPoint pos = mapToGlobal(localPos);
        return overlay->mapFromGlobal(pos);
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (!isChecked()) {
            setChecked(true);

            switch (objType) {
            case AUTO: {
                auto autorobutek = new AutoRobot();
                overlay->activeObject = autorobutek;
            } break;
            case CONT: {
                auto robutek = new Robot();
                overlay->activeObject = robutek;
                break;
            }
            case OBST: {
                auto obstacle = new Obstacle();
                overlay->activeObject = obstacle;
                break;
            }
            default:
                throw "Unknow object";
                break;
            }
            overlay->lastMousePos = getWidgetPos(event->pos());
        }
        QPushButton::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        event->ignore();
        if (isChecked()) {
            // overlay->lastMousePos = getWidgetPos(event->pos());
        }
        QPushButton::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        QPushButton::mouseReleaseEvent(event);
        setChecked(false);
        event->ignore();
        // overlay->anchor();
    }
};

#endif // CHECKABLEBUTTON_HPP
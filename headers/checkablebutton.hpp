

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
        // setAutoExclusive(false);
        setCheckable(true);
        setMouseTracking(true); // Enable mouse tracking
    }

  protected:
    bool isPressed = false;
    ObjectType objType;

    void mousePressEvent(QMouseEvent *event) override {
        if (!isChecked()) {
            setChecked(true);
            qDebug() << "Mouse Press Event in CheckableButton";

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
        }
        QPushButton::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (isChecked()) {
            qDebug() << "Mouse Move Event in CheckableButton";
            overlay->lastMousePos = event->pos();
        }
        QPushButton::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        QPushButton::mouseReleaseEvent(event);
        qDebug() << "Mouse Release Event in CheckableButton";
        setChecked(false);
        overlay->anchorObject();
        overlay->lastMousePos = QPoint(0, 0);
    }
};

#endif // CHECKABLEBUTTON_HPP
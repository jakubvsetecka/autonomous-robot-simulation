#include "checkablebutton.hpp"

CheckableButton::CheckableButton(const QString &text, QWidget *parent, ObjectType type)
    : QPushButton(text, parent), objType(type) {
    setCheckable(true);
    setMouseTracking(true); // Enable mouse tracking
}

QPoint CheckableButton::getWidgetPos(QPoint localPos) {
    QPoint pos = mapToGlobal(localPos);
    return overlay->mapFromGlobal(pos);
}

void CheckableButton::mousePressEvent(QMouseEvent *event) {
    if (!isChecked()) {
        setChecked(true);

        switch (objType) {
        case AUTO: {
            auto autorobutek = new AutoRobot(nullptr, 50, 10, Robot::RotationDirection::Right, 1, 1, overlay->simEng->getTimeConstant());
            overlay->activeObject = autorobutek;
        } break;
        case CONT: {
            auto robutek = new Robot(nullptr, overlay->simEng->getTimeConstant());
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

void CheckableButton::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
    if (isChecked()) {
        // overlay->lastMousePos = getWidgetPos(event->pos());
    }
    QPushButton::mouseMoveEvent(event);
}

void CheckableButton::mouseReleaseEvent(QMouseEvent *event) {
    QPushButton::mouseReleaseEvent(event);
    setChecked(false);
    event->ignore();
    // overlay->anchor();
}
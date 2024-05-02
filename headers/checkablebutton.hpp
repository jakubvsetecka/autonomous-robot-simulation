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

    explicit CheckableButton(const QString &text, QWidget *parent = nullptr, ObjectType type = ObjectType::OBST);
    OverlayWidget *getOverlay() const { return overlay; }
    void setOverlay(OverlayWidget *overlay) { this->overlay = overlay; }

  protected:
    OverlayWidget *overlay;
    bool isPressed = false;
    ObjectType objType;

    QPoint getWidgetPos(QPoint localPos);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CHECKABLEBUTTON_HPP
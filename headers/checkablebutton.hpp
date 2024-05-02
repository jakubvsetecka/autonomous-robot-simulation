/**
 * @file checkablebutton.hpp
 * @brief This file contains the declaration of the CheckableButton class.
 * @details It is a subclass of the QPushButton class and represents a checkable button.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#ifndef CHECKABLEBUTTON_HPP
#define CHECKABLEBUTTON_HPP

#include "autorobot.hpp"
#include "gameobject.hpp"
#include "obstacle.hpp"
#include "overlaywidget.hpp"
#include <QPushButton>

/**
 * @class CheckableButton
 * @brief A class to represent a checkable button.
 * @details This class inherits from QPushButton and provides functionalities for a button that can be checked and unchecked. It also has an OverlayWidget that is used to draw the object on the grid.
 * @see QPushButton
 */
class CheckableButton : public QPushButton {
  public:
    /** * @brief Enum to represent the type of object that the button represents
     * AUTO: AutoRobot
     * CONT: ControlledRobot
     * OBST: Obstacle
     */
    enum ObjectType {
        AUTO,
        CONT,
        OBST
    };

    /**
     * @brief Constructor for CheckableButton.
     * @param text The text to be displayed on the button.
     * @param parent The parent QWidget.
     * @param type The type of object that the button represents.
     */
    explicit CheckableButton(const QString &text, QWidget *parent = nullptr, ObjectType type = ObjectType::OBST);

    /**
     * @brief Get the overlay widget of the button
     * @return OverlayWidget* The overlay widget of the button
     */
    OverlayWidget *getOverlay() const { return overlay; }

    /**
     * @brief Set the overlay widget of the button
     * @param overlay The overlay widget to set
     * @return void
     */
    void setOverlay(OverlayWidget *overlay) { this->overlay = overlay; }

  protected:
    /** @brief Pointer to the overlay widget */
    OverlayWidget *overlay;

    /** @brief The type of object that the button represents */
    ObjectType objType;

    /**
     * @brief Get the position of the widget on the grid.
     * @param localPos The local position of the mouse.
     * @return QPoint The position in the overlay widget.
     */
    QPoint getWidgetPos(QPoint localPos);

  private slots:

    /**
     * @brief Override the mousePressEvent method
     * @param event The mouse event
     * @return void
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Override the mouseMoveEvent method
     * @param event The mouse event
     * @return void
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief Override the mouseReleaseEvent method
     * @param event The mouse event
     * @return void
     */
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CHECKABLEBUTTON_HPP
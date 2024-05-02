/**
 * @file overlaywidget.hpp
 * @brief This file contains the declaration of the OverlayWidget class.
 * @details It is a subclass of the QWidget class and represents an overlay widget.
 * @authors Tomáš Hobza, Jakub Všetečka
 */

#ifndef OVERLAYWIDGET_HPP
#define OVERLAYWIDGET_HPP

#include "gameobject.hpp"
#include "obstacle.hpp"
#include "simulationengine.hpp"
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <qgesture.h>

/**
 * @class OverlayWidget
 * @brief A class to represent an overlay widget.
 * @details This class provides an interface for creating and managing overlay widgets.
 * @see QWidget
 */
class OverlayWidget : public QWidget {
  public:
    /**
     * @brief Construct a new Overlay Widget object.
     *
     * @param parent The parent widget. Default is nullptr.
     * @param simEng The simulation engine. Default is nullptr.
     * @param graphView The graphics view. Default is nullptr.
     */
    explicit OverlayWidget(QWidget *parent = nullptr, SimulationEngine *simEng = nullptr, QGraphicsView *graphView = nullptr);

    /**
     * @brief Try grab the object based on the mouse position.
     * @param event The mouse event.
     * @return void
     */
    void trySetSail(QMouseEvent *event);

    /**
     * @brief Drag the object based on the mouse position in the overlay.
     * @param event The mouse event.
     * @return void
     */
    void navigateTheSea(QMouseEvent *event);

    /**
     * @brief Anchor the object based on the mouse position back to scene.
     * @return void
     */
    void anchor();

    /**
     * @brief Get the time constant of the simulation engine.
     * @return qreal* The time constant of the simulation engine.
     */
    qreal *getTimeConstant() { return simEng->getTimeConstant(); }

    /**
     * @brief Get the active object.
     * @return GameObject* The active object.
     */
    void setActiveObject(GameObject *obj) { activeObject = obj; }

    /**
     * @brief Get the last mouse position.
     * @return QPoint The last mouse position.
     */
    void setLastMousePos(QPoint pos) { lastMousePos = pos; }

  protected:
    /** @brief The active object. */
    GameObject *activeObject;

    /** @brief The last mouse position. */
    QPoint lastMousePos;

    /** @brief The simulation engine. */
    SimulationEngine *simEng;

    /** @brief The graphics view. */
    QGraphicsView *graphView;

    /** @brief The option for the graphics item. */
    QStyleOptionGraphicsItem option;

    /**
     * @brief Override the mousePressEvent method.
     * @param event The mouse event.
     * @return void
     */
    void paintEvent(QPaintEvent *event) override;
};

#endif // OVERLAYWIDGET_HPP
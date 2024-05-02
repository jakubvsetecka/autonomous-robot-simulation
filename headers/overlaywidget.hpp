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

class OverlayWidget : public QWidget {
  public:
    explicit OverlayWidget(QWidget *parent = nullptr, SimulationEngine *simEng = nullptr, QGraphicsView *graphView = nullptr);

    void trySetSail(QMouseEvent *event);
    void navigateTheSea(QMouseEvent *event);
    void anchor();

    qreal *getTimeConstant() { simEng->getTimeConstant(); }
    void setActiveObject(GameObject *obj) { activeObject = obj; }
    void setLastMousePos(QPoint pos) { lastMousePos = pos; }

  protected:
    GameObject *activeObject;
    QPoint lastMousePos;
    SimulationEngine *simEng;
    QGraphicsView *graphView;
    QStyleOptionGraphicsItem option;

    void paintEvent(QPaintEvent *event) override;
};

#endif // OVERLAYWIDGET_HPP
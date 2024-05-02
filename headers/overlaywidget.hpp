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

    GameObject *activeObject;
    QPoint lastMousePos;
    SimulationEngine *simEng;

    void anchor();
    void trySetSail(QMouseEvent *event);
    void navigateTheSea(QMouseEvent *event);

  protected:
    QGraphicsView *graphView;
    QStyleOptionGraphicsItem option;

    void paintEvent(QPaintEvent *event) override;
};

#endif // OVERLAYWIDGET_HPP
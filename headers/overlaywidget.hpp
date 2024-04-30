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
    explicit OverlayWidget(QWidget *parent = nullptr, SimulationEngine *simEng = nullptr, QGraphicsView *graphView = nullptr)
        : QWidget(parent), simEng(simEng), graphView(graphView) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
        option = QStyleOptionGraphicsItem();
        activeObject = nullptr;
        lastMousePos = QPoint(-1, -1);
        setMouseTracking(true); // Enable mouse tracking
    }

    GameObject *activeObject;
    QPoint lastMousePos;
    SimulationEngine *simEng;

    void anchor() {
        if (activeObject) {
            auto object = dynamic_cast<QGraphicsItem *>(activeObject);
            if (object) {
                QPoint localPos = graphView->mapFromParent(lastMousePos);
                QPointF scenePos = graphView->mapToScene(localPos);

                if (simEng->isInsideScene(scenePos)) {
                    object->setPos(scenePos);
                    simEng->addItem(object);
                } else {
                    delete object;
                }
            }
            activeObject = nullptr;
        }
    }

    void trySetSail(QMouseEvent *event) {
        event->ignore();
        QPoint localPos = graphView->mapFromParent(event->pos());
        QPointF scenePos = graphView->mapToScene(localPos);
        QGraphicsItem *item = graphView->itemAt(scenePos.toPoint());
        if (item) {
            // Handle the click on the item
            auto object = dynamic_cast<GameObject *>(item);
            if (object) {
                activeObject = object;
                lastMousePos = event->pos();
                simEng->removeItem(item);
            }
        }
    }

    void navigateTheSea(QMouseEvent *event) {
        event->ignore();
        if (activeObject) {
            lastMousePos = event->pos();
            update(); // Trigger repaint
        }
    }

  protected:
    QGraphicsView *graphView;
    QStyleOptionGraphicsItem option;

    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        if (activeObject) {
            // Use lastMousePos here
            painter.save();
            painter.translate(lastMousePos);
            activeObject->paint(&painter, &option, this);
            update(); // Trigger repaint
            painter.restore();
        }
    }
};

#endif // OVERLAYWIDGET_HPP
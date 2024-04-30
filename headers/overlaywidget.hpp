#ifndef OVERLAYWIDGET_HPP
#define OVERLAYWIDGET_HPP

#include "gameobject.hpp"
#include "obstacle.hpp"
#include "simulationengine.hpp"
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

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

    void anchorObject() {
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

  protected:
    SimulationEngine *simEng;
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

    void mouseMoveEvent(QMouseEvent *event) override {
        qDebug() << "Mouse move event in overlay widget";
        lastMousePos = event->pos(); // Update last mouse position
        update();                    // Trigger repaint
    }

    void mousePressEvent(QMouseEvent *event) {
        qDebug() << "Mouse press event in overlay widget";
        QGraphicsItem *item = graphView->itemAt(event->pos());
        if (item) {
            // Handle the click on the item
            qDebug() << "Item clicked:" << item;
        } else {
            // If no item is clicked, forward the event to the base class
            QWidget::mousePressEvent(event);
        }
    }
};

#endif // OVERLAYWIDGET_HPP
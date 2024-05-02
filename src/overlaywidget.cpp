/**
 * @file overlaywidget.cpp
 * @brief This file contains the implementation of the OverlayWidget class.
 * @details It is a subclass of the QWidget class and represents an overlay widget for the QGraphicsView.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#include "overlaywidget.hpp"

OverlayWidget::OverlayWidget(QWidget *parent, SimulationEngine *simEng, QGraphicsView *graphView)
    : QWidget(parent), simEng(simEng), graphView(graphView) {
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
    option = QStyleOptionGraphicsItem();
    activeObject = nullptr;
    lastMousePos = QPoint(-1, -1);
    setMouseTracking(true); // Enable mouse tracking
}

void OverlayWidget::anchor() {
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

void OverlayWidget::trySetSail(QMouseEvent *event) {
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

void OverlayWidget::navigateTheSea(QMouseEvent *event) {
    event->ignore();
    if (activeObject) {
        lastMousePos = event->pos();
        update(); // Trigger repaint
    }
}

void OverlayWidget::paintEvent(QPaintEvent *event) {
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
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

            if (simEng->isInsideScene(scenePos - offset)) {
                object->setPos(scenePos - offset);
                simEng->addItem(object);
                object->setFocus();
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
            qDebug() << "Rotation: " << object->rotation() << " degrees";
            activeObject->setRotation(object->rotation());
            lastMousePos = event->pos();
            offset = (item->mapFromScene(scenePos)).toPoint();
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
    QPoint localPos = graphView->mapFromParent(lastMousePos);
    QPointF scenePos = graphView->mapToScene(localPos);

    if (activeObject) {
        painter.save();
        painter.translate(lastMousePos - offset);
        painter.translate(activeObject->getCenter()); // Move origin to object center
        painter.rotate(activeObject->rotation());     // Rotate around object center
        painter.translate(-activeObject->getCenter());
        activeObject->paint(&painter, &option, this);
        update(); // Trigger repaint
        painter.restore();
    }
}
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

            qreal angle = activeObject->rotation();

            QPointF center = activeObject->getCenter();
            offset = QPoint(center.x() - offset.x(), center.y() - offset.y());
            offset = convertFromRotatedSystem(offset, angle);
            QPoint dest = scenePos.toPoint() - center.toPoint() + offset;

            if (simEng->isInsideScene(scenePos)) {
                object->setPos(dest);
                simEng->addItem(object);
                object->setFocus();
            } else {
                delete object;
            }
        }
        activeObject = nullptr;
        offset = QPoint(0, 0);
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

QPoint OverlayWidget::convertToRotatedSystem(QPoint point, qreal angle) {
    qreal x = point.x();
    qreal y = point.y();
    qreal angleRad = qDegreesToRadians(angle);
    qreal xNew = x * qCos(angleRad) - y * qSin(angleRad);
    qreal yNew = x * qSin(angleRad) + y * qCos(angleRad);
    return QPoint(xNew, yNew);
}

QPoint OverlayWidget::convertFromRotatedSystem(QPoint point, qreal angle) {
    qreal x = point.x();
    qreal y = point.y();
    qreal angleRad = qDegreesToRadians(angle);
    qreal xNew = x * qCos(angleRad) - y * qSin(angleRad);
    qreal yNew = x * qSin(angleRad) + y * qCos(angleRad);
    return QPoint(xNew, yNew);
}

void OverlayWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (activeObject) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.save();

        qreal angle = activeObject->rotation();
        QPointF center = activeObject->getCenter(); // Fix: Change QPoint to QPointF

        // Translate and rotate the painter to position the object correctly
        painter.translate(lastMousePos - convertToRotatedSystem(center.toPoint(), angle));
        painter.rotate(angle);

        painter.translate(center - offset);

        activeObject->paint(&painter, &option, this);

        update(); // Trigger repaint
        painter.restore();
    }
}
/**
 * @file expbuttonwidget.cpp
 * @brief This file contains the implementation of the ExpandableButtonWidget class.
 * @details It is a subclass of the QWidget class and represents a widget with expandable buttons.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#include "expbuttonwidget.hpp"

ExpandableButtonWidget::ExpandableButtonWidget(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    obstacleButton = new CheckableButton("Add Obstacle", this, CheckableButton::ObjectType::OBST);
    mainButton = new ExpButton("Add Robot", this);
    autoButton = new CheckableButton("Auto", this, CheckableButton::ObjectType::AUTO);
    controlButton = new CheckableButton("Controlled", this, CheckableButton::ObjectType::CONT);

    autoButton->hide();    // Initially hidden
    controlButton->hide(); // Initially hidden

    layout->addWidget(obstacleButton);
    layout->addWidget(mainButton);
    layout->addWidget(autoButton);
    layout->addWidget(controlButton);

    connect(mainButton, &ExpButton::pressed, this, &ExpandableButtonWidget::expand);

    // Install an event filter to listen for clicks outside the widget
    qApp->installEventFilter(this);
}

void ExpandableButtonWidget::expand() {
    bool isVisible = autoButton->isVisible();
    autoButton->setVisible(!isVisible);
    controlButton->setVisible(!isVisible);
    mainButton->setVisible(isVisible);
}

void ExpandableButtonWidget::collapse() {
    // Collapse the expandable buttons
    for (int i = 1; i < layout()->count(); ++i) {
        QLayoutItem *item = layout()->itemAt(i);
        if (item->widget()) {
            item->widget()->hide();
            mainButton->show();
        }
    }
}

void ExpandableButtonWidget::setOverlay(OverlayWidget *overlay) {
    obstacleButton->setOverlay(overlay);
    autoButton->setOverlay(overlay);
    controlButton->setOverlay(overlay);
}
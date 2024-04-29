#ifndef EXPANDABLEBUTTONWIDGET_HPP
#define EXPANDABLEBUTTONWIDGET_HPP

// ExpandableButtonWidget.h
#include "checkablebutton.hpp"
#include "overlaywidget.hpp"
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class ExpandableButtonWidget : public QWidget {
    Q_OBJECT

  public:
    CheckableButton *obstacleButton;
    QPushButton *mainButton;
    CheckableButton *autoButton;
    CheckableButton *controlButton;

    explicit ExpandableButtonWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        obstacleButton = new CheckableButton("Add Obstacle", this, CheckableButton::ObjectType::OBST);
        mainButton = new QPushButton("Add Robot", this);
        autoButton = new CheckableButton("Auto", this, CheckableButton::ObjectType::AUTO);
        controlButton = new CheckableButton("Controlled", this, CheckableButton::ObjectType::CONT);

        autoButton->hide();    // Initially hidden
        controlButton->hide(); // Initially hidden

        layout->addWidget(obstacleButton);
        layout->addWidget(mainButton);
        layout->addWidget(autoButton);
        layout->addWidget(controlButton);

        connect(mainButton, &QPushButton::clicked, [this]() {
            bool isVisible = autoButton->isVisible();
            autoButton->setVisible(!isVisible);
            controlButton->setVisible(!isVisible);
            mainButton->setVisible(isVisible);
        });

        // Install an event filter to listen for clicks outside the widget
        qApp->installEventFilter(this);
    }

    void collapse() {
        // Collapse the expandable buttons
        for (int i = 1; i < layout()->count(); ++i) {
            QLayoutItem *item = layout()->itemAt(i);
            if (item->widget()) {
                item->widget()->hide();
                mainButton->show();
            }
        }
    }
};

#endif // EXPANDABLEBUTTONWIDGET_HPP
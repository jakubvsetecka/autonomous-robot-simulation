#ifndef EXPANDABLEBUTTONWIDGET_HPP
#define EXPANDABLEBUTTONWIDGET_HPP

// ExpandableButtonWidget.h
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
    QPushButton *mainButton;
    QPushButton *button1;
    QPushButton *button2;

    explicit ExpandableButtonWidget(QWidget *parent = nullptr)
        : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        mainButton = new QPushButton("Add Robot", this);
        button1 = new QPushButton("Auto", this);
        button2 = new QPushButton("Controlled", this);

        button1->hide(); // Initially hidden
        button2->hide(); // Initially hidden

        layout->addWidget(mainButton);
        layout->addWidget(button1);
        layout->addWidget(button2);

        connect(mainButton, &QPushButton::clicked, [this]() {
            bool isVisible = button1->isVisible();
            button1->setVisible(!isVisible);
            button2->setVisible(!isVisible);
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
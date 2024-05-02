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

    explicit ExpandableButtonWidget(QWidget *parent = nullptr);
    void collapse();
};

#endif // EXPANDABLEBUTTONWIDGET_HPP
#ifndef EXPANDABLEBUTTONWIDGET_HPP
#define EXPANDABLEBUTTONWIDGET_HPP

// ExpandableButtonWidget.h
#include "checkablebutton.hpp"
#include "expbutton.hpp"
#include "overlaywidget.hpp"
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

/**
 * @brief A class to represent an expandable button widget.

*/
class ExpandableButtonWidget : public QWidget {
    Q_OBJECT

  public:
    explicit ExpandableButtonWidget(QWidget *parent = nullptr);

    /** @brief Collapse the widget.*/
    void collapse();

    /** @brief Collapse the widget.*/
    void setOverlay(OverlayWidget *overlay);

  protected:
    CheckableButton *obstacleButton;
    ExpButton *mainButton;
    CheckableButton *autoButton;
    CheckableButton *controlButton;

  private slots:
    /** @brief Expand the widget.*/
    void expand();
};

#endif // EXPANDABLEBUTTONWIDGET_HPP
/**
 * @file expbuttonwidget.hpp
 * @brief This file contains the declaration of the ExpandableButtonWidget class.
 * @details It is a subclass of the QWidget class and represents an expandable button widget.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

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
 * @class ExpandableButtonWidget
 * @brief A class to represent an expandable button widget.
 * @details This class provides an interface for creating and managing expandable button widgets.
 * @see QWidget
 */
class ExpandableButtonWidget : public QWidget {
    Q_OBJECT

  public:
    /**
     * @brief Construct a new Expandable Button Widget object.
     * @param parent The parent widget. Default is nullptr.
     */
    explicit ExpandableButtonWidget(QWidget *parent = nullptr);

    /**
     * @brief Get the obstacle button.
     * @return CheckableButton* The obstacle button.
     */
    void collapse();

    /**
     * @brief Get the obstacle button.
     * @return CheckableButton* The obstacle button.
     */
    void setOverlay(OverlayWidget *overlay);

  protected:
    /** @brief Reference to the obstacle button.*/
    CheckableButton *obstacleButton;

    /** @brief Reference to the main button.*/
    ExpButton *mainButton;

    /** @brief Reference to the auto button.*/
    CheckableButton *autoButton;

    /** @brief Reference to the control button.*/
    CheckableButton *controlButton;

  private slots:
    /**
     * @brief Slot to handle the main button press event.
     * @return void
     */
    void expand();
};

#endif // EXPANDABLEBUTTONWIDGET_HPP
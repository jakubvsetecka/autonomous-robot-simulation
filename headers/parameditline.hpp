/**
 * @file parameditline.hpp
 * @brief This file contains the declaration of the ParamEditLine class.
 * @details It is a subclass of the QLineEdit class and represents a line edit widget for editing parameters.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 03.05.2024
 */

#ifndef PARAMEDITLINE_HPP
#define PARAMEDITLINE_HPP

#include <QFocusEvent>
#include <QLineEdit>

/**
 * @class ParamEditLine
 * @brief A class to represent a line edit widget for editing parameters.
 * @details This class inherits from QLineEdit and provides a line edit widget for editing parameters.
 * @see QLineEdit
 */
class ParamEditLine : public QLineEdit {
    Q_OBJECT

  public:
    /**
     * @brief Default constructor.
     * @param parent The parent widget.
     */
    explicit ParamEditLine(QWidget *parent = nullptr)
        : QLineEdit(parent) {}

    /**
     * @brief Overridden focusInEvent method.
     * @param event The focus event.
     * @return void
     */
    void focusInEvent(QFocusEvent *event) override {
        QLineEdit::focusOutEvent(event);
        emit focusIn();
    }

    /**
     * @brief Overridden focusOutEvent method.
     * @param event The focus event.
     * @return void
     */
    void focusOutEvent(QFocusEvent *event) override {
        QLineEdit::focusOutEvent(event);
        emit focusOut();
    }

  signals:
    /**
     * @brief Signal emitted when the line edit widget gains focus.
     * @return void
     */
    void focusIn();

    /**
     * @brief Signal emitted when the line edit widget loses focus.
     * @return void
     */
    void focusOut();
};

#endif // PARAMEDITLINE_HPP

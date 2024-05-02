/**
 * @file popupsavewindow.h
 * @brief This file contains the declaration of the PopupSaveWindow class.
 * @details It is a subclass of the QDialog class and represents a popup save window.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#ifndef POPUPSAVEWINDOW_H
#define POPUPSAVEWINDOW_H

#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

/**
 * @class PopupSaveWindow
 * @brief A class to represent a popup save window.
 * @details This class provides an interface for creating and managing a popup save window.
 * @see QDialog
 */
class PopupSaveWindow : public QDialog {
    Q_OBJECT

  public:
    /**
     * @brief Construct a new Popup Save Window object.
     * @param parent The parent widget. Default is nullptr.
     */
    explicit PopupSaveWindow(QWidget *parent = nullptr);
    ~PopupSaveWindow();

    /**
     * @brief Get the entered text.
     * @return QString The entered text.
     */
    QString getEnteredText() { return enteredText; }

  private:
    /** @brief The entered text. */
    QString enteredText;

    /** @brief The line edit widget. */
    QLineEdit *lineEdit;

  private slots:

    /**
     * @brief Slot to handle the ok button click event.
     * @return void
     */
    void onOkClicked();
};

#endif // POPUPSAVEWINDOW_H

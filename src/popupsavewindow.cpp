/**
 * @file popupsavewindow.cpp
 * @brief This file contains the implementation of the PopupSaveWindow class.
 * @details It is a subclass of the QDialog class and represents a popup save window.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#include "popupsavewindow.h"

PopupSaveWindow::PopupSaveWindow(QWidget *parent)
    : QDialog(parent) {
    // Create layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Enter name:", this);
    lineEdit = new QLineEdit(this);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // Connect the "OK" button to the slot
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PopupSaveWindow::onOkClicked);

    // Connect the "Cancel" button to the slot
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PopupSaveWindow::reject);

    // Add widgets to layout
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(buttonBox);

    setLayout(layout);
}

PopupSaveWindow::~PopupSaveWindow() {}

void PopupSaveWindow::onOkClicked() {
    // Set the dialog as accepted
    enteredText = lineEdit->text();

    accept();
}
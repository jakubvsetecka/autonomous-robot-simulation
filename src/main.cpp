/**
 * @file main.cpp
 * @brief This file contains the main function of the application.
 * @details It creates the main window and runs the application.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

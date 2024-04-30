#include "mainwindow.h"
#include "popupsavewindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    PopupSaveWindow popupWindow;

    // Show the popup window
    popupWindow.show();
    w.show();
    return a.exec();
}

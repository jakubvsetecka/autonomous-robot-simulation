#ifndef POPUPSAVEWINDOW_H
#define POPUPSAVEWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class PopupSaveWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PopupSaveWindow(QWidget *parent = nullptr);

signals:

};

#endif // POPUPSAVEWINDOW_H

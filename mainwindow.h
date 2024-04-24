#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupAnimation();

private:
    Ui::MainWindow *ui;

    QGraphicsRectItem *square; // Declare the square as a member variable

    std::vector<int> square_velocity = {4, 4};

    void initScene();
    void updateAnimation(); // Method to update the animation

};
#endif // MAINWINDOW_H

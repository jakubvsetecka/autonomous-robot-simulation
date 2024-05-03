

#ifndef PARAMWIDGET_HPP
#define PARAMWIDGET_HPP

#include "autorobot.hpp"
#include "gameobject.hpp"
#include "obstacle.hpp"
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

class ParamWidget : public QWidget {
    Q_OBJECT

  public:
    explicit ParamWidget(QWidget *parent = nullptr);

    void stalk(AutoRobot *robot);
    void stalk(Obstacle *obstacle);
    void hide();

  private:
    QVBoxLayout *layout;
    GameObject *stalkedObject = nullptr;

    QLabel *labelDetectionDistance;
    QLineEdit *detectionDistance;
    QLabel *labelAngleToRotate;
    QLineEdit *angleToRotate;
    QLabel *labelDirection;
    QLineEdit *direction;
    QLabel *labelSpeed;
    QLineEdit *speed;
    QLabel *labelRadius;
    QLineEdit *radius;
    QLabel *labelAngle;
    QLineEdit *angle;

    QLabel *labelSize;
    QLineEdit *size;
    QLabel *labelOAngle;
    QLineEdit *oAngle;

  private slots:
    void show();
};

#endif // PARAMWIDGET_HPP
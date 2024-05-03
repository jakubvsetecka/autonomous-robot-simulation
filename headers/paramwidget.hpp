

#ifndef PARAMWIDGET_HPP
#define PARAMWIDGET_HPP

#include "autorobot.hpp"
#include "gameobject.hpp"
#include "obstacle.hpp"
#include "parameditline.hpp"
#include <QLabel>
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
    bool keepUpdating = true;

    QLabel *labelDetectionDistance;
    ParamEditLine *detectionDistance;
    QLabel *labelAngleToRotate;
    ParamEditLine *angleToRotate;
    QLabel *labelDirection;
    ParamEditLine *direction;
    QLabel *labelSpeed;
    ParamEditLine *speed;
    QLabel *labelRadius;
    ParamEditLine *radius;
    QLabel *labelAngle;
    ParamEditLine *angle;

    QLabel *labelSize;
    ParamEditLine *size;
    QLabel *labelOAngle;
    ParamEditLine *oAngle;

    void setUpEditLine(ParamEditLine *lineEdit, QLabel *label);

  private slots:
    void show();
    void setDetectionDistance();
    void setAngleToRotate();
    void setDirection();
    void setSpeed();
    void setRadius();
    void setAngle();
    void setSize();
    void setOAngle();

    void focusIn() { keepUpdating = false; }
    void focusOut() { keepUpdating = true; }
};

#endif // PARAMWIDGET_HPP
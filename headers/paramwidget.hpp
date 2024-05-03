

#ifndef PARAMWIDGET_HPP
#define PARAMWIDGET_HPP

#include "autorobot.hpp"
#include "gameobject.hpp"
#include "obstacle.hpp"
#include "parameditline.hpp"
#include "robot.hpp"
#include <QCheckBox>
#include <QDoubleValidator>
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
    void stalk(Robot *robot);
    void stopStalking();

  private:
    QVBoxLayout *layout;
    GameObject *stalkedObject = nullptr;
    bool keepUpdating = true;
    QDoubleValidator *numberValidator;

    QLabel *labelDetectionDistance;
    ParamEditLine *detectionDistance;
    QLabel *labelAngleToRotate;
    ParamEditLine *angleToRotate;
    QLabel *labelDirection;
    QCheckBox *direction;
    QLabel *labelSpeed;
    ParamEditLine *speed;
    QLabel *labelRadius;
    ParamEditLine *radius;
    QLabel *labelAngle;
    ParamEditLine *angle;
    QLabel *labelSize;
    ParamEditLine *size;

    void setUpEditLine(ParamEditLine *lineEdit, QLabel *label);
    void show(Robot *robot);
    void show(AutoRobot *robot);
    void show(Obstacle *obstacle);
    void hide();
    void disconnectStalkedObject();

  private slots:
    void setDetectionDistance();
    void setAngleToRotate();
    void setDirection();
    void setSpeed();
    void setRadius();
    void setAngle();
    void setSize();

    void focusIn() { keepUpdating = false; }
    void focusOut() { keepUpdating = true; }

    void updateAutoRobot();
    void updateObstacle();
    void updateRobot();
};

#endif // PARAMWIDGET_HPP
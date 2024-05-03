#include "paramwidget.hpp"
#include <QDebug>

ParamWidget::ParamWidget(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    labelDetectionDistance = new QLabel("Detection distance:", this);
    detectionDistance = new QLineEdit(this);
    detectionDistance->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(labelDetectionDistance);
    layout->addWidget(detectionDistance);

    labelAngleToRotate = new QLabel("Angle to rotate:", this);
    angleToRotate = new QLineEdit(this);
    angleToRotate->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(labelAngleToRotate);
    layout->addWidget(angleToRotate);

    labelDirection = new QLabel("Direction:", this);
    direction = new QLineEdit(this);
    direction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(labelDirection);
    layout->addWidget(direction);

    labelSpeed = new QLabel("Speed:", this);
    speed = new QLineEdit(this);
    speed->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(labelSpeed);
    layout->addWidget(speed);

    labelRadius = new QLabel("Radius:", this);
    radius = new QLineEdit(this);
    radius->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(labelRadius);
    layout->addWidget(radius);

    labelAngle = new QLabel("Angle:", this);
    angle = new QLineEdit(this);
    angle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(labelAngle);
    layout->addWidget(angle);

    labelSize = new QLabel("Size:", this);
    size = new QLineEdit(this);
    size->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(labelSize);
    layout->addWidget(size);

    labelOAngle = new QLabel("Angle:", this);
    oAngle = new QLineEdit(this);
    oAngle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(labelOAngle);
    layout->addWidget(oAngle);

    layout->addStretch();

    hide();
}

void ParamWidget::stalk(AutoRobot *robot) {
    stalkedObject = robot;
    connect(robot, &AutoRobot::paramsUpdated, this, &ParamWidget::show);
    show();
}

void ParamWidget::show() {
    if (stalkedObject == nullptr)
        return;

    qDebug() << "Showing params";

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);
    if (robot) {
        qDebug() << "Showing robot params";
        labelDetectionDistance->show();
        detectionDistance->show();
        labelAngleToRotate->show();
        angleToRotate->show();
        labelDirection->show();
        direction->show();
        labelSpeed->show();
        speed->show();
        labelRadius->show();
        radius->show();
        labelAngle->show();
        angle->show();
        labelSize->hide();
        size->hide();
        labelOAngle->hide();
        oAngle->hide();

        detectionDistance->setText(QString::number(robot->getCollisionLookAhead()));
        angleToRotate->setText(QString::number(robot->getTargetAngle()));
        direction->setText(QString::number(robot->getRotationDirection()));
        speed->setText(QString::number(robot->getMoveSpeed()));
        radius->setText(QString::number(robot->getRadius()));
        angle->setText(QString::number(robot->getAngle()));
    }
}

void ParamWidget::hide() {
    labelDetectionDistance->hide();
    detectionDistance->hide();
    labelAngleToRotate->hide();
    angleToRotate->hide();
    labelDirection->hide();
    direction->hide();
    labelSpeed->hide();
    speed->hide();
    labelRadius->hide();
    radius->hide();
    labelAngle->hide();
    angle->hide();
    labelSize->hide();
    size->hide();
    labelOAngle->hide();
    oAngle->hide();
}
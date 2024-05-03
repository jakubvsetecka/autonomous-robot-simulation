#include "paramwidget.hpp"

ParamWidget::ParamWidget(QWidget *parent)
    : QWidget(parent) {
    layout = new QVBoxLayout(this);
    setLayout(layout);

    labelDetectionDistance = new QLabel("Detection distance:", this);
    detectionDistance = new ParamEditLine(this);
    setUpEditLine(detectionDistance, labelDetectionDistance);
    connect(detectionDistance, &ParamEditLine::returnPressed, this, &ParamWidget::setDetectionDistance);

    labelAngleToRotate = new QLabel("Rotation amount:", this);
    angleToRotate = new ParamEditLine(this);
    setUpEditLine(angleToRotate, labelAngleToRotate);
    connect(angleToRotate, &ParamEditLine::returnPressed, this, &ParamWidget::setAngleToRotate);

    labelDirection = new QLabel("Direction:", this);
    direction = new ParamEditLine(this);
    setUpEditLine(direction, labelDirection);
    connect(direction, &ParamEditLine::returnPressed, this, &ParamWidget::setDirection);

    labelSpeed = new QLabel("Speed:", this);
    speed = new ParamEditLine(this);
    setUpEditLine(speed, labelSpeed);
    connect(speed, &ParamEditLine::returnPressed, this, &ParamWidget::setSpeed);

    labelRadius = new QLabel("Radius:", this);
    radius = new ParamEditLine(this);
    setUpEditLine(radius, labelRadius);
    connect(radius, &ParamEditLine::returnPressed, this, &ParamWidget::setRadius);

    labelAngle = new QLabel("Angle:", this);
    angle = new ParamEditLine(this);
    setUpEditLine(angle, labelAngle);
    connect(angle, &ParamEditLine::returnPressed, this, &ParamWidget::setAngle);

    labelSize = new QLabel("Size:", this);
    size = new ParamEditLine(this);
    setUpEditLine(size, labelSize);
    connect(size, &ParamEditLine::returnPressed, this, &ParamWidget::setSize);

    labelOAngle = new QLabel("Angle:", this);
    oAngle = new ParamEditLine(this);
    setUpEditLine(oAngle, labelOAngle);
    connect(oAngle, &ParamEditLine::returnPressed, this, &ParamWidget::setOAngle);

    layout->addStretch();

    hide();
}

void ParamWidget::setUpEditLine(ParamEditLine *lineEdit, QLabel *label) {
    lineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    lineEdit->setCursorMoveStyle(Qt::VisualMoveStyle);
    lineEdit->setFocusPolicy(Qt::StrongFocus);
    connect(lineEdit, &ParamEditLine::focusIn, this, &ParamWidget::focusIn);
    connect(lineEdit, &ParamEditLine::focusOut, this, &ParamWidget::focusOut);
}

void ParamWidget::stalk(AutoRobot *robot) {
    stalkedObject = robot;
    connect(robot, &AutoRobot::paramsUpdated, this, &ParamWidget::show);
    show();
}

void ParamWidget::show() {
    if (stalkedObject == nullptr)
        return;

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);
    if (robot) {
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

        if (keepUpdating) {
            detectionDistance->setText(QString::number(robot->getCollisionLookAhead()));
            angleToRotate->setText(QString::number(robot->getRotationSpeed()));
            direction->setText(QString::number(robot->getRotationDirection()));
            speed->setText(QString::number(robot->getMoveSpeed()));
            radius->setText(QString::number(robot->getRadius()));
            angle->setText(QString::number(static_cast<int>(robot->getAngle()) % 360));
        }
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

    stalkedObject = nullptr;
}

void ParamWidget::setDetectionDistance() {
    if (stalkedObject == nullptr)
        return;

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);
    if (robot) {
        robot->setCollisionLookAhead(detectionDistance->text().toDouble());
    }
}

void ParamWidget::setAngleToRotate() {
    if (stalkedObject == nullptr)
        return;

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);
    if (robot) {
        robot->setRotationSpeed(angleToRotate->text().toDouble());
    }
}

void ParamWidget::setDirection() {
    if (stalkedObject == nullptr)
        return;

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);
    if (robot) {
        robot->setRotationDirection(static_cast<Robot::RotationDirection>(direction->text().toInt()));
    }
}

void ParamWidget::setSpeed() {
    if (stalkedObject == nullptr)
        return;

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);
    if (robot) {
        robot->setMoveSpeed(speed->text().toDouble());
    }
}

void ParamWidget::setRadius() {
    if (stalkedObject == nullptr)
        return;

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);
    if (robot) {
        robot->setRadius(radius->text().toDouble());
    }
}

void ParamWidget::setAngle() {
    if (stalkedObject == nullptr)
        return;

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);
    if (robot) {
        robot->setRotation(angle->text().toDouble());
    }
}

void ParamWidget::setSize() {
    if (stalkedObject == nullptr)
        return;

    Obstacle *obstacle = dynamic_cast<Obstacle *>(stalkedObject);
    if (obstacle) {
        obstacle->setRect(0, 0, size->text().toDouble(), size->text().toDouble());
    }
}

void ParamWidget::setOAngle() {
    if (stalkedObject == nullptr)
        return;

    Obstacle *obstacle = dynamic_cast<Obstacle *>(stalkedObject);
    if (obstacle) {
        obstacle->setRotation(oAngle->text().toDouble());
    }
}
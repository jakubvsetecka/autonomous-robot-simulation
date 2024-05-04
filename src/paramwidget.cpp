/**
 * @file paramwidget.cpp
 * @brief This file contains the implementation of the ParamWidget class.
 * @details It is a subclass of the QWidget class and represents a widget for editing parameters of game objects.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 03.05.2024
 */

#include "paramwidget.hpp"

ParamWidget::ParamWidget(QWidget *parent)
    : QWidget(parent) {
    layout = new QVBoxLayout(this);
    setLayout(layout);

    numberValidator = new QDoubleValidator();
    numberValidator->setNotation(QDoubleValidator::StandardNotation);
    numberValidator->setBottom(0);
    numberValidator->setDecimals(3);

    labelDetectionDistance = new QLabel("Detection distance:", this);
    detectionDistance = new ParamEditLine(this);
    setUpEditLine(detectionDistance, labelDetectionDistance);
    connect(detectionDistance, &ParamEditLine::returnPressed, this, &ParamWidget::setDetectionDistance);

    labelAngleToRotate = new QLabel("Rotation amount:", this);
    angleToRotate = new ParamEditLine(this);
    setUpEditLine(angleToRotate, labelAngleToRotate);
    connect(angleToRotate, &ParamEditLine::returnPressed, this, &ParamWidget::setAngleToRotate);

    labelDirection = new QLabel("Rotation direction:", this);
    direction = new QCheckBox("anticlockwise", this);
    direction->setCheckState(Qt::Unchecked);
    direction->setTristate(false);
    direction->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    direction->setCursor(Qt::PointingHandCursor);
    direction->setFocusPolicy(Qt::StrongFocus);
    layout->addWidget(labelDirection);
    layout->addWidget(direction);
    connect(direction, &QCheckBox::stateChanged, this, &ParamWidget::setDirection);

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

    layout->addStretch();

    hide();
}

void ParamWidget::setUpEditLine(ParamEditLine *lineEdit, QLabel *label) {
    lineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    lineEdit->setCursorMoveStyle(Qt::VisualMoveStyle);
    lineEdit->setFocusPolicy(Qt::StrongFocus);
    lineEdit->setValidator(numberValidator);
    connect(lineEdit, &ParamEditLine::focusIn, this, &ParamWidget::focusIn);
    connect(lineEdit, &ParamEditLine::focusOut, this, &ParamWidget::focusOut);
}

void ParamWidget::stalk(AutoRobot *robot) {
    hide();
    if (stalkedObject)
        disconnectStalkedObject();
    stalkedObject = robot;
    connect(robot, &AutoRobot::paramsUpdated, this, &ParamWidget::updateAutoRobot);
    connect(robot, &Robot::robotSepuku, this, &ParamWidget::hide);
    show(robot);
    updateAutoRobot();
}

void ParamWidget::stalk(Obstacle *obstacle) {
    hide();
    if (stalkedObject)
        disconnectStalkedObject();
    stalkedObject = obstacle;
    connect(obstacle, &Obstacle::paramsUpdated, this, &ParamWidget::updateObstacle);
    connect(obstacle, &Obstacle::obstacleSepuku, this, &ParamWidget::hide);
    show(obstacle);
    updateObstacle();
}

void ParamWidget::stalk(Robot *robot) {
    hide();
    if (stalkedObject)
        disconnectStalkedObject();
    stalkedObject = robot;
    connect(robot, &Robot::paramsUpdated, this, &ParamWidget::updateRobot);
    connect(robot, &Robot::robotSepuku, this, &ParamWidget::hide);
    show(robot);
    updateRobot();
}

void ParamWidget::stopStalking() {
    stalkedObject = nullptr;
    hide();
}

void ParamWidget::disconnectStalkedObject() {
    qDebug() << "Disconnecting from the stalked object";
    if (stalkedObject != nullptr) {
        if (dynamic_cast<AutoRobot *>(stalkedObject))
            disconnect(dynamic_cast<AutoRobot *>(stalkedObject), &AutoRobot::paramsUpdated, this, &ParamWidget::updateAutoRobot);
        else if (dynamic_cast<Obstacle *>(stalkedObject))
            disconnect(dynamic_cast<Obstacle *>(stalkedObject), &Obstacle::paramsUpdated, this, &ParamWidget::updateObstacle);
        else if (dynamic_cast<Robot *>(stalkedObject))
            disconnect(dynamic_cast<Robot *>(stalkedObject), &Robot::paramsUpdated, this, &ParamWidget::updateRobot);
    }
    qDebug() << "Disconnected";
}

void ParamWidget::show(Robot *robot) {
    if (stalkedObject == nullptr)
        return;

    labelSpeed->show();
    speed->show();
    labelRadius->show();
    radius->show();
    labelAngle->show();
    angle->show();
}

void ParamWidget::show(AutoRobot *robot) {
    if (stalkedObject == nullptr)
        return;

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
}

void ParamWidget::show(Obstacle *obstacle) {
    if (stalkedObject == nullptr)
        return;

    labelSize->show();
    size->show();
    labelAngle->show();
    angle->show();
}

void ParamWidget::updateAutoRobot() {
    if (stalkedObject == nullptr)
        return;

    AutoRobot *robot = dynamic_cast<AutoRobot *>(stalkedObject);

    if (keepUpdating && robot) {
        detectionDistance->setText(QString::number(robot->getCollisionLookAhead()));
        angleToRotate->setText(QString::number(robot->getRotationSpeed()));
        direction->setText(robot->getRotationDirection() == Robot::RotationDirection::Left ? "anti-clockwise" : "clockwise");
        speed->setText(QString::number(robot->getMoveSpeed()));
        radius->setText(QString::number(robot->getRadius()));
        angle->setText(QString::number(static_cast<int>(robot->getAngle()) % 360));
    }
}

void ParamWidget::updateObstacle() {
    if (stalkedObject == nullptr)
        return;

    Obstacle *obstacle = dynamic_cast<Obstacle *>(stalkedObject);

    if (keepUpdating && obstacle) {
        size->setText(QString::number(obstacle->rect().width()));
        angle->setText(QString::number(static_cast<int>(obstacle->rotation()) % 360));
    }
}

void ParamWidget::updateRobot() {
    if (stalkedObject == nullptr)
        return;

    Robot *robot = dynamic_cast<Robot *>(stalkedObject);

    if (keepUpdating && robot) {
        speed->setText(QString::number(robot->getMoveSpeed()));
        radius->setText(QString::number(robot->getRadius()));
        angle->setText(QString::number(static_cast<int>(robot->getAngle()) % 360));
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

    stalkedObject = nullptr;
}

void ParamWidget::setDetectionDistance() {
    if (stalkedObject)
        dynamic_cast<AutoRobot *>(stalkedObject)->setCollisionLookAhead(detectionDistance->text().toDouble());
}

void ParamWidget::setAngleToRotate() {
    if (stalkedObject)
        dynamic_cast<AutoRobot *>(stalkedObject)->setRotationSpeed(angleToRotate->text().toDouble());
}

void ParamWidget::setDirection() {
    if (stalkedObject)
        dynamic_cast<AutoRobot *>(stalkedObject)->setRotationDirection(dynamic_cast<AutoRobot *>(stalkedObject)->getRotationDirection() == Robot::RotationDirection::Left ? Robot::RotationDirection::Right : Robot::RotationDirection::Left);
}

void ParamWidget::setSpeed() {
    if (stalkedObject)
        dynamic_cast<Robot *>(stalkedObject)->setMoveSpeed(speed->text().toDouble());
}

void ParamWidget::setRadius() {
    if (stalkedObject)
        dynamic_cast<Robot *>(stalkedObject)->setRadius(radius->text().toDouble());
}

void ParamWidget::setAngle() {
    if (stalkedObject)
        stalkedObject->setRotation(angle->text().toDouble());
}

void ParamWidget::setSize() {
    if (stalkedObject)
        dynamic_cast<Obstacle *>(stalkedObject)->setRect(0, 0, size->text().toDouble(), size->text().toDouble());
}
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
    hide();
    if (!stalkedObject)
        disconnect(dynamic_cast<AutoRobot *>(stalkedObject), &AutoRobot::paramsUpdated, this, &ParamWidget::updateAutoRobot);
    stalkedObject = robot;
    connect(robot, &AutoRobot::paramsUpdated, this, &ParamWidget::updateAutoRobot);
    show(robot);
    updateAutoRobot();
}

void ParamWidget::stalk(Obstacle *obstacle) {
    hide();
    if (!stalkedObject)
        disconnect(dynamic_cast<Obstacle *>(stalkedObject), &Obstacle::paramsUpdated, this, &ParamWidget::updateObstacle);
    stalkedObject = obstacle;
    connect(obstacle, &Obstacle::paramsUpdated, this, &ParamWidget::updateObstacle);
    show(obstacle);
    updateObstacle();
}

void ParamWidget::stalk(Robot *robot) {
    hide();
    if (!stalkedObject)
        disconnect(dynamic_cast<Robot *>(stalkedObject), &Robot::paramsUpdated, this, &ParamWidget::updateRobot);
    stalkedObject = robot;
    connect(robot, &Robot::paramsUpdated, this, &ParamWidget::updateRobot);
    show(robot);
    updateRobot();
}

void ParamWidget::stopStalking() {
    stalkedObject = nullptr;
    hide();
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
        direction->setText(QString::number(robot->getRotationDirection()));
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
        dynamic_cast<AutoRobot *>(stalkedObject)->setRotationDirection(static_cast<Robot::RotationDirection>(direction->text().toInt()));
}

void ParamWidget::setSpeed() {
    if (stalkedObject)
        dynamic_cast<Robot *>(stalkedObject)->setMoveSpeed(speed->text().toDouble());
}

void ParamWidget::setRadius() {
    if (stalkedObject)
        dynamic_cast<Robot *>(stalkedObject)->setRect(0, 0, radius->text().toDouble(), radius->text().toDouble());
}

void ParamWidget::setAngle() {
    if (stalkedObject)
        dynamic_cast<Robot *>(stalkedObject)->setRotation(angle->text().toDouble());
}

void ParamWidget::setSize() {
    if (stalkedObject)
        dynamic_cast<Obstacle *>(stalkedObject)->setRect(0, 0, size->text().toDouble(), size->text().toDouble());
}
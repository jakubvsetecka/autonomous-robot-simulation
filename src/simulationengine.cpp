#include "simulationengine.hpp"

qreal SimulationEngine::timeConstant = 0.5;

SimulationEngine::SimulationEngine(QObject *parent, int fps, int simulationSpeed) : QGraphicsScene(parent)
{
    // Set the frame rate and simulation speed
    this->fps = fps;
    this->simulationSpeed = simulationSpeed;

    // Set the background color
    setBackgroundBrush(QBrush(Qt::white));

    // Set the static time constant
    SimulationEngine::timeConstant = getFrameTime() * simulationSpeed;

    // Testing obsacle
    // QGraphicsRectItem *rectangl = addRect(100, 200, 100, 100, QPen(Qt::blue));
    // rectangl->setBrush(QBrush(Qt::blue));
    // rectangl->setTransformOriginPoint(rectangl->rect().width() / 2, rectangl->rect().height() / 2);
    // rectangl->setRotation(45);

    // rectangl = addRect(350, 200, 100, 100, QPen(Qt::blue));
    // rectangl->setBrush(QBrush(Qt::blue));

    // Create a robot and set it as the controlled robot
    Robot *robutek = new Robot();
    robutek->setPos(100, 100);
    setControlledRobot(robutek);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            AutoRobot *samorobutek = new AutoRobot(nullptr, 50, Robot::RotationDirection::Right, 5, 5);
            samorobutek->setPos(300 + i * 50, 300 + j * 50);
            addItem(samorobutek);
        }
    }
}

SimulationEngine::~SimulationEngine() {}

int SimulationEngine::getFPS() { return fps; }

int SimulationEngine::getFrameTime() { return 1000 / fps; }

qreal SimulationEngine::getSimulationSpeed() { return simulationSpeed; }

Robot *SimulationEngine::getControlledRobot() { return controlledRobot; }

void SimulationEngine::setControlledRobot(Robot *robot)
{
    controlledRobot = robot;
    addItem(controlledRobot);
}
#include "simulationengine.hpp"
#include "obstacle.hpp"

qreal SimulationEngine::timeConstant = 0.5;

SimulationEngine::SimulationEngine(QObject *parent, int fps, int simulationSpeed)
    : QGraphicsScene(parent)
{
    // Set the frame rate and simulation speed
    this->fps = fps;
    this->simulationSpeed = simulationSpeed;

    // Set the background color
    setBackgroundBrush(QBrush(Qt::white));

    // Set the static time constant
    SimulationEngine::timeConstant = getFrameTime() * simulationSpeed;

    // // Create a robot and set it as the controlled robot
    // Robot *robutek = new Robot();
    // robutek->setPos(100, 100);
    // setControlledRobot(robutek);

    // for (int i = 0; i < 10; i++)
    // {
    //     for (int j = 0; j < 10; j++)
    //     {
    // Add an autonomous robot
    AutoRobot *autoRobot = new AutoRobot(nullptr, 10, Robot::RotationDirection::Right, 7, 1);
    autoRobot->setPos(1 * 50, 1 * 50);
    addItem(autoRobot);
    //     }
    // }
}

SimulationEngine::~SimulationEngine() {}

int SimulationEngine::getFPS()
{
    return fps;
}

int SimulationEngine::getFrameTime()
{
    return 1000 / fps;
}

qreal SimulationEngine::getSimulationSpeed()
{
    return simulationSpeed;
}

Robot *SimulationEngine::getControlledRobot()
{
    return controlledRobot;
}

void SimulationEngine::setControlledRobot(Robot *robot)
{
    controlledRobot = robot;
    addItem(controlledRobot);
}

void SimulationEngine::addObstacle()
{
    Obstacle *obstacle = new Obstacle();
    addItem(obstacle);
}

void SimulationEngine::addAutoRobot()
{
    AutoRobot *autoRobot = new AutoRobot(nullptr, 10, Robot::RotationDirection::Right, 7, 1);
    addItem(autoRobot);
}

void SimulationEngine::addControlledRobot()
{
    Robot *robot = new Robot();
    setControlledRobot(robot);
}
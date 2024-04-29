#include "simulationengine.hpp"
#include "obstacle.hpp"

SimulationEngine::SimulationEngine(QObject *parent, int fps, qreal simulationSpeed)
    : QGraphicsScene(parent)
{
    // Set the frame rate and simulation speed
    setFPS(fps);
    setSimulationSpeed(simulationSpeed);

    // Set the background color
    setBackgroundBrush(QBrush(Qt::white));

    // Create a robot and set it as the controlled robot
    Robot *robutek = new Robot(nullptr, &timeConstant);
    robutek->setPos(12.5, 12.5);
    setControlledRobot(robutek);

    AutoRobot *samorobutek = new AutoRobot(nullptr, 10, Robot::RotationDirection::Right, 1, 1, &timeConstant);
    samorobutek->setPos(110, 100);
    addItem(samorobutek);

    AutoRobot *druhy_samorobutek = new AutoRobot(nullptr, 10, Robot::RotationDirection::Right, 1, 1, &timeConstant);
    druhy_samorobutek->setPos(100, 100);
    addItem(druhy_samorobutek);

    // // Add an autonomous robot
    // for (int i = 0; i < 1; i++)
    // {
    //     for (int j = 0; j < 1; j++)
    //     {
    //         AutoRobot *samorobutek = new AutoRobot(nullptr, 10, Robot::RotationDirection::Right, 7, 1, &timeConstant);
    //         samorobutek->setPos(150 + i * 10, 150 + j * 10);
    //         addItem(samorobutek);
    //     }
    // }
}

SimulationEngine::~SimulationEngine() {}

int SimulationEngine::getFPS()
{
    return fps;
}

void SimulationEngine::setFPS(int fps)
{
    this->fps = fps;
    updateTimeConstant();
}

int SimulationEngine::getFrameTime()
{
    return 1000 / fps;
}

qreal SimulationEngine::getSimulationSpeed()
{
    return simulationSpeed;
}

void SimulationEngine::setSimulationSpeed(qreal speed)
{
    simulationSpeed = speed;
    updateTimeConstant();
}

void SimulationEngine::updateTimeConstant()
{
    timeConstant = 1000 / getFPS() * simulationSpeed;
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
#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QGraphicsScene>
#include "robot.hpp"
#include "autorobot.hpp"

class SimulationEngine : public QGraphicsScene
{
public:
    /** A static time constant for the simulation engine. */
    static qreal timeConstant;

    SimulationEngine(QObject *parent = nullptr, int fps = 60, int simulationSpeed = 1) : QGraphicsScene(parent)
    {
        // Set the frame rate and simulation speed
        this->fps = fps;
        this->simulationSpeed = simulationSpeed;

        // Set the static time constant
        SimulationEngine::timeConstant = getFrameTime() * simulationSpeed;

        // Testing obsacle
        QGraphicsRectItem *rectangl = addRect(100, 200, 100, 100, QPen(Qt::blue));
        rectangl->setBrush(QBrush(Qt::blue));
        rectangl->setTransformOriginPoint(rectangl->rect().width() / 2, rectangl->rect().height() / 2);
        rectangl->setRotation(45);

        // Create a robot and set it as the controlled robot
        Robot *robutek = new Robot();
        robutek->setPos(100, 100);
        setControlledRobot(robutek);

        // Add an autonomous robot
        AutoRobot *samorobutek = new AutoRobot();
        samorobutek->setPos(150, 150);
        addItem(samorobutek);
    }

    ~SimulationEngine() {}

    /**
     * @brief Simulation Frames-Per-Second getter.
     *
     */
    int getFPS() { return fps; }

    /**
     * @brief Get the time it takes to render a single frame.
     */
    int getFrameTime() { return 1000 / fps; }

    /**
     * @brief Get the simulation speed.
     */
    qreal getSimulationSpeed() { return simulationSpeed; }

    Robot *getControlledRobot() { return controlledRobot; }
    void setControlledRobot(Robot *robot)
    {
        controlledRobot = robot;
        addItem(controlledRobot);
    }

private:
    /** The frames per second of the simulation engine. */
    int fps = 60;
    /** The speed of the simulation engine. */
    qreal simulationSpeed = 0.1;

    Robot *controlledRobot = nullptr;
};

#endif // SIMULATIONENGINE_H
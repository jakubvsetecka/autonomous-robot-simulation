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

    SimulationEngine(QObject *parent = nullptr, int fps = 60, int simulationSpeed = 1);

    ~SimulationEngine();

    /**
     * @brief Simulation Frames-Per-Second getter.
     *
     */
    int getFPS();

    /**
     * @brief Get the time it takes to render a single frame.
     */
    int getFrameTime();

    /**
     * @brief Get the simulation speed.
     */
    qreal getSimulationSpeed();

    Robot *getControlledRobot();
    void setControlledRobot(Robot *robot);

private:
    /** The frames per second of the simulation engine. */
    int fps = 60;
    /** The speed of the simulation engine. */
    qreal simulationSpeed = 0.1;

    Robot *controlledRobot = nullptr;
};

#endif // SIMULATIONENGINE_H
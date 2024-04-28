#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QGraphicsScene>
#include "robutek.hpp"

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

    Robutek *getControlledRobot() { return controlledRobot; }
    void setControlledRobot(Robutek *robot)
    {
        controlledRobot = robot;
        addItem(controlledRobot);
    }

private:
    /** The frames per second of the simulation engine. */
    int fps = 60;
    /** The speed of the simulation engine. */
    qreal simulationSpeed = 0.1;

    Robutek *controlledRobot = nullptr;
};

#endif // SIMULATIONENGINE_H
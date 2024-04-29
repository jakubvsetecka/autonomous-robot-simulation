#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include "autorobot.hpp"
#include "robot.hpp"
#include <QGraphicsScene>

class SimulationEngine : public QGraphicsScene
{
public:
    SimulationEngine(QObject *parent = nullptr, int fps = 60, qreal simulationSpeed = 1.0 / 16.0);

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
     * @brief Set the simulation Frames-Per-Second.
     *
     * @param fps
     */
    void setFPS(int fps);

    /**
     * @brief Get the simulation speed.
     */
    qreal getSimulationSpeed();

    /**
     * @brief Set the simulation speed.
     *
     * @param speed
     */
    void setSimulationSpeed(qreal speed);

    /**
     * @brief Update the time constant.
     */
    void updateTimeConstant();

    /**
     * @brief Get the time constant pointer.
     *
     * @return qreal*
     */
    qreal *getTimeConstant();

    /**
     * @brief Add obstacle to the scene.
     */
    void addObstacle();

    void addAutoRobot();

    void addControlledRobot();

    Robot *getControlledRobot();
    void setControlledRobot(Robot *robot);

private:
    /** The frames per second of the simulation engine. */
    int fps = 60;
    /** The speed of the simulation engine. */
    qreal simulationSpeed = 1;

    qreal *timeConstant = nullptr;

    Robot *controlledRobot = nullptr;
};

#endif // SIMULATIONENGINE_H
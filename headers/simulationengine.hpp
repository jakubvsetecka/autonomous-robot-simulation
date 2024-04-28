#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include "autorobot.hpp"
#include "robot.hpp"
#include <QGraphicsScene>

class SimulationEngine : public QGraphicsScene {
  public:
    GameObject *dragDeezNuts = nullptr;

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

    /**
     * @brief Add obstacle to the scene.
     */
    void addObstacle();

    void addAutoRobot();

    void addControlledRobot();

    Robot *getControlledRobot();
    void setControlledRobot(Robot *robot);
    void followCursor(QPointF pos);

  private:
    /** The frames per second of the simulation engine. */
    int fps = 60;
    /** The speed of the simulation engine. */
    qreal simulationSpeed = 0.1;

    Robot *controlledRobot = nullptr;
};

#endif // SIMULATIONENGINE_H
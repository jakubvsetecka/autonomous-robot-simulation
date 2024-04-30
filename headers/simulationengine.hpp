#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include "autorobot.hpp"
#include "gameobject.hpp"
#include "robot.hpp"
#include <QGraphicsScene>
#include <QJsonArray>
#include <QJsonDocument>

class SimulationEngine : public QGraphicsScene {
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
     *
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

    bool isInsideScene(const QPointF &point) const;

    Robot *getControlledRobot();
    void setControlledRobot(Robot *robot);

    bool saveSimulation();
    bool loadSimulation();

    void read(const QJsonObject &json);
    QJsonObject toJson() const;

  private:
    /** The frames per second of the simulation engine. */
    int fps = 60;
    /** The speed of the simulation engine. */
    qreal simulationSpeed = 1;

    qreal timeConstant = 1;

    Robot *controlledRobot = nullptr;
};

#endif // SIMULATIONENGINE_H
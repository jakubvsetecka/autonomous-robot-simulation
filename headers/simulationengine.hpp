/**
 * @file simulationengine.hpp
 * @brief This file contains the declaration of the SimulationEngine class.
 * @details It is a subclass of the QGraphicsScene class and represents the simulation engine.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

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
     * @return int
     */
    int getFPS();

    /**
     * @brief Get the time it takes to render a single frame.
     * @return int
     */
    int getFrameTime();

    /**
     * @brief Set the simulation Frames-Per-Second.
     * @param fps
     */
    void setFPS(int fps);

    /**
     * @brief Get the simulation speed.
     * @return qreal
     */
    qreal getSimulationSpeed();

    /**
     * @brief Set the simulation speed.
     * @param speed
     * @return void
     */
    void setSimulationSpeed(qreal speed);

    /**
     * @brief Update the time constant.
     * @return void
     */
    void updateTimeConstant();

    /**
     * @brief Get the time constant pointer.
     * @return qreal*
     */
    qreal *getTimeConstant();

    /**
     * @brief Check if a point is inside the scene.
     * @param point
     * @return bool
     */
    bool isInsideScene(const QPointF &point) const;

    /**
     * @brief Get the robot that is currently being controlled.
     * @return Robot*
     */
    Robot *getControlledRobot();

    /**
     * @brief Set the robot that is currently being controlled.
     * @param robot
     * @return void
     */
    void setControlledRobot(Robot *robot);

    /**
     * @brief Save the simulation.
     * @param filename The name of the file to save the simulation to.
     * @details The file will be saved in the JSON format in folder "simulations"
     * @return void
     */
    bool saveSimulation(const QString &filename = "simulation");

    /**
     * @brief Load the simulation.
     * @param filename The name of the file to load the simulation from.
     * @details The file will be loaded from the JSON format from folders "simulations" and "exmaples"
     * @return void
     */
    bool loadSimulation(QString filename = "simulation");

    /**
     * @brief Read the simulation from a JSON object.
     * @param json The JSON object to read.
     * @return void
     */
    void read(const QJsonObject &json);

    /**
     * @brief Convert the simulation to a JSON object.
     * @return QJsonObject
     */
    QJsonObject toJson() const;

    /**
     * @brief Clear the scene.
     *
     */
    void clearScene();

  private:
    /** The frames per second of the simulation engine. */
    int fps = 60;
    /** The speed of the simulation engine. */
    qreal simulationSpeed = 1;

    /** The time constant of the simulation engine. */
    qreal timeConstant = 1;

    /** The robot that is currently being controlled. */
    Robot *controlledRobot = nullptr;
};

#endif // SIMULATIONENGINE_H
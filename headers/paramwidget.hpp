/**
 * @file paramwidget.hpp
 * @brief This file contains the declaration of the ParamWidget class.
 * @details It is a subclass of the QWidget class and represents a widget for editing parameters of game objects.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 03.05.2024
 */

#ifndef PARAMWIDGET_HPP
#define PARAMWIDGET_HPP

#include "autorobot.hpp"
#include "gameobject.hpp"
#include "obstacle.hpp"
#include "parameditline.hpp"
#include "robot.hpp"
#include <QCheckBox>
#include <QDoubleValidator>
#include <QLabel>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

/**
 * @class ParamWidget
 * @brief A class to represent a widget for editing parameters of game objects.
 * @details This class inherits from QWidget and provides a widget for editing parameters of game objects.
 * @see QWidget
 */
class ParamWidget : public QWidget {
    Q_OBJECT

  public:
    /**
     * @brief Default constructor.
     * @param parent The parent widget.
     */
    explicit ParamWidget(QWidget *parent = nullptr);

    /**
     * @brief Set the game object whose parameters will be displayed.
     * @param object The game object.
     * @return void
     */
    void stalk(AutoRobot *robot);

    /**
     * @brief Set the game object whose parameters will be displayed.
     * @param object The game object.
     * @return void
     */
    void stalk(Obstacle *obstacle);

    /**
     * @brief Set the game object whose parameters will be displayed.
     * @param object The game object.
     * @return void
     */
    void stalk(Robot *robot);

    /**
     * @brief Stop editing the parameters of the game object.
     * @return void
     */
    void stopStalking();

  private:
    /** @brief The layout of the widget. */
    QVBoxLayout *layout;

    /** @brief The game object whose parameters are being displayed. */
    GameObject *stalkedObject = nullptr;

    /** @brief Whether the widget should keep updating the parameters of the game object. */
    bool keepUpdating = true;

    /** @brief The validator for the number input. */
    QDoubleValidator *numberValidator;

    /** @brief The labels and line edit widgets for editing the parameters. */
    QLabel *labelDetectionDistance;
    ParamEditLine *detectionDistance;
    QLabel *labelAngleToRotate;
    ParamEditLine *angleToRotate;
    QLabel *labelDirection;
    QCheckBox *direction;
    QLabel *labelSpeed;
    ParamEditLine *speed;
    QLabel *labelRadius;
    ParamEditLine *radius;
    QLabel *labelAngle;
    ParamEditLine *angle;
    QLabel *labelSize;
    ParamEditLine *size;

    /**
     * @brief Set up the line edit widget for editing a parameter.
     * @param lineEdit The line edit widget.
     * @param label The label for the line edit widget.
     * @return void
     */
    void setUpEditLine(ParamEditLine *lineEdit, QLabel *label);

    /**
     * @brief Show the parameters of the game object.
     * @param robot The robot whose parameters will be displayed.
     * @return void
     */
    void show(Robot *robot);

    /**
     * @brief Show the parameters of the game object.
     * @param robot The robot whose parameters will be displayed.
     * @return void
     */
    void show(AutoRobot *robot);

    /**
     * @brief Show the parameters of the game object.
     * @param obstacle The obstacle whose parameters will be displayed.
     * @return void
     */
    void show(Obstacle *obstacle);

    /**
     * @brief Hide the widget.
     * @return void
     */
    void hide();

    /**
     * @brief Disconnect the widget from the game object.
     * @return void
     */
    void disconnectStalkedObject();

  private slots:
    /**
     * @brief Signal to set the detection distance of the game object.
     * @return void
     */
    void setDetectionDistance();

    /**
     * @brief Signal to set the angle to rotate of the game object.
     * @return void
     */
    void setAngleToRotate();

    /**
     * @brief Signal to set the direction of the game object.
     * @return void
     */
    void setDirection();

    /**
     * @brief Signal to set the speed of the game object.
     * @return void
     */
    void setSpeed();

    /**
     * @brief Signal to set the radius of the game object.
     * @return void
     */
    void setRadius();

    /**
     * @brief Signal to set the angle of the game object.
     * @return void
     */
    void setAngle();

    /**
     * @brief Signal to set the size of the game object.
     * @return void
     */
    void setSize();

    /**
     * @brief Signal to update the parameters of the game object.
     * @return void
     */
    inline void focusIn() { keepUpdating = false; }

    /**
     * @brief Signal to update the parameters of the game object.
     * @return void
     */
    inline void focusOut() { keepUpdating = true; }

    /**
     * @brief Update the parameters of the game object.
     * @return void
     */
    void updateAutoRobot();

    /**
     * @brief Update the parameters of the game object.
     * @return void
     */
    void updateObstacle();

    /**
     * @brief Update the parameters of the game object.
     * @return void
     */
    void updateRobot();
};

#endif // PARAMWIDGET_HPP
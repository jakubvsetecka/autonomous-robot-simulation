// mainwindow.cpp

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "autonomousrobot.h"
#include "controlledrobot.h"
#include "gameobject.h"
#include "obstacle.h"
#include "simulation.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    simulation = new Simulation(scene);

    Obstacle *obstacle = new Obstacle(NULL, QPointF(200, 50), QPointF(50, 100), 0);
    simulation->addObject(obstacle);

    AutonomousRobot *autonomousRobot = new AutonomousRobot(NULL, QPointF(50, 50), QPointF(50, 50), 0, 1);
    simulation->addObject(autonomousRobot);

    // ControlledRobot *controlledRobot = new ControlledRobot();
    // simulation->addObject(controlledRobot);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateAnimation);
    timer->start(16);

    // Connect the button click signal to the appropriate slot
    connect(ui->addObstacleButton, &QPushButton::clicked, this, &MainWindow::onAddObstacleClicked);
}

void MainWindow::onAddObstacleClicked() {
    // Create a new obstacle
    int posx = rand() % 1000 - 500;
    int posy = rand() % 1000 - 500;
    int size = rand() % 50;
    Obstacle *obstacle = new Obstacle(NULL, QPointF(posx, posy), QPointF(size, size), rand() % 360);
    simulation->addObject(obstacle);
    // Here you need to specify how to add this to your scene or simulation
    // Example: simulation->addObject(obstacle); or scene->addItem(obstacle);
    // Make sure you have access to your QGraphicsScene or Simulation class instance here
}

void MainWindow::updateAnimation() {
    simulation->updateObjects();
}

MainWindow::~MainWindow() {
    delete ui;
}

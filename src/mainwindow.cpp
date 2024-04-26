// mainwindow.cpp

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "objects.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    Obstacle *obstacle = new Obstacle(NULL, QPointF(50, 50), QPointF(50, 50), 0);
    scene->addItem(obstacle);
    obstacle->setPos(50, 50);

    AutonomousRobot *autonomousRobot = new AutonomousRobot(NULL, QPointF(50, 50), QPointF(50, 50), 5.0, 0.1);
    scene->addItem(autonomousRobot);
    autonomousRobot->setPos(100, 100);

    ControlledRobot *controlledRobot = new ControlledRobot();
    scene->addItem(controlledRobot);
    controlledRobot->setPos(150, 150);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateAnimation);
    timer->start(16);

    // Connect the button click signal to the appropriate slot
    connect(ui->addObstacleButton, &QPushButton::clicked, this, &MainWindow::onAddObstacleClicked);
}

void MainWindow::onAddObstacleClicked() {
    // Create a new obstacle
    Obstacle *obstacle = new Obstacle();
    scene->addItem(obstacle);
    // Here you need to specify how to add this to your scene or simulation
    // Example: simulation->addObject(obstacle); or scene->addItem(obstacle);
    // Make sure you have access to your QGraphicsScene or Simulation class instance here
}

void MainWindow::updateAnimation() {
    QGraphicsScene *scene = ui->graphicsView->scene();
    for (QGraphicsItem *item : scene->items()) {
        GameObject *gameObject = dynamic_cast<GameObject *>(item);
        if (gameObject) {
            gameObject->update();
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

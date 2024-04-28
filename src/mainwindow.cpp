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
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus); // Set the focus policy to accept key events
    setFocus();                      // Set the focus to the main window

    simulationEngine = new SimulationEngine(this);
    ui->graphicsView->setScene(simulationEngine);
    ui->graphicsView->resetTransform();
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    ui->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

    // Set the alignment to ensure (0, 0) is at the top-left corner
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Set the initial scene rectangle
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());

    QGraphicsRectItem *rectangl = simulationEngine->addRect(100, 200, 100, 100, QPen(Qt::blue));
    rectangl->setBrush(QBrush(Qt::blue));
    rectangl->setTransformOriginPoint(rectangl->rect().width() / 2, rectangl->rect().height() / 2);
    rectangl->setRotation(45);

    // rectangl = simulationEngine->addRect(400, 100, 100, 100, QPen(Qt::blue));
    // rectangl->setRotation(45);
    // rectangl->setBrush(QBrush(Qt::blue));

    // rectangl = simulationEngine->addRect(300, 200, 100, 100, QPen(Qt::blue));
    // rectangl->setRotation(45);
    // rectangl->setBrush(QBrush(Qt::blue));

    Robutek *robutek = new Robutek();
    robutek->setPos(100, 100);
    simulationEngine->setControlledRobot(robutek);

    Samorobutek *samorobutek = new Samorobutek();
    samorobutek->setPos(150, 150);
    simulationEngine->addItem(samorobutek);

    // simulation = new Simulation(scene);

    // Obstacle *obstacle = new Obstacle(NULL, QPointF(200, 50), QPointF(50, 100), 0);
    // simulation->addObject(obstacle);

    // // AutonomousRobot *autonomousRobot = new AutonomousRobot(NULL, QPointF(50, 50), QPointF(50, 50), 0, 1);
    // // simulation->addObject(autonomousRobot);

    // ControlledRobot *controlledRobot = new ControlledRobot();
    // simulation->addObject(controlledRobot);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateAnimation);
    timer->start(simulationEngine->getFrameTime());

    // Connect the button click signal to the appropriate slot
    connect(ui->addObstacleButton, &QPushButton::clicked, this, &MainWindow::onAddObstacleClicked);
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    // Update the scene rect to match the new viewport size
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (simulationEngine->getControlledRobot() == nullptr)
    {
        QMainWindow::keyPressEvent(event); // Pass the unhandled keys to the base class
        return;
    }

    switch (event->key())
    {
    case Qt::Key_Up:
        simulationEngine->getControlledRobot()->startMoving();
        break;
    case Qt::Key_Left:
        // Rotate left
        simulationEngine->getControlledRobot()->startRotating(Robutek::RotationDirection::Left);
        break;
    case Qt::Key_Right:
        // Rotate right
        simulationEngine->getControlledRobot()->startRotating(Robutek::RotationDirection::Right);
        break;
    default:
        QMainWindow::keyPressEvent(event); // Pass the unhandled keys to the base class
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (simulationEngine->getControlledRobot() == nullptr)
    {
        QMainWindow::keyReleaseEvent(event); // Pass the unhandled keys to the base class
        return;
    }

    switch (event->key())
    {
    case Qt::Key_Up:
        simulationEngine->getControlledRobot()->stopMoving();
        break;
    case Qt::Key_Left:
        simulationEngine->getControlledRobot()->stopRotating();
        break;
    case Qt::Key_Right:
        simulationEngine->getControlledRobot()->stopRotating();
        break;
    default:
        QMainWindow::keyReleaseEvent(event); // Pass the unhandled keys to the base class
    }
}

void MainWindow::onAddObstacleClicked()
{
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

void MainWindow::updateAnimation()
{
    Robutek *controlledRobot = simulationEngine->getControlledRobot();
    if (controlledRobot != nullptr)
    {
        controlledRobot->move();
    }

    for (QGraphicsItem *item : simulationEngine->items())
    {
        Robutek *robutek = dynamic_cast<Robutek *>(item);
        if (robutek != nullptr && robutek != controlledRobot)
        {
            robutek->move();
        }
    }

    // simulation->updateObjects();
    // simulationEngine->getControlledRobot()->move(SimulationEngine::timeConstant);
    // simulationEngine->getControlledRobot()->setRotation(simulationEngine->getControlledRobot()->rotation() + 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

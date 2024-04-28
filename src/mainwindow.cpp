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

    simulationEngine = new SimulationEngine(this);
    ui->graphicsView->setScene(simulationEngine);
    ui->graphicsView->resetTransform();
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    ui->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

    // Set the alignment to ensure (0, 0) is at the top-left corner
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Set the initial scene rectangle
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());

    Robutek *robutek = new Robutek();
    robutek->setPos(100, 100);
    simulationEngine->setControlledRobot(robutek);

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
    drawGrid(); // Draw the grid after setting the scene rect
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    // Update the scene rect to match the new viewport size
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
    drawGrid();
}

void MainWindow::drawGrid()
{
    const int gridSpacing = 100;        // Grid spacing in pixels
    QPen pen(Qt::gray, 0, Qt::DotLine); // Pen for the grid lines

    // Clear previous grid lines if they exist
    foreach (QGraphicsItem *item, simulationEngine->items())
    {
        if (item->data(0) == "gridLine")
        {
            simulationEngine->removeItem(item);
            delete item;
        }
    }

    // Get the current size of the scene
    QRectF rect = simulationEngine->sceneRect();

    // Draw vertical lines
    for (double x = rect.left(); x <= rect.right(); x += gridSpacing)
    {
        QGraphicsLineItem *line = simulationEngine->addLine(x, rect.top(), x, rect.bottom(), pen);
        line->setData(0, "gridLine");
    }

    // Draw horizontal lines
    for (double y = rect.top(); y <= rect.bottom(); y += gridSpacing)
    {
        QGraphicsLineItem *line = simulationEngine->addLine(rect.left(), y, rect.right(), y, pen);
        line->setData(0, "gridLine");
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
    // simulation->updateObjects();
    simulationEngine->getControlledRobot()->move(SimulationEngine::timeConstant);
    simulationEngine->getControlledRobot()->setRotation(simulationEngine->getControlledRobot()->rotation() + 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

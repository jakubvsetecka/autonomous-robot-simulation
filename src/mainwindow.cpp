// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus); // Set the focus policy to accept key events
    setFocus();                      // Set the focus to the main window

    // Initialize the simulation engine
    simulationEngine = new SimulationEngine(this);

    // Set the scene to the simulation engine
    ui->graphicsView->setScene(simulationEngine);

    // Make the scene solid in place and the origin at the top-left corner
    ui->graphicsView->resetTransform();
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
    ui->graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

    // Set the alignment to ensure (0, 0) is at the top-left corner
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Set the initial scene rectangle
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());

    // Setup the animation loop
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateAnimation);
    timer->start(simulationEngine->getFrameTime());

    // Connect the button click signal to the appropriate slot
    connect(ui->addObstacleButton, &QPushButton::clicked, this, &MainWindow::onAddObstacleClicked);
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    // Update the scene rect to match the viewport size
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
        // Move forward
        simulationEngine->getControlledRobot()->startMoving();
        break;
    case Qt::Key_Left:
        // Rotate left
        simulationEngine->getControlledRobot()->startRotating(Robot::RotationDirection::Left);
        break;
    case Qt::Key_Right:
        // Rotate right
        simulationEngine->getControlledRobot()->startRotating(Robot::RotationDirection::Right);
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
        // Stop moving
        simulationEngine->getControlledRobot()->stopMoving();
        break;
    case Qt::Key_Left:
        // Stop rotating
        simulationEngine->getControlledRobot()->stopRotating();
        break;
    case Qt::Key_Right:
        // Stop rotating
        simulationEngine->getControlledRobot()->stopRotating();
        break;
    default:
        QMainWindow::keyReleaseEvent(event); // Pass the unhandled keys to the base class
    }
}

void MainWindow::onAddObstacleClicked()
{
    // TODO: add obstacle to the scene
}

void MainWindow::updateAnimation()
{
    for (QGraphicsItem *item : simulationEngine->items())
    {
        Robot *robutek = dynamic_cast<Robot *>(item);
        if (robutek != nullptr)
        {
            robutek->move();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// mainwindow.cpp

#include "mainwindow.h"
#include "obstacle.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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

    // Create the overlay widget
    overlay = new OverlayWidget(this, simulationEngine, ui->graphicsView);
    overlay->setGeometry(rect());
    ui->expWidget->autoButton->overlay = overlay;
    ui->expWidget->controlButton->overlay = overlay;
    ui->expWidget->obstacleButton->overlay = overlay;

    expandableWidget = ui->expWidget;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event); // Call the base class implementation
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
    // if (overlay) {
    //     overlay->setGeometry(centralWidget()->geometry());
    // }
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    // Update the scene rect to match the viewport size
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (simulationEngine->getControlledRobot() == nullptr) {
        QMainWindow::keyPressEvent(event); // Pass the unhandled keys to the base class
        return;
    }

    switch (event->key()) {
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

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (simulationEngine->getControlledRobot() == nullptr) {
        QMainWindow::keyReleaseEvent(event); // Pass the unhandled keys to the base class
        return;
    }

    switch (event->key()) {
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

void MainWindow::onAddObstacleClicked() {
    qDebug() << "Add Obstacle Clicked";
}

void MainWindow::onAddAutoRobotClicked() {
}

void MainWindow::onAddControlledRobotClicked() {
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Handle widget
    qDebug() << "Mouse Press Event";
    if (!expandableWidget->geometry().contains(event->pos())) {
        expandableWidget->collapse();
    } else {
        QMainWindow::mousePressEvent(event);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint localPos = ui->graphicsView->mapFromParent(event->pos());
    QPointF scenePos = ui->graphicsView->mapToScene(localPos);
    qDebug() << "Mouse Move Event in Scene at position:" << scenePos;

    // Call the base class implementation if you're not fully handling the event yourself
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    // qDebug() << "Mouse Release Event";
    //  simulationEngine->dragDeezNuts = nullptr;
    QMainWindow::mouseReleaseEvent(event);
    // ... your code ...
}

void MainWindow::updateAnimation() {
    for (QGraphicsItem *item : simulationEngine->items()) {
        Robot *robutek = dynamic_cast<Robot *>(item);
        if (robutek != nullptr) {
            robutek->move();
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @file mainwindow.cpp
 * @brief This file contains the implementation of the MainWindow class.
 * @details It is a subclass of the QMainWindow class and represents the main window of the application.
 * @authors Tomáš Hobza, Jakub Všetečka
 * @date 02.05.2024
 */

#include "mainwindow.h"
#include "obstacle.hpp"
#include "ui_mainwindow.h"
#include <QKeyEvent> // Include the necessary header file
#include <qdir.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus); // Set the focus policy to accept key events
    setFocus();                      // Set the focus to the main window

    // int fps = 60, qreal simulationSpeed = 1.0 / 16.0
    const int FPS = 60;
    const qreal SIMULATION_SPEED = 4.0 / 16.0;

    // Initialize the simulation engine
    simulationEngine = new SimulationEngine(this, FPS, SIMULATION_SPEED);
    ui->horizontalSlider->setValue(SIMULATION_SPEED * 100);

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
    ui->expWidget->setOverlay(overlay);

    expandableWidget = ui->expWidget;

    ui->graphicsView->viewport()->installEventFilter(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveSimulation);

    listWidget = new QListWidget(this);
    listWidget->setFixedWidth(ui->horizontalSlider->width());
    listWidget->hide();
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::toggleList);
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::handleItemDoubleClick);

    connect(ui->goLeft, &QPushButton::pressed, this, &MainWindow::goLeft);
    connect(ui->goLeft, &QPushButton::released, this, &MainWindow::stopRotating);
    connect(ui->goRight, &QPushButton::pressed, this, &MainWindow::goRight);
    connect(ui->goRight, &QPushButton::released, this, &MainWindow::stopRotating);
    connect(ui->goStraight, &QPushButton::pressed, this, &MainWindow::goStraight);
    connect(ui->goStraight, &QPushButton::released, this, &MainWindow::stopMoving);
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (ui->graphicsView->viewport()) {
        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mEvent = (QMouseEvent *)event;
            mouseMoveEvent(mEvent);
        } else if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mEvent = (QMouseEvent *)event;
            mouseReleaseEvent(mEvent);
        }
    }
    return false;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event); // Call the base class implementation
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
    overlay->setGeometry(0, 0, width(), height());
    listWidget->setFixedWidth(ui->horizontalSlider->width());
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    // Update the scene rect to match the viewport size
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
    listWidget->setFixedWidth(ui->sideBar->geometry().width());
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Collapse the expandable widget
    expandableWidget->collapse();

    QPoint localPos = ui->graphicsView->mapFromParent(event->pos());
    QPointF scenePos = ui->graphicsView->mapToScene(localPos);
    QGraphicsItem *item = ui->graphicsView->itemAt(scenePos.toPoint());

    // Handle controlled robot
    if (Robot *r = simulationEngine->getControlledRobot()) {
        simulationEngine->setControlledRobot(nullptr);
        r->toggleActive();
    }
    if (item && item->type() == Robot::Type) {
        Robot *robot = dynamic_cast<Robot *>(item);
        if (robot->isActive()) {
            simulationEngine->setControlledRobot(nullptr);
        } else {
            simulationEngine->setControlledRobot(robot);
            connect(robot, &Robot::destroyed, this, [this]() { simulationEngine->setControlledRobot(nullptr); });
        }
        robot->toggleActive();
    }

    // Handle param widget
    if (item) {
        switch (item->type()) {
        case Obstacle::Type:
            ui->paramWidget->stalk(dynamic_cast<Obstacle *>(item));
            break;
        case Robot::Type:
            ui->paramWidget->stalk(dynamic_cast<Robot *>(item));
            break;
        case AutoRobot::Type:
            ui->paramWidget->stalk(dynamic_cast<AutoRobot *>(item));
            break;
        default:
            ui->paramWidget->stopStalking();
            break;
        }
    } else {
        ui->paramWidget->stopStalking();
    }

    overlay->trySetSail(event);

    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    overlay->navigateTheSea(event);
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    overlay->anchor();
    QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    // overlay->trySetSail(event);
    QMainWindow::mouseDoubleClickEvent(event);
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

void MainWindow::on_horizontalSlider_valueChanged(int value) {
    simulationEngine->setSimulationSpeed(value / 100.0);
}

void MainWindow::saveSimulation() {
    PopupSaveWindow popupWindow(this);

    float speed = simulationEngine->getSimulationSpeed();
    simulationEngine->setSimulationSpeed(0.0);
    ui->horizontalSlider->setValue(0);

    if (popupWindow.exec() == QDialog::Accepted) {
        // User accepted the dialog (e.g., clicked "Save")
        qDebug() << "Saving simulation...";
        simulationEngine->saveSimulation(popupWindow.getEnteredText());
    }
    // Restore the simulation speed
    simulationEngine->setSimulationSpeed(speed);
    ui->horizontalSlider->setValue(speed * 100);
}

void MainWindow::toggleList() {
    if (listWidget->isVisible()) {
        ui->sideBar->removeWidget(listWidget);
        listWidget->hide();
        listWidget->clear();
        ui->loadButton->setText("Load");
    } else {
        QDir directory("simulations");
        QStringList files = directory.entryList(QStringList() << "*.json", QDir::Files);

        foreach (QString filename, files) {
            // Remove .json
            filename.chop(5);
            listWidget->addItem(filename);
        }

        listWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        listWidget->setFixedWidth(ui->horizontalLayout->geometry().width());
        ui->sideBar->addWidget(listWidget);
        listWidget->show();
        ui->loadButton->setText("Load");
    }
}

void MainWindow::handleItemDoubleClick(QListWidgetItem *item) {
    simulationEngine->setSimulationSpeed(0.0);
    ui->horizontalSlider->setValue(0);
    simulationEngine->loadSimulation(item->text());
}
void MainWindow::on_pushButton_clicked() {
    simulationEngine->clearScene();
}

void MainWindow::goLeft() {
    if (Robot *r = simulationEngine->getControlledRobot())
        r->startRotating(Robot::RotationDirection::Left);
}

void MainWindow::stopRotating() {
    if (Robot *r = simulationEngine->getControlledRobot()) {
        r->stopRotating();
        r->setFocus();
    }
}
void MainWindow::goRight() {
    if (Robot *r = simulationEngine->getControlledRobot())
        r->startRotating(Robot::RotationDirection::Right);
}
void MainWindow::goStraight() {
    if (Robot *r = simulationEngine->getControlledRobot())
        r->startMoving();
}
void MainWindow::stopMoving() {
    if (Robot *r = simulationEngine->getControlledRobot()) {
        r->stopMoving();
        r->setFocus();
    }
}
// mainwindow.cpp

#include "mainwindow.h"
#include "obstacle.hpp"
#include "ui_mainwindow.h"

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
    ui->expWidget->autoButton->overlay = overlay;
    ui->expWidget->controlButton->overlay = overlay;
    ui->expWidget->obstacleButton->overlay = overlay;

    expandableWidget = ui->expWidget;

    ui->graphicsView->viewport()->installEventFilter(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveSimulation);
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
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    // Update the scene rect to match the viewport size
    simulationEngine->setSceneRect(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (!expandableWidget->geometry().contains(event->pos())) {
        expandableWidget->collapse();
    }
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
    overlay->trySetSail(event);
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
    qDebug() << "Simulation speed: " << value;
    simulationEngine->setSimulationSpeed(value / 100.0);
}

void MainWindow::loadSimulation() {
    // simulationEngine->loadSimulation();
}

void MainWindow::saveSimulation() {
    PopupSaveWindow popupWindow(this);

    float speed = simulationEngine->getSimulationSpeed();
    simulationEngine->setSimulationSpeed(0.0);

    if (popupWindow.exec() == QDialog::Accepted) {
        // User accepted the dialog (e.g., clicked "Save")
        qDebug() << "Saving simulation...";
        simulationEngine->saveSimulation(popupWindow.getEnteredText());
    } else {
        // Restore the simulation speed
        simulationEngine->setSimulationSpeed(speed);
    }
}
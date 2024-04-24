#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    square(nullptr) // Initialize the square pointer to null
{
    ui->setupUi(this);

    // Create a scene
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Initialize the square and add it to the scene
    square = scene->addRect(0, 0, 100, 100, QPen(Qt::black), QBrush(Qt::blue)); // Create and assign the square

    // Set up a timer for animation
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateAnimation);
    timer->start(16); // Roughly 60 FPS

    // Adjust view settings, if necessary
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::updateAnimation()
{
    int maxWidth = ui->graphicsView->viewport()->width();
    int maxHeight = ui->graphicsView->viewport()->height();

    // Example: Move the square diagonally
    if (square) { // Check if square is not null
        qreal x = square->x();
        qreal y = square->y();

        if ((x+square->boundingRect().width() >= maxWidth && square_velocity[0] > 0) || (x < 0 && square_velocity[0] < 0)) {
            square_velocity[0] = -square_velocity[0];
        }

        if ((y+square->boundingRect().height() >= maxHeight && square_velocity[1] > 0) || (y < 0 && square_velocity[1] < 0)) {
            square_velocity[1] = -square_velocity[1];
        }

        square->setPos(x+square_velocity[0], y+square_velocity[1]); // Update the square's position
    }

    // Add boundary checks or other animation logic as needed
}

MainWindow::~MainWindow()
{
    delete ui;
}



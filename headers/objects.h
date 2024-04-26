// objects.h

#include <QGraphicsItem>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPainter>
#include <cmath>

class AngleDirection {
  public:
    double angle;     // Angle in degrees or radians
    double magnitude; // Magnitude of the vector

    // Constructor
    AngleDirection(double angle = 0.0, double magnitude = 0.0)
        : angle(angle), magnitude(magnitude) {}

    // Convert to Cartesian coordinates
    double getX() const {
        return magnitude * cos(angle); // Assuming angle is in radians
    }

    double getY() const {
        return magnitude * sin(angle); // Assuming angle is in radians
    }

    // Other methods as needed, such as updating angle or magnitude, etc.
};

class GameObject : public QGraphicsItem {
  public:
    GameObject(QGraphicsItem *parent = nullptr, QPointF position = QPointF(-25, -25), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0)
        : QGraphicsItem(parent), position(position), angleDir(angle, velocity), dimension(dimension) {
        setTransformOriginPoint(boundingRect().center());
    }

    virtual ~GameObject() {}

    QRectF boundingRect() const override {
        return QRectF(position.x(), position.y(), dimension.x(), dimension.y());
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        QBrush brush(Qt::CrossPattern);
        painter->setBrush(brush);
        painter->drawRect(boundingRect());
    }

    virtual void update() {
        moveBy(angleDir.getX(), angleDir.getY());
        setRotation(angleDir.angle);
    }

    virtual QJsonValue toJson() const {
        // Convert object to JSON
    }

    static GameObject *fromJson(const QJsonObject &obj) {
        // Create object from JSON

    } // Static method returning a pointer

  protected:
    QPointF position;
    AngleDirection angleDir;
    QPointF dimension;
};

class Obstacle : public GameObject {
  public:
    Obstacle(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0)
        : GameObject(parent, position, dimension, angle, 0) {}

    void update() override {
        // Obstacles do not move
    }
};

class Robot : public GameObject {
  public:
    Robot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0)
        : GameObject(parent, position, dimension, angle, velocity) {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        QBrush brush(Qt::CrossPattern);
        painter->setBrush(brush);
        painter->drawEllipse(boundingRect());
    }
};

class AutonomousRobot : public Robot {
  public:
    AutonomousRobot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0)
        : Robot(parent, position, dimension, angle, velocity) {}

    void update() override {
        // Example behavior: move randomly within bounds
        moveBy(angleDir.getX(), angleDir.getY());
    }

  protected:
    double detectDistance = 50;
    double rotaionAmount = 1;
    bool rotateRight = true;
};

class ControlledRobot : public Robot {
  public:
    ControlledRobot(QGraphicsItem *parent = nullptr, QPointF position = QPointF(0, 0), QPointF dimension = QPointF(25, 25), double angle = 0.0, double velocity = 0.0)
        : Robot(parent, position, dimension, angle, velocity) {}

    void update() override {
        // Example behavior: move based on user input
        angleDir.angle += 0.3;
        setRotation(angleDir.angle);
    }
};

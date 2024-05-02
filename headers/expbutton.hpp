#ifndef EXPBUTTON_HPP
#define EXPBUTTON_HPP

#include <QObject>
#include <QPushButton>

class ExpButton : public QPushButton {
    Q_OBJECT

  public:
    explicit ExpButton(const QString &text, QWidget *parent = nullptr);

  signals:
    void pressed();

  private slots:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // EXPBUTTON_HPP
#ifndef PARAMEDITLINE_HPP
#define PARAMEDITLINE_HPP

#include <QFocusEvent>
#include <QLineEdit>

class ParamEditLine : public QLineEdit {
    Q_OBJECT

  public:
    explicit ParamEditLine(QWidget *parent = nullptr)
        : QLineEdit(parent) {}

    void focusInEvent(QFocusEvent *event) override {
        QLineEdit::focusOutEvent(event);
        emit focusIn();
    }

    void focusOutEvent(QFocusEvent *event) override {
        QLineEdit::focusOutEvent(event);
        emit focusOut();
    }

  signals:
    void focusIn();
    void focusOut();
};

#endif // PARAMEDITLINE_HPP

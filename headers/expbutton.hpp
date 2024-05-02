#ifndef EXPBUTTON_HPP
#define EXPBUTTON_HPP

#include <QObject>
#include <QPushButton>

/**
 * @class ExpButton
 * @brief A class for expandable buttons.
 * @details This class inherits from QPushButton and emits a signal when pressed.
 * @see QPushButton
 */
class ExpButton : public QPushButton {
    Q_OBJECT

  public:
    /**
     * @brief Constructor for ExpButton.
     * @param text The text to be displayed on the button.
     * @param parent The parent QWidget.
     */
    explicit ExpButton(const QString &text, QWidget *parent = nullptr);

  signals:
    /**
     * @brief Signal emitted when the button is pressed.
     * @return void
     */
    void pressed();

  private slots:
    /**
     * @brief Slot to handle the button press event.
     * @param event The QMouseEvent that triggered the slot.
     * @return void
     */
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // EXPBUTTON_HPP
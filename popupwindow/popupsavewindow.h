#ifndef POPUPSAVEWINDOW_H
#define POPUPSAVEWINDOW_H

#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class PopupSaveWindow : public QDialog {
    Q_OBJECT

  public:
    explicit PopupSaveWindow(QWidget *parent = nullptr);
    ~PopupSaveWindow();

    QString getEnteredText() { return enteredText; }

  private:
    QString enteredText;
    QLineEdit *lineEdit;

  private slots:
    void onOkClicked();
};

#endif // POPUPSAVEWINDOW_H

#pragma once

#include <QtWidgets>

class DialogWindow : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *mainLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *buttonsLayout;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;

signals:
    void buttonClickedOK(const QString &text);
    void buttonClickedCancel();

private slots:
    void slotOK();
    void slotCancel();

public:
    DialogWindow(QWidget *parent, const QString &text = "");
    ~DialogWindow();

};

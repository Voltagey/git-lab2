#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitClicked();
    void dotClicked();
    void clearClicked();
    void binaryOperatorClicked();
    void equalClicked();

    // Индивидуальные функции (Вариант 12)
    void plusMinusClicked();
    void cosClicked();
    void log2Clicked();
    void dbClicked();

private:
    QLineEdit *display;
    double firstOperand;
    QString pendingOperator;
    bool waitingForOperand;
};

#endif // MAINWINDOW_H

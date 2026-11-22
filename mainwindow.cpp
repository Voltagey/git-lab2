#include "mainwindow.h"
#include <QWidget>
#include <QMessageBox>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), firstOperand(0.0), waitingForOperand(true) {
    setWindowTitle("Калькулятор Qt — Вариант 12");
    resize(340, 420);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QGridLayout *layout = new QGridLayout(central);

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(45);
    layout->addWidget(display, 0, 0, 1, 4);

    // Индивидуальные функции Варианта 12: ±, cos, log2, дБ
    QPushButton *btnPlusMinus = new QPushButton("±");
    QPushButton *btnCos = new QPushButton("cos");
    QPushButton *btnLog2 = new QPushButton("log2");
    QPushButton *btnDb = new QPushButton("дБ");

    connect(btnPlusMinus, &QPushButton::clicked, this, &MainWindow::plusMinusClicked);
    connect(btnCos, &QPushButton::clicked, this, &MainWindow::cosClicked);
    connect(btnLog2, &QPushButton::clicked, this, &MainWindow::log2Clicked);
    connect(btnDb, &QPushButton::clicked, this, &MainWindow::dbClicked);

    layout->addWidget(btnPlusMinus, 1, 0);
    layout->addWidget(btnCos, 1, 1);
    layout->addWidget(btnLog2, 1, 2);
    layout->addWidget(btnDb, 1, 3);

    // Цифровой блок 0-9
    const char *digits[10] = {"0","1","2","3","4","5","6","7","8","9"};
    int positions[10][2] = {
        {5, 0}, {4, 0}, {4, 1}, {4, 2},
        {3, 0}, {3, 1}, {3, 2},
        {2, 0}, {2, 1}, {2, 2}
    };

    for (int i = 0; i < 10; ++i) {
        QPushButton *btn = new QPushButton(digits[i]);
        connect(btn, &QPushButton::clicked, this, &MainWindow::digitClicked);
        layout->addWidget(btn, positions[i][0], positions[i][1]);
    }

    QPushButton *btnDot = new QPushButton(".");
    QPushButton *btnClear = new QPushButton("C");
    QPushButton *btnEqual = new QPushButton("=");

    connect(btnDot, &QPushButton::clicked, this, &MainWindow::dotClicked);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::clearClicked);
    connect(btnEqual, &QPushButton::clicked, this, &MainWindow::equalClicked);

    layout->addWidget(btnDot, 5, 1);
    layout->addWidget(btnClear, 5, 2);
    layout->addWidget(btnEqual, 5, 3);

    // Базовые операции: +, -, *, /
    const char *ops[4] = {"/", "*", "-", "+"};
    for (int i = 0; i < 4; ++i) {
        QPushButton *btnOp = new QPushButton(ops[i]);
        connect(btnOp, &QPushButton::clicked, this, &MainWindow::binaryOperatorClicked);
        layout->addWidget(btnOp, i + 2, 3);
    }
}

MainWindow::~MainWindow() {}

void MainWindow::digitClicked() {
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    QString digit = btn->text();
    if (display->text() == "0" && digit == "0") return;
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + digit);
}

void MainWindow::dotClicked() {
    if (waitingForOperand) {
        display->setText("0");
        waitingForOperand = false;
    }
    if (!display->text().contains('.')) {
        display->setText(display->text() + ".");
    }
}

void MainWindow::clearClicked() {
    display->setText("0");
    firstOperand = 0.0;
    pendingOperator.clear();
    waitingForOperand = true;
}

void MainWindow::binaryOperatorClicked() {
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    firstOperand = display->text().toDouble();
    pendingOperator = btn->text();
    waitingForOperand = true;
}

void MainWindow::equalClicked() {
    double secondOperand = display->text().toDouble();
    double result = 0.0;

    if (pendingOperator == "+") result = firstOperand + secondOperand;
    else if (pendingOperator == "-") result = firstOperand - secondOperand;
    else if (pendingOperator == "*") result = firstOperand * secondOperand;
    else if (pendingOperator == "/") {
        if (secondOperand == 0.0) {
            QMessageBox::warning(this, "Ошибка", "Деление на ноль невозможно!");
            clearClicked();
            return;
        }
        result = firstOperand / secondOperand;
    } else {
        return;
    }

    display->setText(QString::number(result));
    pendingOperator.clear();
    waitingForOperand = true;
}

// 1. Знак плюс-минус
void MainWindow::plusMinusClicked() {
    double val = display->text().toDouble();
    display->setText(QString::number(-val));
}

// 2. Косинус cos(x)
void MainWindow::cosClicked() {
    double val = display->text().toDouble();
    display->setText(QString::number(std::cos(val)));
    waitingForOperand = true;
}

// 3. Двоичный логарифм log2(x)
void MainWindow::log2Clicked() {
    double val = display->text().toDouble();
    if (val <= 0.0) {
        QMessageBox::warning(this, "Ошибка", "Логарифм определен только для x > 0!");
        return;
    }
    display->setText(QString::number(std::log2(val)));
    waitingForOperand = true;
}

// 4. Вычисление дБ: 10 * lg(x)
void MainWindow::dbClicked() {
    double val = display->text().toDouble();
    if (val <= 0.0) {
        QMessageBox::warning(this, "Ошибка", "Значение для дБ должно быть > 0!");
        return;
    }
    display->setText(QString::number(10.0 * std::log10(val)));
    waitingForOperand = true;
}

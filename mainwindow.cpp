#include "mainwindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("База данных «Фирмы» (Qt + SQLite) — Вариант 12");
    resize(780, 440);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    QVBoxLayout *leftLayout = new QVBoxLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();

    tableView = new QTableView(this);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->hide();
    leftLayout->addWidget(tableView);

    QHBoxLayout *btnRow = new QHBoxLayout();
    QPushButton *allDataViewButton = new QPushButton("Вывести все", this);
    QPushButton *filterDataButton = new QPushButton("Выручка > 500", this);
    QPushButton *filterData2Button = new QPushButton("Город = Moscow", this);
    QPushButton *sortDataButton = new QPushButton("Сортировка по выручке", this);

    btnRow->addWidget(allDataViewButton);
    btnRow->addWidget(filterDataButton);
    btnRow->addWidget(filterData2Button);
    btnRow->addWidget(sortDataButton);
    leftLayout->addLayout(btnRow);

    QFormLayout *formLayout = new QFormLayout();
    lineEditID = new QLineEdit(this);
    lineEditName = new QLineEdit(this);
    lineEditCity = new QLineEdit(this);
    lineEditEmployees = new QLineEdit(this);
    lineEditRevenue = new QLineEdit(this);

    formLayout->addRow("ID:", lineEditID);
    formLayout->addRow("Название:", lineEditName);
    formLayout->addRow("Город:", lineEditCity);
    formLayout->addRow("Сотрудники:", lineEditEmployees);
    formLayout->addRow("Выручка (млн):", lineEditRevenue);
    rightLayout->addLayout(formLayout);

    QPushButton *pushButtonAdd = new QPushButton("Добавить запись", this);
    QPushButton *pushButtonRem = new QPushButton("Удалить по ID", this);
    rightLayout->addWidget(pushButtonAdd);
    rightLayout->addWidget(pushButtonRem);
    rightLayout->addStretch();

    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 1);

    // Подключение к БД SQLite
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("firms.db");
    query = new QSqlQuery(m_db);

    if (!m_db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных!");
        return;
    }

    if (!m_db.tables().contains("Firms")) {
        query->clear();
        query->exec("CREATE TABLE Firms (ID INTEGER PRIMARY KEY, Name VARCHAR(30), City VARCHAR(30), Employees INTEGER, Revenue REAL);");
        query->clear();
        query->exec("INSERT INTO Firms (ID, Name, City, Employees, Revenue) VALUES (1, 'Yandex', 'Moscow', 25000, 800.5);");
        query->clear();
        query->exec("INSERT INTO Firms (ID, Name, City, Employees, Revenue) VALUES (2, 'Gazprom', 'SPb', 490000, 8500.0);");
        query->clear();
        query->exec("INSERT INTO Firms (ID, Name, City, Employees, Revenue) VALUES (3, 'Ozon', 'Moscow', 60000, 420.2);");
        query->clear();
        query->exec("INSERT INTO Firms (ID, Name, City, Employees, Revenue) VALUES (4, 'Selectel', 'SPb', 1200, 12.5);");
        query->clear();
        query->exec("INSERT INTO Firms (ID, Name, City, Employees, Revenue) VALUES (5, 'Tinkoff', 'Moscow', 45000, 510.8);");
    }

    model = new QSqlTableModel(this, m_db);
    model->setTable("Firms");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    tableView->setModel(model);

    connect(allDataViewButton, &QPushButton::clicked, this, &MainWindow::on_allDataViewButton_clicked);
    connect(filterDataButton, &QPushButton::clicked, this, &MainWindow::on_filterDataButton_clicked);
    connect(filterData2Button, &QPushButton::clicked, this, &MainWindow::on_filterData2Button_clicked);
    connect(sortDataButton, &QPushButton::clicked, this, &MainWindow::on_sortDataButton_clicked);
    connect(pushButtonAdd, &QPushButton::clicked, this, &MainWindow::on_pushButtonAdd_clicked);
    connect(pushButtonRem, &QPushButton::clicked, this, &MainWindow::on_pushButtonRem_clicked);
}

MainWindow::~MainWindow() {
    delete query;
    delete model;
}

void MainWindow::on_allDataViewButton_clicked() {
    model->setFilter("");
    model->setSort(0, Qt::AscendingOrder);
    model->select();
}

void MainWindow::on_filterDataButton_clicked() {
    model->setFilter("Revenue > 500");
    model->select();
}

void MainWindow::on_filterData2Button_clicked() {
    model->setFilter("City = 'Moscow'");
    model->select();
}

void MainWindow::on_sortDataButton_clicked() {
    model->setSort(4, Qt::DescendingOrder);
    model->select();
}

void MainWindow::on_pushButtonAdd_clicked() {
    if (lineEditID->text().isEmpty() || lineEditName->text().isEmpty() ||
        lineEditCity->text().isEmpty() || lineEditEmployees->text().isEmpty() ||
        lineEditRevenue->text().isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Заполните все поля!");
        return;
    }
    QString buf = QString("INSERT INTO Firms (ID, Name, City, Employees, Revenue) VALUES (%1, '%2', '%3', %4, %5);")
                      .arg(lineEditID->text())
                      .arg(lineEditName->text())
                      .arg(lineEditCity->text())
                      .arg(lineEditEmployees->text())
                      .arg(lineEditRevenue->text());
    query->clear();
    if (!query->exec(buf)) {
        QMessageBox::warning(this, "Ошибка", "Запись с таким ID уже существует или неверные данные!");
        return;
    }
    model->select();
}

void MainWindow::on_pushButtonRem_clicked() {
    if (lineEditID->text().isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Введите ID для удаления!");
        return;
    }
    query->clear();
    query->exec("DELETE FROM Firms WHERE ID = " + lineEditID->text());
    model->select();
}

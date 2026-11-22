#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_allDataViewButton_clicked();
    void on_filterDataButton_clicked();
    void on_filterData2Button_clicked();
    void on_sortDataButton_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonRem_clicked();

private:
    QSqlDatabase m_db;
    QSqlQuery *query;
    QSqlTableModel *model;

    QTableView *tableView;
    QLineEdit *lineEditID;
    QLineEdit *lineEditName;
    QLineEdit *lineEditCity;
    QLineEdit *lineEditEmployees;
    QLineEdit *lineEditRevenue;
};

#endif // MAINWINDOW_H

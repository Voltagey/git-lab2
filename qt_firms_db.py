import sys
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QHBoxLayout, QVBoxLayout,
    QFormLayout, QLineEdit, QPushButton, QTableView, QMessageBox, QHeaderView
)
from PySide6.QtSql import QSqlDatabase, QSqlQuery, QSqlTableModel
from PySide6.QtCore import Qt

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("База данных «Фирмы» (Qt + SQLite) — Вариант 12")
        self.resize(800, 440)

        central = QWidget(self)
        self.setCentralWidget(central)
        main_layout = QHBoxLayout(central)
        left_layout = QVBoxLayout()
        right_layout = QVBoxLayout()

        self.table_view = QTableView(self)
        self.table_view.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        left_layout.addWidget(self.table_view)

        btn_row = QHBoxLayout()
        self.btn_all = QPushButton("Вывести все")
        self.btn_f1 = QPushButton("Выручка > 500")
        self.btn_f2 = QPushButton("Город = Moscow")
        self.btn_sort = QPushButton("Сортировка по выручке")
        for b in (self.btn_all, self.btn_f1, self.btn_f2, self.btn_sort):
            btn_row.addWidget(b)
        left_layout.addLayout(btn_row)

        form = QFormLayout()
        self.edit_id = QLineEdit()
        self.edit_name = QLineEdit()
        self.edit_city = QLineEdit()
        self.edit_emp = QLineEdit()
        self.edit_rev = QLineEdit()
        form.addRow("ID:", self.edit_id)
        form.addRow("Название:", self.edit_name)
        form.addRow("Город:", self.edit_city)
        form.addRow("Сотрудники:", self.edit_emp)
        form.addRow("Выручка (млн):", self.edit_rev)
        right_layout.addLayout(form)

        self.btn_add = QPushButton("Добавить запись")
        self.btn_rem = QPushButton("Удалить по ID")
        self.btn_add.setStyleSheet("background-color: #d9ead3; font-weight: bold;")
        self.btn_rem.setStyleSheet("background-color: #f4cccc; font-weight: bold;")
        right_layout.addWidget(self.btn_add)
        right_layout.addWidget(self.btn_rem)
        right_layout.addStretch()

        main_layout.addLayout(left_layout, 3)
        main_layout.addLayout(right_layout, 1)

        self.db = QSqlDatabase.addDatabase("QSQLITE")
        self.db.setDatabaseName("firms.db")
        if not self.db.open():
            QMessageBox.critical(self, "Ошибка", "Не удалось открыть базу данных!")
            return

        self.query = QSqlQuery(self.db)
        if "Firms" not in self.db.tables():
self.query.exec("СОЗДАТЬ ТАБЛИЦУ Firms (ID INTEGER PRIMARY KEY, Name VARCHAR(30), City VARCHAR(30), Employees INTEGER, Revenue REAL);")
rows = [
"(1, 'Яндекс', 'Москва', 25000, 800.5)",
"(2, 'Газпром', 'СПб', 490000, 8500.0)",
"(3, 'Ozon', 'Москва', 60000, 420.2)",
"(4, 'Selectel', 'СПб', 1200, 12.5)",
"(5, "Тинькофф", "Москва", 45000, 510.8)"
]
для r в строках:
self.query.exec(f"INSERT INTO Firms (ID, Name, City, Employees, Revenue) VALUES {r};")
self.model = QSqlTableModel(self, self.db)
self.model.setTable("Firms")
self.model.setEditStrategy(QSqlTableModel.OnFieldChange)
self.model.select()
self.table_view.setModel(self.model)
self.btn_all.clicked.connect(self.show_all)
self.btn_f1.clicked.connect(self.filter_rev)
self.btn_f2.clicked.connect(self.filter_city)
self.btn_sort.clicked.connect(self.sort_rev)
self.btn_add.clicked.connect(self.add_record)
self.btn_rem.clicked.connect(self.rem_record)
def show_all(self):
self.model.setFilter("")
self.model.setSort(0, Qt.AscendingOrder)
self.model.select()
def filter_rev(self):
self.model.setFilter("Revenue > 500")
self.model.select()
def filter_city(self):
self.model.setFilter("City = 'Moscow'")
self.model.select()
def sort_rev(self):
self.model.setSort(4, Qt.DescendingOrder)
self.model.select()
определение add_record(self):
если не все([self.edit_id.text(), self.edit_name.text(), self.edit_city.text(), self.edit_emp.text(), self.edit_rev.text()]):
QMessageBox.warning(self, "Внимание", "Заполните все поля!")
возвращает
sql = f"ВСТАВИТЬ В значения Firms (ID, название, город, сотрудники, доход) ({self.edit_id. text()}, '{self.edit_name.text()}', '{self.edit_city.text()}', {self.edit_emp.text()}, {self.edit_rev.text()});"
если не self.query.exec(sql):
QMessageBox.warning(self, "Ошибка", "Запись с таким идентификатором уже существует или неверный формат чисел!")
return
self.model.select()
def rem_record(self):
if not self.edit_id.text():
QMessageBox.warning(self, "Внимание", "Введите идентификатор для удаления!")
return
self.query.exec(f"DELETE FROM Firms WHERE ID = {self.edit_id.text()};")
self.model.select()
if name == "main":
app = QApplication(sys.argv)
w = MainWindow()
w.show()
sys.exit(app.exec())

import sys
import math
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QGridLayout,
    QLineEdit, QPushButton, QMessageBox
)
from PySide6.QtCore import Qt
from PySide6.QtGui import QFont

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Калькулятор Qt — Вариант 12")
        self.resize(340, 430)

        self.first_operand = 0.0
        self.pending_operator = ""
        self.waiting_for_operand = True

        central = QWidget(self)
        self.setCentralWidget(central)
        layout = QGridLayout(central)
        layout.setSpacing(6)

        self.display = QLineEdit("0")
        self.display.setReadOnly(True)
        self.display.setAlignment(Qt.AlignRight)
        self.display.setMinimumHeight(52)
        self.display.setFont(QFont("Segoe UI", 18, QFont.Bold))
        layout.addWidget(self.display, 0, 0, 1, 4)

        special_btns = [
            ("±", 1, 0, self.plus_minus_clicked),
            ("cos", 1, 1, self.cos_clicked),
            ("log2", 1, 2, self.log2_clicked),
            ("дБ", 1, 3, self.db_clicked),
        ]
        for text, r, c, slot in special_btns:
            btn = QPushButton(text)
            btn.setMinimumHeight(42)
            btn.setFont(QFont("Segoe UI", 11, QFont.Bold))
            btn.setStyleSheet("background-color: #dce6f2;")
            btn.clicked.connect(slot)
            layout.addWidget(btn, r, c)

        digits = [
            ("7", 2, 0), ("8", 2, 1), ("9", 2, 2),
            ("4", 3, 0), ("5", 3, 1), ("6", 3, 2),
            ("1", 4, 0), ("2", 4, 1), ("3", 4, 2),
            ("0", 5, 0)
        ]
        for text, r, c in digits:
            btn = QPushButton(text)
            btn.setMinimumHeight(45)
            btn.setFont(QFont("Segoe UI", 12))
            btn.clicked.connect(self.digit_clicked)
            layout.addWidget(btn, r, c)

        btn_dot = QPushButton(".")
        btn_dot.setMinimumHeight(45)
        btn_dot.setFont(QFont("Segoe UI", 12))
        btn_dot.clicked.connect(self.dot_clicked)
        layout.addWidget(btn_dot, 5, 1)

        btn_clear = QPushButton("C")
        btn_clear.setMinimumHeight(45)
        btn_clear.setFont(QFont("Segoe UI", 11, QFont.Bold))
        btn_clear.setStyleSheet("background-color: #f4cccc;")
        btn_clear.clicked.connect(self.clear_clicked)
        layout.addWidget(btn_clear, 5, 2)

        ops = [("/", 2, 3), ("*", 3, 3), ("-", 4, 3), ("+", 5, 3)]
        for text, r, c in ops:
            btn = QPushButton(text)
            btn.setMinimumHeight(45)
            btn.setFont(QFont("Segoe UI", 12, QFont.Bold))
            btn.setStyleSheet("background-color: #fce5cd;")
            btn.clicked.connect(self.binary_operator_clicked)
            layout.addWidget(btn, r, c)

        btn_eq = QPushButton("=")
        btn_eq.setMinimumHeight(46)
        btn_eq.setFont(QFont("Segoe UI", 13, QFont.Bold))
        btn_eq.setStyleSheet("background-color: #c9daf8;")
        btn_eq.clicked.connect(self.equal_clicked)
        layout.addWidget(btn_eq, 6, 0, 1, 4)

    def digit_clicked(self):
        digit = self.sender().text()
        if self.display.text() == "0" and digit == "0":
            return
        if self.waiting_for_operand:
            self.display.clear()
            self.waiting_for_operand = False
        self.display.setText(self.display.text() + digit)

    def dot_clicked(self):
if self.waiting_for_operand:
self.display.setText("0")
self.waiting_for_operand = False
если "." не в self.display.text():
self.display.setText(self.display.text() + ".")
определение clear_clicked(self):
self.display.setText("0")
self.first_operand = 0.0
self.pending_operator = ""
self.waiting_for_operand = True
def binary_operator_clicked(self):
self.first_operand = float(self.display.text())
self.pending_operator = self.sender().text()
self.waiting_for_operand = True
определение equal_clicked(self):
second_operand = float(self.display.text())
op = self.pending_operator
если op == "+":
результат = self.first_operand + second_operand
elif op == "-":
результат = self.first_operand - second_operand
elif op == "*":
результат = self.first_operand * second_operand
elif op == "/":
если second_operand == 0.0:
QMessageBox.warning(self, "Ошибка", "Деление на ноль невозможно!")
self.clear_clicked()
возвращает
результат = self.first_operand / second_operand
еще:
возвращает
self.display.setText(f"{результат:g}")
self.pending_operator = ""
self.waiting_for_operand = True
определение plus_minus_clicked(self):
val = float(self.display.text())
self.display.setText(f"{-val:g}")
определение cos_clicked(self):
val = float(self.display.text())
self.display.setText(f"{math.cos(val):.6g}")
self.waiting_for_operand = True
def log2_clicked(self):
val = float(self.display.text())
if val <= 0.0:
QMessageBox.warning(self, "Ошибка", "Логарифм определен только для x > 0!")
return
self.display.setText(f"{math.log2(val):.6g}")
self.waiting_for_operand = True
def db_clicked(self):
val = float(self.display.text())
if val <= 0.0:
QMessageBox.warning(self, "Ошибка", "Значение для дБ должно быть > 0!")
return
self.display.setText(f"{10.0 * math.log10(val):.6g}")
self.waiting_for_operand = True
если name == "main":
app = QApplication(sys.argv)
w = MainWindow()
w.show()
sys.exit(app.exec())

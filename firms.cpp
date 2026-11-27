#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <windows.h>

using namespace std;

struct Firm {
    int id;
    string name;
    string city;
    string industry;
    int employees;
    double revenue;
    double avgSalary;
};

int inputInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "Ошибка: вы ввели не число! Попробуйте снова.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double inputDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "Ошибка: вы ввели не число! Попробуйте снова.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

Firm* loadFirms(const string& filename, int& count) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        count = 0;
        return nullptr;
    }
    count = 0;
    Firm temp;
    while (fin >> temp.id >> temp.name >> temp.city >> temp.industry >> temp.employees >> temp.revenue >> temp.avgSalary) {
        count++;
    }
    fin.clear();
    fin.seekg(0, ios::beg);

    Firm* arr = new Firm[count];
    for (int i = 0; i < count; i++) {
        fin >> arr[i].id >> arr[i].name >> arr[i].city >> arr[i].industry >> arr[i].employees >> arr[i].revenue >> arr[i].avgSalary;
    }
    fin.close();
    return arr;
}

void printFirms(const Firm* arr, int count) {
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << left << setw(5) << "ID"
         << setw(14) << "Название"
         << setw(12) << "Город"
         << setw(14) << "Отрасль"
         << setw(12) << "Сотрудники"
         << setw(12) << "Выручка"
         << setw(10) << "Зарплата" << endl;
    cout << "--------------------------------------------------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << left << setw(5) << arr[i].id
             << setw(14) << arr[i].name
             << setw(12) << arr[i].city
             << setw(14) << arr[i].industry
             << setw(12) << arr[i].employees
             << setw(12) << fixed << setprecision(1) << arr[i].revenue
             << setw(10) << fixed << setprecision(1) << arr[i].avgSalary << endl;
    }
    cout << "--------------------------------------------------------------------------------\n";
}

void saveFirms(const string& filename, const Firm* arr, int count) {
    ofstream fout(filename);
    for (int i = 0; i < count; i++) {
        fout << arr[i].id << " " << arr[i].name << " " << arr[i].city << " "
             << arr[i].industry << " " << arr[i].employees << " "
             << arr[i].revenue << " " << arr[i].avgSalary << "\n";
    }
    fout.close();
}

void saveReport(const string& filename, const Firm* arr, int count) {
    ofstream fout(filename);
    long long totalStaff = 0;
    double totalRev = 0.0, sumSal = 0.0;
    fout << "Отчет по базе данных: Фирмы (Вариант 12)\n";
    fout << "------------------------------------------------------------\n";
    for (int i = 0; i < count; i++) {
        fout << arr[i].id << ". " << arr[i].name << " (" << arr[i].city << ", " << arr[i].industry
             << ") - Сотр.: " << arr[i].employees << ", Выручка: " << arr[i].revenue
             << ", Зарплата: " << arr[i].avgSalary << "\n";
        totalStaff += arr[i].employees;
        totalRev += arr[i].revenue;
        sumSal += arr[i].avgSalary;
    }
    fout << "------------------------------------------------------------\n";
    fout << "Всего фирм: " << count << "\n";
    fout << "Всего сотрудников: " << totalStaff << "\n";
    fout << "Общая выручка: " << totalRev << " млн\n";
    if (count > 0) {
        fout << "Средняя зарплата: " << (sumSal / count) << " тыс.\n";
    }
    fout.close();
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int count = 0;
    Firm* firms = loadFirms("firms.txt", count);
    if (!firms) {
        cout << "Ошибка открытия файла firms.txt!\n";
        return 1;
    }

    int choice;
    do {
        cout << "\n--- МЕНЮ (База данных: Фирмы) ---\n";
        cout << "1. Вывести таблицу фирм\n";
        cout << "2. Добавить новую фирму\n";
        cout << "3. Удалить фирму по ID\n";
        cout << "4. Поиск по отрасли\n";
        cout << "5. Статистика (сотрудники, выручка, средняя зарплата)\n";
        cout << "0. Сохранить и выйти\n";
        choice = inputInt("Выберите пункт: ");

        switch (choice) {
            case 1:
                printFirms(firms, count);
                break;
            case 2: {
                Firm newFirm;
                newFirm.id = inputInt("Введите ID: ");
                cout << "Введите название (одно слово): ";
                cin >> newFirm.name;
                cout << "Введите город: ";
                cin >> newFirm.city;
                cout << "Введите отрасль: ";
                cin >> newFirm.industry;
                newFirm.employees = inputInt("Введите количество сотрудников: ");
                newFirm.revenue = inputDouble("Введите выручку (млн): ");
                newFirm.avgSalary = inputDouble("Введите среднюю зарплату (тыс.): ");

                Firm* temp = new Firm[count + 1];
                for (int i = 0; i < count; i++) temp[i] = firms[i];
                temp[count] = newFirm;
                delete[] firms;
                firms = temp;
                count++;
                cout << "Фирма успешно добавлена!\n";
                break;
            }
            case 3: {
                int delId = inputInt("Введите ID фирмы для удаления: ");
                int idx = -1;
                for (int i = 0; i < count; i++) {
                    if (firms[i].id == delId) { idx = i; break; }
                }
                if (idx == -1) {
                    cout << "Фирма с таким ID не найдена.\n";
                } else {
                    Firm* temp = new Firm[count - 1];
                    for (int i = 0, j = 0; i < count; i++) {
                        if (i != idx) temp[j++] = firms[i];
                    }
                    delete[] firms;
                    firms = temp;
                    count--;
                    cout << "Фирма удалена!\n";
                }
                break;
            }
            case 4: {
                string ind;
                cout << "Введите название отрасли (например, IT): ";
                cin >> ind;
                bool found = false;
                for (int i = 0; i < count; i++) {
                    if (firms[i].industry == ind) {
                        cout << firms[i].id << " | " << firms[i].name << " | " << firms[i].city
                             << " | Сотр: " << firms[i].employees << " | Выручка: " << firms[i].revenue << endl;
                        found = true;
                    }
                }
                if (!found) cout << "Фирм в этой отрасли не найдено.\n";
                break;
            }
            case 5: {
                long long totalStaff = 0;
                double totalRev = 0.0, sumSal = 0.0;
                for (int i = 0; i < count; i++) {
                    totalStaff += firms[i].employees;
                    totalRev += firms[i].revenue;
                    sumSal += firms[i].avgSalary;
                }
                cout << "\nВсего фирм: " << count << endl;
                cout << "Всего сотрудников: " << totalStaff << endl;
                cout << "Общая выручка: " << fixed << setprecision(1) << totalRev << " млн" << endl;
                if (count > 0)
                    cout << "Средняя зарплата по фирмам: " << fixed << setprecision(1) << (sumSal / count) << " тыс.\n";
                break;
            }
            case 0:
                saveFirms("firms.txt", firms, count);
                saveReport("out.txt", firms, count);
                cout << "Данные сохранены в firms.txt и out.txt. Выход...\n";
                break;
            default:
                cout << "Неверный пункт меню! Выберите от 0 до 5.\n";
        }
    } while (choice != 0);

    delete[] firms;
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
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

Firm* readFromFile(const string& filename, int& count) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Ошибка: файл " << filename << " не найден!" << endl;
        count = 0;
        return nullptr;
    }
    count = 0;
    Firm temp;
    while (fin >> temp.id >> temp.name >> temp.city >> temp.industry >> temp.employees >> temp.revenue >> temp.avgSalary) {
        count++;
    }
    fin.clear();
    fin.seekg(0);

    Firm* arr = new Firm[count];
    for (int i = 0; i < count; i++) {
        fin >> arr[i].id >> arr[i].name >> arr[i].city >> arr[i].industry >> arr[i].employees >> arr[i].revenue >> arr[i].avgSalary;
    }
    fin.close();
    return arr;
}

void viewData(const Firm* arr, int count) {
    if (count == 0 || arr == nullptr) {
        cout << "База данных пуста." << endl;
        return;
    }
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

void editRecord(Firm* arr, int count) {
    int targetId;
    cout << "Введите ID фирмы для редактирования: ";
    cin >> targetId;
    for (int i = 0; i < count; i++) {
        if (arr[i].id == targetId) {
            cout << "Введите новые: Название, Город, Отрасль, Сотрудников, Выручку, Зарплату:\n";
            cin >> arr[i].name >> arr[i].city >> arr[i].industry >> arr[i].employees >> arr[i].revenue >> arr[i].avgSalary;
            cout << "Запись успешно обновлена!" << endl;
            return;
        }
    }
    cout << "Фирма с ID " << targetId << " не найдена." << endl;
}

Firm* addRecord(Firm* arr, int& count) {
    Firm* newArr = new Firm[count + 1];
    for (int i = 0; i < count; i++) {
        newArr[i] = arr[i];
    }
    cout << "Введите: ID, Название, Город, Отрасль, Сотрудников, Выручку, Зарплату:\n";
    cin >> newArr[count].id >> newArr[count].name >> newArr[count].city >> newArr[count].industry >> newArr[count].employees >> newArr[count].revenue >> newArr[count].avgSalary;
    delete[] arr;
    count++;
    cout << "Фирма добавлена!" << endl;
    return newArr;
}

Firm* deleteRecord(Firm* arr, int& count) {
    int targetId;
    cout << "Введите ID фирмы для удаления: ";
    cin >> targetId;
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (arr[i].id == targetId) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << "Фирма с ID " << targetId << " не найдена." << endl;
        return arr;
    }
    Firm* newArr = (count - 1 > 0) ? new Firm[count - 1] : nullptr;
    for (int i = 0, j = 0; i < count; i++) {
        if (i != idx) {
            newArr[j++] = arr[i];
        }
    }
    delete[] arr;
    count--;
    cout << "Фирма удалена!" << endl;
    return newArr;
}

void calculateStats(const Firm* arr, int count) {
    if (count == 0 || arr == nullptr) {
        cout << "Нет данных для расчетов." << endl;
        return;
    }
    long long totalStaff = 0;
    double totalRevenue = 0;
    double sumSalary = 0;
    for (int i = 0; i < count; i++) {
        totalStaff += arr[i].employees;
        totalRevenue += arr[i].revenue;
        sumSalary += arr[i].avgSalary;
    }
    cout << "\n=== Статистика по фирмам ===" << endl;
    cout << "Всего фирм: " << count << endl;
    cout << "Всего сотрудников: " << totalStaff << endl;
    cout << "Общая выручка: " << fixed << setprecision(1) << totalRevenue << " млн" << endl;
    cout << "Средняя зарплата по фирмам: " << fixed << setprecision(1) << (sumSalary / count) << " тыс." << endl;
}

void saveToFile(const Firm* arr, int count) {
    string outFilename;
    cout << "Введите имя нового файла для сохранения (например, out.txt): ";
    cin >> outFilename;
    ofstream fout(outFilename);
    if (!fout) {
        cout << "Ошибка при создании файла!" << endl;
        return;
    }
    for (int i = 0; i < count; i++) {
        fout << arr[i].id << " " << arr[i].name << " " << arr[i].city << " "
             << arr[i].industry << " " << arr[i].employees << " "
             << arr[i].revenue << " " << arr[i].avgSalary << "\n";
    }
    fout.close();
    cout << "Данные успешно сохранены в файл " << outFilename << "!" << endl;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int count = 0;
    Firm* firms = readFromFile("firms.txt", count);
    if (!firms) return 1;

    int choice;
    do {
        cout << "\n--- МЕНЮ (База данных: Фирмы) ---\n";
        cout << "1. Просмотр всех фирм\n";
        cout << "2. Редактировать фирму\n";
        cout << "3. Добавить фирму\n";
        cout << "4. Удалить фирму\n";
        cout << "5. Вычислить статистику\n";
        cout << "0. Сохранить в новый файл и выйти\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: viewData(firms, count); break;
            case 2: editRecord(firms, count); break;
            case 3: firms = addRecord(firms, count); break;
            case 4: firms = deleteRecord(firms, count); break;
            case 5: calculateStats(firms, count); break;
            case 0: saveToFile(firms, count); break;
            default: cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    delete[] firms;
    return 0;
}

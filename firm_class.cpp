#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

class Firm {
private:
    int id;
    string name;
    string city;
    string industry;
    int employees;
    double revenue;
    double avgSalary;

public:
    Firm();
    Firm(int id, string name, string city, string industry, int employees, double revenue, double avgSalary);
    ~Firm();

    int getId() const;
    void setId(int val);

    string getName() const;
    void setName(string val);

    string getCity() const;
    void setCity(string val);

    string getIndustry() const;
    void setIndustry(string val);

    int getEmployees() const;
    void setEmployees(int val);

    double getRevenue() const;
    void setRevenue(double val);

    double getAvgSalary() const;
    void setAvgSalary(double val);

    void printRow() const;
};

Firm::Firm() {
    id = 0;
    name = "Неизвестно";
    city = "Не указан";
    industry = "Не указана";
    employees = 0;
    revenue = 0.0;
    avgSalary = 0.0;
}

Firm::Firm(int id, string name, string city, string industry, int employees, double revenue, double avgSalary) {
    this->id = id;
    this->name = name;
    this->city = city;
    this->industry = industry;
    this->employees = employees;
    this->revenue = revenue;
    this->avgSalary = avgSalary;
}

Firm::~Firm() {
}

int Firm::getId() const { return id; }
void Firm::setId(int val) { id = val; }

string Firm::getName() const { return name; }
void Firm::setName(string val) { name = val; }

string Firm::getCity() const { return city; }
void Firm::setCity(string val) { city = val; }

string Firm::getIndustry() const { return industry; }
void Firm::setIndustry(string val) { industry = val; }

int Firm::getEmployees() const { return employees; }
void Firm::setEmployees(int val) { employees = val; }

double Firm::getRevenue() const { return revenue; }
void Firm::setRevenue(double val) { revenue = val; }

double Firm::getAvgSalary() const { return avgSalary; }
void Firm::setAvgSalary(double val) { avgSalary = val; }

void Firm::printRow() const {
    cout << left << setw(5) << id
         << setw(14) << name
         << setw(12) << city
         << setw(14) << industry
         << setw(12) << employees
         << setw(12) << fixed << setprecision(1) << revenue
         << setw(10) << fixed << setprecision(1) << avgSalary << endl;
}

void printTableHeader() {
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << left << setw(5) << "ID"
         << setw(22) << "Название"
         << setw(17) << "Город"
         << setw(21) << "Отрасль"
         << setw(22) << "Сотрудники"
         << setw(19) << "Выручка"
         << setw(18) << "Зарплата" << endl;
    cout << "--------------------------------------------------------------------------------\n";
}

// 1. Создание объекта с помощью конструктора по умолчанию
Firm createDefaultFirm() {
    cout << "\n=== 1. Создание объекта (конструктор по умолчанию) ===" << endl;
    Firm f1;
    printTableHeader();
    f1.printRow();
    return f1;
}

// 2. Создание объекта с помощью конструктора с параметрами
Firm createParamFirm() {
    cout << "\n=== 2. Создание объекта (конструктор с параметрами) ===" << endl;
    Firm f2(1, "Yandex", "Moscow", "IT", 25000, 800.5, 210.0);
    printTableHeader();
    f2.printRow();
    return f2;
}

// 3. Создание массива объектов
void createFirmArray(Firm arr[], int size) {
    cout << "\n=== 3. Создание массива объектов (размер: " << size << ") ===" << endl;
    arr[0] = Firm(1, "Yandex", "Moscow", "IT", 25000, 800.5, 210.0);
    arr[1] = Firm(2, "Gazprom", "SPb", "Energy", 490000, 8500.0, 165.0);
    arr[2] = Firm(3, "Ozon", "Moscow", "Ecommerce", 60000, 420.2, 140.0);
    printTableHeader();
    for (int i = 0; i < size; i++) {
        arr[i].printRow();
    }
}

// 4. Редактирование и просмотр свойств каждого объекта
void editAndViewFirms(Firm arr[], int size) {
    cout << "\n=== 4. Редактирование (сеттеры) и просмотр свойств (геттеры) ===" << endl;
    arr[0].setCity("Innopolis");
    arr[0].setAvgSalary(225.0);
    arr[2].setEmployees(65000);

    for (int i = 0; i < size; i++) {
        cout << "Фирма ID=" << arr[i].getId()
             << " | Название: " << arr[i].getName()
             << " | Город: " << arr[i].getCity()
             << " | Отрасль: " << arr[i].getIndustry()
             << " | Сотрудники: " << arr[i].getEmployees()
             << " | Выручка: " << arr[i].getRevenue()
             << " | Зарплата: " << arr[i].getAvgSalary() << endl;
    }
}

// 5. Обработка массива объектов (статистика по фирмам)
void processFirmArray(const Firm arr[], int size) {
    cout << "\n=== 5. Обработка массива объектов (статистика по фирмам) ===" << endl;
    long long totalStaff = 0;
    double totalRevenue = 0.0;
    double sumSalary = 0.0;

    printTableHeader();
    for (int i = 0; i < size; i++) {
        arr[i].printRow();
        totalStaff += arr[i].getEmployees();
        totalRevenue += arr[i].getRevenue();
        sumSalary += arr[i].getAvgSalary();
    }
    cout << "--------------------------------------------------------------------------------\n";
    cout << "Всего фирм: " << size << endl;
    cout << "Всего сотрудников: " << totalStaff << endl;
    cout << "Общая выручка: " << fixed << setprecision(1) << totalRevenue << " млн" << endl;
    cout << "Средняя зарплата: " << fixed << setprecision(1) << (sumSalary / size) << " тыс." << endl;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Firm f1 = createDefaultFirm();
    Firm f2 = createParamFirm();

    const int SIZE = 3;
    Firm firms[SIZE];
    createFirmArray(firms, SIZE);
    editAndViewFirms(firms, SIZE);
    processFirmArray(firms, SIZE);

    return 0;
}

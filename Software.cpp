#include "Software.h"
#include <iostream>

using namespace std;

Software::Software() : name("Без названия"), company("Неизвестно") {}

Software::Software(const string& name, const string& company)
    : name(name), company(company) {}

Software::~Software() {}

string Software::getCompany() const {
    return company;
}

void Software::setCompany(const string& company) {
    this->company = company;
}

void Software::show() const {
    cout << "Программный продукт: " << name << " | Фирма: " << company << endl;
}

#include "OperatingSystem.h"
#include <iostream>

using namespace std;

OperatingSystem::OperatingSystem() : Software(), bitness(64) {}

OperatingSystem::OperatingSystem(const string& name, const string& company, int bitness)
    : Software(name, company), bitness(bitness) {}

void OperatingSystem::setBitness(int bitness) {
    this->bitness = bitness;
}

int OperatingSystem::getBitness() const {
    return bitness;
}

void OperatingSystem::show() const {
    cout << "[ОС] Название: " << name
         << " | Фирма: " << company
         << " | Разрядность: " << bitness << "-bit" << endl;
}

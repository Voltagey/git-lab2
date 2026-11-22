#include "MetroTrain.h"
#include <iostream>

using namespace std;

MetroTrain::MetroTrain() {
    headlightsOn = false;
    doorsClosed = true;
    speed = 0;
}

MetroTrain::MetroTrain(bool headlights, bool doors, int startSpeed) {
    headlightsOn = headlights;
    doorsClosed = doors;
    if (startSpeed < 0) startSpeed = 0;
    if (startSpeed > 80) startSpeed = 80;
    speed = doorsClosed ? startSpeed : 0;
}

MetroTrain::~MetroTrain() {
}

void MetroTrain::changeHeadlights() {
    headlightsOn = !headlightsOn;
    cout << "Фары головного вагона: " << (headlightsOn ? "ВКЛЮЧЕНЫ" : "ВЫКЛЮЧЕНЫ") << ".\n";
}

void MetroTrain::openDoors() {
    if (speed > 0) {
        cout << "Ошибка: нельзя открыть двери на ходу (скорость " << speed << " км/ч)!\n";
        return;
    }
    if (!doorsClosed) {
        cout << "Двери уже открыты.\n";
        return;
    }
    doorsClosed = false;
    cout << "Двери вагонов открыты для посадки пассажиров.\n";
}

void MetroTrain::closeDoors() {
    if (doorsClosed) {
        cout << "Двери уже закрыты.\n";
        return;
    }
    doorsClosed = true;
    cout << "Осторожно, двери закрываются! Двери закрыты.\n";
}

void MetroTrain::accelerate() {
    if (!doorsClosed) {
        cout << "Ошибка: движение запрещено при открытых дверях!\n";
        return;
    }
    if (!headlightsOn) {
        cout << "Ошибка: перед отправлением необходимо включить фары!\n";
        return;
    }
    if (speed >= 80) {
        cout << "Достигнута максимальная скорость 80 км/ч.\n";
        return;
    }
    speed += 40;
    cout << "Поезд набирает ход. Текущая скорость: " << speed << " км/ч.\n";
}

void MetroTrain::brake() {
    if (speed == 0) {
        cout << "Поезд уже стоит на месте.\n";
        return;
    }
    speed -= 40;
    cout << "Торможение. Текущая скорость: " << speed << " км/ч.\n";
}

std::string MetroTrain::getModeDescription() const {
    if (!headlightsOn && doorsClosed && speed == 0) return "В депо / отстой (фары выкл, двери закрыты, стоит)";
    if (headlightsOn && doorsClosed && speed == 0) return "Готов к отправлению (фары вкл, двери закрыты, стоит)";
    if (!doorsClosed && speed == 0) return "Посадка/высадка на станции (двери открыты, стоит)";
    if (headlightsOn && doorsClosed && speed == 40) return "Движение в тоннеле (крейсерский ход 40 км/ч)";
    if (headlightsOn && doorsClosed && speed == 80) return "Движение в тоннеле (максимальный ход 80 км/ч)";
    return "Промежуточное состояние";
}

void MetroTrain::printState() const {
    cout << "\n--- СОСТОЯНИЕ ПОЕЗДА МЕТРО ---\n";
    cout << "Фары:     " << (headlightsOn ? "ВКЛ" : "ВЫКЛ") << endl;
    cout << "Двери:    " << (doorsClosed ? "ЗАКРЫТЫ" : "ОТКРЫТЫ") << endl;
    cout << "Скорость: " << speed << " км/ч" << endl;
    cout << "Режим:    " << getModeDescription() << endl;
}

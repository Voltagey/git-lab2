#include <iostream>
#include <windows.h>
#include "MetroTrain.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    MetroTrain train;
    int work = 1, command;

    cout << "Модель устройства «Поезд метро» (Вариант 12) запущена.\n";
    train.printState();

    while (work) {
        cout << "\n=== МЕНЮ УПРАВЛЕНИЯ ПОЕЗДОМ ===\n";
        cout << "1. Показать состояние поезда\n";
        cout << "2. Переключить фары (changeHeadlights)\n";
        cout << "3. Открыть двери (openDoors)\n";
        cout << "4. Закрыть двери (closeDoors)\n";
        cout << "5. Набрать скорость +40 км/ч (accelerate)\n";
        cout << "6. Затормозить -40 км/ч (brake)\n";
        cout << "0. Завершить работу\n";
        cout << "Введите номер команды -> ";
        cin >> command;

        switch (command) {
            case 1: train.printState(); break;
            case 2: train.changeHeadlights(); break;
            case 3: train.openDoors(); break;
            case 4: train.closeDoors(); break;
            case 5: train.accelerate(); break;
            case 6: train.brake(); break;
            case 0: work = 0; cout << "Моделирование завершено.\n"; break;
            default: cout << "Неизвестная команда!\n";
        }
    }

    return 0;
}

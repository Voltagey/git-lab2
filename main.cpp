#include <iostream>
#include <windows.h>
#include "Software.h"
#include "OperatingSystem.h"
#include "TextEditor.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    OperatingSystem os1("Windows 11", "Microsoft", 64);
    OperatingSystem os2("Astra Linux", "RusBITech", 64);
    TextEditor ed1("MS Word", "Microsoft", "DOCX");
    TextEditor ed2("Notepad++", "DonHo", "TXT");

    const int SIZE = 4;
    Software* items[SIZE];
    items[0] = &os1;
    items[1] = &os2;
    items[2] = &ed1;
    items[3] = &ed2;

    int choice;
    do {
        cout << "\n=== МЕНЮ (S3P14 Наследование — Вариант 12) ===\n";
        cout << "1. Показать все программные продукты\n";
        cout << "2. Изменить свойства объекта по номеру элемента\n";
        cout << "3. Подсчитать количество программ заданной фирмы\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n--- Список программных продуктов ---\n";
                for (int i = 0; i < SIZE; i++) {
                    cout << i + 1 << ". ";
                    items[i]->show();
                }
                break;
            }
            case 2: {
                int idx;
                cout << "Введите номер элемента (от 1 до " << SIZE << "): ";
                cin >> idx;
                if (idx < 1 || idx > SIZE) {
                    cout << "Неверный номер элемента!\n";
                    break;
                }
                string newComp;
                cout << "Введите новую фирму-разработчика: ";
                cin >> newComp;
                items[idx - 1]->setCompany(newComp);

                if (idx == 1 || idx == 2) {
                    int newBit;
                    cout << "Введите новую разрядность (32 или 64): ";
                    cin >> newBit;
                    static_cast<OperatingSystem*>(items[idx - 1])->setBitness(newBit);
                } else {
                    string newFmt;
                    cout << "Введите новый формат файлов (например, PDF, TXT): ";
                    cin >> newFmt;
                    static_cast<TextEditor*>(items[idx - 1])->setFormat(newFmt);
                }
                cout << "Свойства успешно обновлены!\n";
                break;
            }
            case 3: {
                string targetCompany;
                cout << "Введите название фирмы (например, Microsoft): ";
                cin >> targetCompany;
                int count = 0;
                for (int i = 0; i < SIZE; i++) {
                    if (items[i]->getCompany() == targetCompany) {
                        count++;
                    }
                }
                cout << "Количество программ фирмы \"" << targetCompany << "\": " << count << endl;
                break;
            }
            case 0:
                cout << "Работа программы завершена.\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}

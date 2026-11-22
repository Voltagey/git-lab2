#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

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
        cout << "Error: file " << filename << " not found!" << endl;
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
        cout << "Database is empty." << endl;
        return;
    }
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << left << setw(5) << "ID"
         << setw(14) << "Name"
         << setw(12) << "City"
         << setw(14) << "Industry"
         << setw(12) << "Staff"
         << setw(12) << "Revenue"
         << setw(10) << "Salary" << endl;
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
    cout << "Enter Firm ID to edit: ";
    cin >> targetId;
    for (int i = 0; i < count; i++) {
        if (arr[i].id == targetId) {
            cout << "Enter new Name, City, Industry, Staff, Revenue, Salary:\n";
            cin >> arr[i].name >> arr[i].city >> arr[i].industry >> arr[i].employees >> arr[i].revenue >> arr[i].avgSalary;
            cout << "Record updated!" << endl;
            return;
        }
    }
    cout << "Firm with ID " << targetId << " not found." << endl;
}

Firm* addRecord(Firm* arr, int& count) {
    Firm* newArr = new Firm[count + 1];
    for (int i = 0; i < count; i++) {
        newArr[i] = arr[i];
    }
    cout << "Enter ID, Name, City, Industry, Staff, Revenue, Salary:\n";
    cin >> newArr[count].id >> newArr[count].name >> newArr[count].city >> newArr[count].industry >> newArr[count].employees >> newArr[count].revenue >> newArr[count].avgSalary;
    delete[] arr;
    count++;
    cout << "Firm added!" << endl;
    return newArr;
}

Firm* deleteRecord(Firm* arr, int& count) {
    int targetId;
    cout << "Enter Firm ID to delete: ";
    cin >> targetId;
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (arr[i].id == targetId) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << "Firm with ID " << targetId << " not found." << endl;
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
    cout << "Firm deleted!" << endl;
    return newArr;
}

void calculateStats(const Firm* arr, int count) {
    if (count == 0 || arr == nullptr) {
        cout << "No data for calculation." << endl;
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
    cout << "\n=== Statistics ===" << endl;
    cout << "Total firms: " << count << endl;
    cout << "Total employees: " << totalStaff << endl;
    cout << "Total revenue: " << fixed << setprecision(1) << totalRevenue << " mln" << endl;
    cout << "Average salary across firms: " << fixed << setprecision(1) << (sumSalary / count) << "k" << endl;
}

void saveToFile(const Firm* arr, int count) {
    string outFilename;
    cout << "Enter new filename to save (e.g. out.txt): ";
    cin >> outFilename;
    ofstream fout(outFilename);
    if (!fout) {
        cout << "Error creating file!" << endl;
        return;
    }
    for (int i = 0; i < count; i++) {
        fout << arr[i].id << " " << arr[i].name << " " << arr[i].city << " "
             << arr[i].industry << " " << arr[i].employees << " "
             << arr[i].revenue << " " << arr[i].avgSalary << "\n";
    }
    fout.close();
    cout << "Data saved to " << outFilename << " successfully!" << endl;
}

int main() {
    int count = 0;
    Firm* firms = readFromFile("firms.txt", count);
    if (!firms) return 1;

    int choice;
    do {
        cout << "\n--- MENU (Firms DB) ---\n";
        cout << "1. View all firms\n";
        cout << "2. Edit firm\n";
        cout << "3. Add firm\n";
        cout << "4. Delete firm\n";
        cout << "5. Calculate statistics\n";
        cout << "0. Save to new file & Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewData(firms, count); break;
            case 2: editRecord(firms, count); break;
            case 3: firms = addRecord(firms, count); break;
            case 4: firms = deleteRecord(firms, count); break;
            case 5: calculateStats(firms, count); break;
            case 0: saveToFile(firms, count); break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    delete[] firms;
    return 0;
}

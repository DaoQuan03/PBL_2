#include "qltt.h"
#include "manager.h"
#include <iostream>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls"); // Clear screen for Windows
#else
    system("clear"); // Clear screen for Linux/Mac
#endif
}

void displayMenu(qltt &use) {
    int choice;
    do {
        clearScreen(); // Clean terminal screen before displaying menu again

        cout << "=========================================" << endl;
        cout << "|               EVENT MENU              |" << endl;
        cout << "=========================================" << endl;
        cout << "|  1. Add a new event                   |" << endl;
        cout << "|  2. Edit an event                     |" << endl;
        cout << "|  3. Delete an event                   |" << endl;
        cout << "|  4. Display all events                |" << endl;
        cout << "|  5. Countdown to an event             |" << endl;
        cout << "|  6. Save data                         |" << endl;
        cout << "|  0. Exit                              |" << endl;
        cout << "=========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                use.add();
                break;
            case 2:
                use.fix();
                break;
            case 3:
                use.erase();
                break;
            case 4:
                use.print();
                break;
            case 5:
                use.countdown();
                break;
            case 6:
                use.writedata();
                break;
            case 0:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice!\n";
        }
        
        cout << "Press any key to return to the menu...";
        cin.ignore();
    } while (true);
}

void displayformanager(manager &master) {
    int choice;
    do {
        clearScreen(); // Clean terminal screen before displaying menu again

        cout << "=========================================" << endl;
        cout << "|              MASTER MENU              |" << endl;
        cout << "=========================================" << endl;
        cout << "|  1. Display list of users             |" << endl;
        cout << "|  2. Add a user                        |" << endl;
        cout << "|  3. Delete a user                     |" << endl;
        cout << "|  4. Edit user data                    |" << endl;
        cout << "|  0. Exit                              |" << endl;
        cout << "=========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                master.print();
                break;
            case 2:
                master.add();
                break;
            case 3:
                master.erase();
                break;
            case 4:
                master.fix();
                break;
            case 0:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice!\n";
        }

        cout << "Press any key to return to the menu...";
        cin.ignore();
    } while (true);
}

int main() {
    qltt use;
    manager master;
    int choice;
    do {
        clearScreen(); // Clean terminal screen before displaying main menu again

        cout << "=========================================" << endl;
        cout << "|       WELCOME TO EVENT MANAGER        |" << endl;
        cout << "=========================================" << endl;
        cout << "|  Do you already have an account?      |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "|  1. Yes                               |" << endl;
        cout << "|  2. No                                |" << endl;
        cout << "|  3. Exit program                      |" << endl;
        cout << "=========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                use.checkdata();
                if (use.rightmanager) {
                    displayformanager(master);
                    return 0;
                } else {
                    use.credata();
                    displayMenu(use);
                }
                break;
            case 2:
                use.creacc();
                if (use.rightmanager) {
                    displayformanager(master);
                    return 0;
                } else {
                    displayMenu(use);
                }
                break;
            case 3:
                cout << "See you again!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }

        cout << "Press any key to return to the main menu...";
        cin.ignore();
    } while (choice != 0);

    return 0;
}

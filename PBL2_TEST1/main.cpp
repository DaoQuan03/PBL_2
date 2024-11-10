#include "qltg.h"
#include "countdown.h"
#include "qlttstopwatch.h"

int main()
{
    int choice;
    qltg manager;
    do
    {
        cout << "-------------MENU-------------\n";
        cout << "1. Them su kien moi\n";
        cout << "2. Chinh sua su kien\n";
        cout << "3. Xoa su kien\n";
        cout << "4. Trinh bay tat ca su kien\n";
        cout << "5. Dong ho dem nguoc\n";
        cout << "6. Dong do thoi gian da troi qua\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            manager.add();
            break;

        case 2:
            manager.fix();
            break;

        case 3:
            manager.erase();
            break;

        case 4:
            manager.print();
            break;

        case 5:
        {
            int inputTime;
            cout << "Nhap thoi gian can dem nguoc (giay): ";
            cin >> inputTime;

            if (inputTime <= 0)
            {
                cout << "Thoi gian phai lon hon 0 giay!" << endl;
                break;
            }

            CountdownTimer timer(inputTime);
            timer.start();
            break;
        }
        case 6:
        {
            qlttstopwatch qlttsw;
            string tmenter;
            qlttsw.add();
            break;
        }

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
#include "qltt.h"

int main()
{
    int choice;
    qltt manager;
    do
    {
        cout << "CAM ON BAN DA SU DUNG DICH VU CUA CHUNG TOI\n";
        cout << "Ban da co tai khoan chua ?\n";
        cout << "1.CHUA           2.ROI\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            manager.creaacc();
            do
            {
                cout << "-------------MENU-------------\n";
                cout << "1. Them su kien moi\n";
                cout << "2. Chinh sua su kien\n";
                cout << "3. Xoa su kien\n";
                cout << "4. Trinh bay tat ca su kien\n";
                cout << "5. Dem nguoc den su kien\n";
                cout << "6. Luu du lieu\n";
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
                    manager.countdown();
                    break;
                case 6:
                    manager.writedata();
                    break;
                case 0:
                    cout << "Exiting...\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
                }
            } while (choice != 0);
            break;
        case 2:
            manager.checkacc();
            do
            {
                cout << "-------------MENU-------------\n";
                cout << "1. Them su kien moi\n";
                cout << "2. Chinh sua su kien\n";
                cout << "3. Xoa su kien\n";
                cout << "4. Trinh bay tat ca su kien\n";
                cout << "5. Dem nguoc den su kien\n";
                cout << "6. Luu du lieu\n";
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
                    manager.countdown();
                    break;
                case 6:
                    manager.writedata();
                    break;
                case 0:
                    cout << "Exiting...\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
                }
            } while (choice != 0);
        }
        break;
    } while (choice != 0);
    return 0;
}
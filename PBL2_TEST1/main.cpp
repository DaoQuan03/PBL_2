#include "qltt.h"
#include "manager.h"
void displayMenu(qltt &use)
{
    int choice;
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
    } while (true);
}

void displayformanager(manager &master)
{
    int choice;
    do
    {
        cout << "-------------FOR MASTER-------------\n";
        cout << "1. In ra danh sach pham nhan\n";
        cout << "2. Them mot pham nhan\n";
        cout << "3. Xoa mot pham nhan\n";
        cout << "4. Chinh sua du lieu cua pham nhan\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
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
    } while (true);
}
int main()
{
    qltt use;
    manager master;
    int choice;
    do
    {
        cout << "CAM ON BAN DA SU DUNG DICH VU CUA CHUNG TOI\n";
        cout << "Ban da co tai khoan chua?\n";
        cout << "1. CHUA           2. ROI           3.Thoat chuong trinh\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            use.creacc();
            if (use.rightmanager)
            {
                displayformanager(master);
                return 0;
            }
            else
            {
                displayMenu(use);
            }
            break;
        case 2:
            use.checkdata();
            if (use.rightmanager)
            {
                displayformanager(master);
                return 0;
            }
            else
            {
                use.credata();
                displayMenu(use);
            }
            break;
        case 3:
            cout << "GOOD LUCK\n";
            return 0;
        default:
            cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);

    return 0;
}
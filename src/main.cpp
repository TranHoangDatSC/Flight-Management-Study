#include "Console.h"
#include "DataFile.h"
#include "Screens.h"

#include <iostream>

using namespace std;

static void ShowMainMenu() {
    PrintBanner({ "CHUONG TRINH QUAN LY", "CHUYEN BAY" }, CYAN);
    cout << endl;

    setTextColor(GREEN);
    cout << "1. Hien thi danh sach cac chuyen bay:" << endl;
    setTextColor(YELLOW);
    cout << "2. Dat ve:" << endl;
    setTextColor(BLUE);
    cout << "3. Quan ly:" << endl;
    setTextColor(RED);
    cout << "4. Thoat:" << endl;
    cout << endl;

    ResetColor();
    cout << "Vui long nhap lua chon: ";
}

int main() {
    EnsureDataFolders();
    while (true) {
        ShowMainMenu();
        switch (ReadChoice(1, 4)) {
        case 1:
            ListFlightConsole();
            break;
        case 2:
            OrderTicketConsole();
            break;
        case 3:
            ManagementConsole();
            break;
        case 4:
            return 0;
        }
        ClearScreen(); // cac man hinh con tra ve day khi chon "Quay ve man hinh chinh"
    }
}

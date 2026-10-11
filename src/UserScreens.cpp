#include "Screens.h"
#include "Console.h"
#include "DataFile.h"
#include "LinkedList.h"
#include "Ticket.h"

#include <cstdlib>
#include <iostream>

using namespace std;

// Khanh
void ListFlightConsole() {
    ClearScreen();
    if (!CreateFlightIfEmpty()) {
        PrintLine("Ma chuyen bay|Ngay khoi hanh|San bay den|Trang thai|Danh sach ve ", GREEN);
        for (const string& line : ReadLines(FILE_CHUYEN_BAY)) {
            cout << line << endl;
        }
        cout << endl;
        PrintLine("Vui long chon lua chon: ", YELLOW);
    }
    ShowFooterMenu();
}

// Dat
static void OrderTicket() {
    Ticket newTicket;
    LinkedList<Ticket> ticketList;

    newTicket.GetInfo();
    ticketList.addTail(newTicket);

    newTicket.SaveToFileSolve();
    PrintLine("Hay cho doi Admin xu ly!\n", RED);

    cout << "Hien thi lai thong tin cua ve: " << endl;
    ticketList.display();

    ShowFooterMenu();
}

// Dat
void OrderTicketConsole() {
    ClearScreen();
    PrintBanner({ "DAT VE" }, GREEN);
    cout << endl;

    setTextColor(MAGENTA);
    cout << "1. Dat ve:" << endl;
    setTextColor(CYAN);
    cout << "2. Quay ve man hinh chinh: " << endl;
    setTextColor(RED);
    cout << "3. Thoat khoi chuong trinh: " << endl;
    ResetColor();

    switch (ReadChoice(1, 3)) {
    case 1:
        OrderTicket();
        break;
    case 2:
        break;
    case 3:
        exit(0);
    }
}

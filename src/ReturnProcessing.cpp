// Xu ly tra ve (Khanh)
#include "Screens.h"
#include "Console.h"
#include "DataFile.h"
#include "Ticket.h"
#include "Utils.h"

#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

static void DeleteSeat(const string& flightId, int soGhe) {
    set<int> gheDaDat = ReadBookedSeats(flightId);
    if (gheDaDat.erase(soGhe) == 0) {
        cout << "Ghe " << soGhe << " khong co trong danh sach ghe da dat cua chuyen bay " << flightId << "!" << endl;
        return;
    }
    if (WriteBookedSeats(flightId, gheDaDat)) {
        cout << "Da xoa ghe " << soGhe << " cua chuyen bay " << flightId << "!" << endl;
    }
}

static void RemoveCustomer(const string& ticketId, const string& flightId) {
    Ticket ve;
    if (!ve.LoadFromFile(ticketId)) {
        PrintLine("Khong the doc file " + TicketFileName(ticketId) + "!", RED);
        return;
    }

    // Xoa khach hang cua ve nay khoi KhachHang.txt
    string khachHang = ve.GetCusInfo().ToLine();
    vector<string> customers = ReadLines(FILE_KHACH_HANG);
    vector<string>::iterator it = find(customers.begin(), customers.end(), khachHang);
    if (it != customers.end()) {
        customers.erase(it);
        WriteLines(FILE_KHACH_HANG, customers);
        cout << "Da xoa khach hang " << khachHang << "!" << endl;
    }
    else {
        PrintLine("Khong tim thay khach hang " + khachHang + " de xoa!", RED);
    }

    // Xoa file ve va tra lai ghe
    if (remove(TicketFileName(ticketId).c_str()) == 0) {
        setTextColor(YELLOW);
        cout << "File cua ve " << ticketId << " da xoa thanh cong!" << endl;
        cout << "Tra ve ghe so " << ve.GetCusInfo().GetSTT() << "!" << endl;
        DeleteSeat(flightId, ve.GetCusInfo().GetSTT());
        ResetColor();
    }
    else {
        PrintLine("Khong the xoa file " + TicketFileName(ticketId) + "!", RED);
    }
}

static void SolveReturnTicket(const string& flightId) {
    while (true) {
        cout << endl << "Nhap vao cac so cuoi cua ma ve can xu ly tra ve hoac nhap 'z' de dung:" << endl;
        string input;
        cin >> input;
        if (input == "z" || input == "Z") {
            return;
        }

        string ticketId = NormalizeId(input, "TK");
        vector<string> dsVe = GetTicketIdsOfFlight(flightId);
        if (find(dsVe.begin(), dsVe.end(), ticketId) == dsVe.end()) {
            cout << "Khong tim thay ve " << ticketId << " trong chuyen bay " << flightId << ", vui long nhap lai!" << endl;
            continue;
        }

        if (UpdateTicketListOfFlight(flightId, ticketId, false)) {
            PrintLine("Ma ve " + ticketId + " da duoc xoa khoi chuyen bay " + flightId + ".", DARK_GREEN);
        }
        RemoveCustomer(ticketId, flightId);
        return;
    }
}

void SolveReturnTicketConsole() {
    do {
        ClearScreen();
        PrintBanner({ "XU LY TRA VE" }, DARK_GREEN);
        cout << SEPARATOR << endl;

        if (CreateFlightIfEmpty()) {
            ShowFooterMenu();
            return;
        }

        PrintFlightList();
        string flightId = SelectFlightToProcess(true);
        if (!flightId.empty()) {
            SolveReturnTicket(flightId);
        }
    } while (ShowFooterMenu("xu ly tra ve"));
}

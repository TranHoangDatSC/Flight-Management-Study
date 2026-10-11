// Xu ly dat ve (Dat)
#include "Screens.h"
#include "Console.h"
#include "DataFile.h"
#include "Ticket.h"
#include "Utils.h"

#include <iostream>

using namespace std;

// Tim yeu cau dat ve trong XuLyDatVe.txt, tra ve "" neu khong co
static string FindPendingRequest(const string& ticketId) {
    for (const string& line : ReadLines(FILE_XU_LY_DAT_VE)) {
        if (Split(line, '|')[0] == ticketId) {
            return line;
        }
    }
    return "";
}

static void RemovePendingRequest(const string& ticketId) {
    vector<string> conLai;
    for (const string& line : ReadLines(FILE_XU_LY_DAT_VE)) {
        if (Split(line, '|')[0] != ticketId) {
            conLai.push_back(line);
        }
    }
    if (WriteLines(FILE_XU_LY_DAT_VE, conLai)) {
        PrintLine("Thong tin ve da duoc luu vao " + FILE_KHACH_HANG + " va xoa khoi " + FILE_XU_LY_DAT_VE + ".", DARK_GREEN);
    }
}

// Duyet yeu cau dat ve vao chuyen bay. Tra ve false neu ghe khong hop le / da co nguoi dat.
static bool ApproveRequest(const string& flightId, const Ticket& ve) {
    int soGhe = ve.GetCusInfo().GetSTT();

    string planeId;
    int maxSeat = 0;
    if (ReadPlaneOfFlight(flightId, planeId, maxSeat) && soGhe > maxSeat) {
        PrintLine("Ghe so " + to_string(soGhe) + " vuot qua so cho ngoi cua may bay (" + to_string(maxSeat) + ")!", YELLOW);
        return false;
    }

    set<int> gheDaDat = ReadBookedSeats(flightId);
    if (gheDaDat.count(soGhe) > 0) {
        PrintLine("Ghe da duoc khach hang khac dat! Khong the dat ghe nay nua!", YELLOW);
        return false;
    }

    gheDaDat.insert(soGhe);
    WriteBookedSeats(flightId, gheDaDat);
    AppendLine(FILE_KHACH_HANG, ve.GetCusInfo().ToLine());
    RemovePendingRequest(ve.GetIdTicket());
    ve.SaveToFile();
    UpdateTicketListOfFlight(flightId, ve.GetIdTicket(), true);
    return true;
}

static void SolveOrderTicket(const string& flightId) {
    while (true) {
        cout << endl << "Nhap vao cac so cuoi cua ma ve can xu ly dat ve hoac nhap 'z' de dung:" << endl;
        string input;
        cin >> input;
        if (input == "z" || input == "Z") {
            return;
        }

        string ticketId = NormalizeId(input, "TK");
        string request = FindPendingRequest(ticketId);
        Ticket ve;
        if (request.empty() || !ve.FromLine(request)) {
            PrintLine("Loi! Khong tim thay yeu cau dat ve " + ticketId + ".", RED);
            continue;
        }

        cout << "Tim thay ve: " << request << endl;
        if (ApproveRequest(flightId, ve)) {
            return;
        }
    }
}

void SolveOrderTicketConsole() {
    do {
        ClearScreen();
        PrintBanner({ "XU LY DAT VE" }, DARK_GREEN);
        cout << SEPARATOR << endl;

        if (CreateFlightIfEmpty()) {
            ShowFooterMenu();
            return;
        }

        PrintFlightList();
        cout << "\nHien thi cac yeu cau xu ly dat ve:" << endl;
        PrintLine("Ma ve|So thu tu|So CMND|Ho Ten|Ma ghe ngoi", YELLOW);
        for (const string& line : ReadLines(FILE_XU_LY_DAT_VE)) {
            cout << line << endl;
        }

        string flightId = SelectFlightToProcess(false);
        if (!flightId.empty()) {
            SolveOrderTicket(flightId);
        }
    } while (ShowFooterMenu("xu ly dat ve"));
}

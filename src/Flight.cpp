#include "Flight.h"
#include "Console.h"
#include "DataFile.h"
#include "Utils.h"

#include <iostream>

using namespace std;

void Flight::InitSeats() {
    danhSachGheTrong.clear();
    for (int i = 1; i <= planeInfo.GetSeatNumber(); ++i) {
        danhSachGheTrong.insert(i);
    }
    danhSachGheDaDat.clear();
}

void Flight::GetInfo() {
    SetIdFlight(GenerateUniqueID("FL"));
    cout << "Ma cua chuyen bay: " << GetIdFlight() << endl;

    planeInfo.GetInfo();
    planeInfo.SaveToFile();

    InitSeats();
    SetDateStart(NhapNgayThangNam());

    cout << endl;
    cin.ignore();
    cout << "San bay den: ";
    do {
        getline(cin, sanBayDen);
        if (sanBayDen.empty()) {
            PrintLine("Vui long nhap lai! San bay den khong duoc de trong.", RED);
        }
    } while (sanBayDen.empty());

    while (true) {
        cout << "Nhap trang thai cua chuyen bay ";
        setTextColor(MAGENTA);
        cout << "(0: Huy,";
        setTextColor(CYAN);
        cout << " 1 : Con Ve,";
        setTextColor(RED);
        cout << " 2 : Het Ve,";
        setTextColor(YELLOW);
        cout << " 3 : Hoan Tat) : ";
        ResetColor();

        cin >> trangThai;
        if (trangThai == "0" || trangThai == "1" || trangThai == "2" || trangThai == "3") break;
        PrintLine("Trang thai khong hop le. Vui long nhap lai.", RED);
    }

    GetInfoTicketFL();
}

void Flight::GetInfoTicketFL() {
    cout << endl;
    PrintLine("Nhap danh sach ve:", YELLOW);
    while (true) {
        setTextColor(CYAN);
        cout << "Nhap bat ky de tiep tuc, nhap 'x' de dung: ";
        ResetColor();
        char choice;
        cin >> choice;
        if (choice == 'x' || choice == 'X') break;

        PrintLine("\nHien thi danh sach ghe trong:", GREEN);
        for (int ghe : danhSachGheTrong) {
            cout << ghe << " ";
        }
        cout << endl;

        Ticket ve;
        while (true) {
            ve.GetInfo();
            int soGhe = ve.GetCusInfo().GetSTT();

            if (soGhe < 1 || soGhe > MaxSeat()) {
                PrintLine("So thu tu ghe khong hop le! Vui long nhap lai tu dau!", RED);
            }
            else if (danhSachGheTrong.count(soGhe) == 0) {
                PrintLine("Ghe nay da duoc dat! Vui long chon ghe khac.", RED);
            }
            else {
                danhSachGheTrong.erase(soGhe);
                danhSachGheDaDat.insert(soGhe);
                ve.GetCusInfo().SaveToFile();
                ve.SaveToFile();
                break;
            }
        }
        danhSachVe.push_back(ve);
    }
}

void Flight::SaveToBookedSeat() const {
    if (WriteBookedSeats(idFlight, danhSachGheDaDat)) {
        PrintLine("Danh sach ghe da dat da duoc luu vao file " + FILE_GHE_DA_DAT + ".", GREEN);
    }
}

void Flight::SaveToPLFLFile() const {
    string line = planeInfo.GetIdPlane() + "|" + idFlight + "|" + to_string(planeInfo.GetSeatNumber());
    if (AppendLine(FILE_PL_FL, line)) {
        PrintLine("Da luu vao file " + FILE_PL_FL + ".", GREEN);
    }
}

void Flight::SaveToFile() const {
    string line = idFlight + "|" + ngayKhoiHanh + "|" + sanBayDen + "|" + trangThai + "|";
    for (const Ticket& ve : danhSachVe) {
        line += ve.GetIdTicket() + ";";
    }
    if (AppendLine(FILE_CHUYEN_BAY, line)) {
        PrintLine("Thong tin chuyen bay da duoc luu vao file " + FILE_CHUYEN_BAY + ".", GREEN);
    }
    SaveToBookedSeat();
    SaveToPLFLFile();
}

bool Flight::FromLine(const string& line) {
    vector<string> parts = Split(line, '|');
    if (parts.size() < 4) return false;

    idFlight = parts[0];
    ngayKhoiHanh = parts[1];
    sanBayDen = parts[2];
    trangThai = parts[3];

    danhSachVe.clear();
    if (parts.size() > 4) {
        for (const string& ticketId : Split(parts[4], ';', true)) {
            Ticket ve;
            if (ve.LoadFromFile(ticketId)) {
                danhSachVe.push_back(ve);
            }
        }
    }

    string planeId;
    int seatCount = 0;
    if (ReadPlaneOfFlight(idFlight, planeId, seatCount)) {
        planeInfo.SetIdPlane(planeId);
        planeInfo.SetSeatNumber(seatCount);
    }

    InitSeats();
    danhSachGheDaDat = ReadBookedSeats(idFlight);
    for (int ghe : danhSachGheDaDat) {
        danhSachGheTrong.erase(ghe);
    }
    return true;
}

void Flight::Display() const {
    cout << idFlight << "|" << ngayKhoiHanh << "|" << sanBayDen << "|" << StatusName(trangThai) << "|";
    for (const Ticket& ve : danhSachVe) {
        ve.Display();
    }
    cout << endl;

    cout << "Danh sach ghe trong: ";
    for (int ghe : danhSachGheTrong) {
        cout << ghe << " ";
    }
    cout << endl;
}

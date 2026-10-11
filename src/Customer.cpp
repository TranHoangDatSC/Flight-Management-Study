#include "Customer.h"
#include "Console.h"
#include "DataFile.h"
#include "Utils.h"

#include <iostream>

using namespace std;

static bool IsValidCMND(const string& cmnd) {
    return cmnd.substr(0, 4) == "CMND";
}

void Customer::GetInfo() {
    PrintLine("Nhap so thu tu cua hang khach:", BLUE);
    while (true) {
        if (!TryReadInt(soThuTu) || soThuTu <= 0) {
            PrintLine("So thu tu phai la so nguyen duong lon hon khong! Vui long nhap lai!", RED);
        }
        else if (soThuTu > MAX_SO_GHE) {
            PrintLine("So thu tu phai be hon " + to_string(MAX_SO_GHE) + "!", RED);
        }
        else break;
    }

    while (true) {
        PrintLine("Nhap so chung minh nhan dan cua hang khach: (Dang CMND******)", GREEN);
        cin >> soCMND;
        if (IsValidCMND(soCMND)) break;
        PrintLine("CMND khong hop le!", RED);
    }

    cin.ignore();
    while (true) {
        PrintLine("Nhap ho ten cua hang khach:", GREEN);
        getline(cin, hoTen);
        if (!IsCMNDUsedByOtherName(hoTen, soCMND)) break;
        PrintLine("Loi! Ten nay da duoc dang ky voi so CMND khac!", RED);
    }
}

void Customer::GetFromFile(const string& fileSTT, const string& fileCMND, const string& fileHoTen) {
    soThuTu = stoi(fileSTT);
    soCMND = fileCMND;
    hoTen = fileHoTen;
}

string Customer::ToLine() const {
    return to_string(soThuTu) + "|" + soCMND + "|" + hoTen;
}

void Customer::SaveToFile() const {
    if (AppendLine(FILE_KHACH_HANG, ToLine())) {
        PrintLine("Thong tin khach hang da duoc luu vao file " + FILE_KHACH_HANG + "!", GREEN);
    }
}

void Customer::Display() const {
    cout << ToLine();
}

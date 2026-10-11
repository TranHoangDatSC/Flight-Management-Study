#include "Screens.h"
#include "Console.h"
#include "DataFile.h"
#include "Flight.h"
#include "Utils.h"

#include <cstdlib>
#include <iostream>

using namespace std;

const int MAX_LOGIN_ATTEMPTS = 3;

// Vinh
static void AdminConsole() {
    ClearScreen();
    PrintLine("Chao mung den voi giao dien quan ly he thong!", DARK_GREEN);
    PrintLine(SEPARATOR, GRAY);

    setTextColor(GREEN);
    cout << "1. Xu ly dat ve                   " << endl;
    setTextColor(YELLOW);
    cout << "2. Xu ly tra ve                   " << endl;
    setTextColor(MAGENTA);
    cout << "3. Thong ke                       " << endl;
    setTextColor(CYAN);
    cout << "4. Quay ve man hinh chinh:        " << endl;
    setTextColor(RED);
    cout << "5. Thoat khoi chuong trinh:       " << endl;
    PrintLine(SEPARATOR, GRAY);
    cout << "Xin vui long nhap lua chon: ";

    switch (ReadChoice(1, 5)) {
    case 1:
        SolveOrderTicketConsole();
        break;
    case 2:
        SolveReturnTicketConsole();
        break;
    case 3:
        SolveStatisticalConsole();
        break;
    case 4:
        break;
    case 5:
        exit(0);
    }
}

// Vinh
void ManagementConsole() {
    ClearScreen();
    PrintBanner({ "DANG NHAP HE THONG" }, YELLOW);

    for (int count = 1; ; count++) {
        setTextColor(DARK_CYAN);
        cout << "User:      ";
        setTextColor(CYAN);
        string username;
        cin >> username;
        string password = GetPassword();

        if (CheckAdmin(username, password)) {
            cout << "Dang nhap thanh cong!" << endl;
            AdminConsole();
            return;
        }
        PrintLine("Tai khoan hoac mat khau khong dung. Vui long thu lai!", RED);

        if (count == MAX_LOGIN_ATTEMPTS) {
            PrintLine("Ban da nhap sai qua " + to_string(MAX_LOGIN_ATTEMPTS) + " lan. Dang xuat chuong trinh!", RED);
            exit(0);
        }
    }
}

bool CreateFlightIfEmpty() {
    if (!IsEmptyFile(FILE_CHUYEN_BAY)) {
        return false;
    }
    PrintLine("File rong! Vui long nhap them thong tin cua chuyen bay:\n", RED);

    Flight chuyenBay;
    chuyenBay.GetInfo();
    chuyenBay.SaveToFile();
    cout << endl << "Da khoi tao du lieu cho file " << FILE_CHUYEN_BAY << "!" << endl;
    return true;
}

void PrintFlightList() {
    cout << "Hien thi cac chuyen bay hien tai:" << endl;
    PrintLine("Ma chuyen bay|Ngay khoi hanh|San bay den|Trang thai|Danh sach ve", GREEN);
    for (const string& line : ReadLines(FILE_CHUYEN_BAY)) {
        cout << line << endl;
    }
}

string SelectFlightToProcess(bool allowSoldOut) {
    PrintLine("\nNhap vao cac so cuoi cua ma chuyen bay:", MAGENTA);
    while (true) {
        string input;
        cin >> input;
        string flightId = NormalizeId(input, "FL");
        string line = FindFlightLine(flightId);

        if (!line.empty()) {
            vector<string> parts = Split(line, '|');
            string status = parts.size() > 3 ? parts[3] : "";
            PrintLine("Da tim thay chuyen bay: " + line, GREEN);

            bool canProcess = false;
            if (status == "0") {
                PrintLine("Trang thai: Huy. Vui long chon chuyen bay khac!", DARK_RED);
                PrintLine("Xin quy khach hay den quay thanh toan de lay lai tien va mang theo ve de xac minh!", YELLOW);
            }
            else if (status == "1") {
                PrintLine("Trang thai: Con ve. Ban co the tiep tuc.", DARK_MAGENTA);
                canProcess = true;
            }
            else if (status == "2") {
                if (allowSoldOut) {
                    PrintLine("Trang thai: Het ve. Ban co the tiep tuc.", RED);
                    canProcess = true;
                }
                else {
                    PrintLine("Trang thai: Het ve. Vui long chon chuyen bay khac.", RED);
                }
            }
            else if (status == "3") {
                PrintLine("Trang thai: Hoan tat. Vui long chon chuyen bay khac.", YELLOW);
                cout << "----------------------------------------" << endl;
                return "";
            }
            else {
                cerr << status << endl;
            }
            cout << "----------------------------------------" << endl;

            if (canProcess) {
                return flightId;
            }
        }

        PrintLine("Khong tim thay chuyen bay voi ma " + flightId
            + " hoac trang thai khong hop le! Thu lai? Dung thi nhap (n/N): ", RED);
        char choice;
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            return "";
        }
        PrintLine("Nhap lai:", YELLOW);
    }
}

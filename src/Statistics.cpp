// Thong ke (Vinh)
#include "Screens.h"
#include "Console.h"
#include "DataFile.h"
#include "Flight.h"
#include "LinkedList.h"
#include "Utils.h"

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

static string FormatPercent(int part, int total) {
    ostringstream ss;
    ss << fixed << setprecision(1) << (total > 0 ? 100.0 * part / total : 0.0) << "%";
    return ss.str();
}

// Doc toan bo ChuyenBay.txt vao danh sach lien ket
static void LoadAllFlights(LinkedList<Flight>& flights) {
    for (const string& line : ReadLines(FILE_CHUYEN_BAY)) {
        Flight chuyenBay;
        if (chuyenBay.FromLine(line)) {
            flights.addTail(chuyenBay);
        }
    }
}

static void PrintFlightTable(LinkedList<Flight>& flights) {
    setTextColor(GREEN);
    cout << left << setw(10) << "Ma CB" << "| " << setw(11) << "Ngay" << "| " << setw(16) << "San bay den"
        << "| " << setw(11) << "Trang thai" << "| " << setw(8) << "So ve" << "| " << setw(12) << "Da dat/Tong"
        << "| " << "Lap day" << endl;
    ResetColor();

    for (Node<Flight>* p = flights._pHead; p != nullptr; p = p->_pNext) {
        const Flight& cb = p->_data;
        int daDat = (int)cb.GetDanhSachGheDaDat().size();
        string ghe = to_string(daDat) + "/" + to_string(cb.MaxSeat());

        cout << left << setw(10) << cb.GetIdFlight() << "| " << setw(11) << cb.GetDateStart() << "| "
            << setw(16) << cb.GetDestination() << "| " << setw(11) << StatusName(cb.GetStatus()) << "| "
            << setw(8) << cb.GetDanhSachVe().size() << "| " << setw(12) << ghe << "| "
            << FormatPercent(daDat, cb.MaxSeat()) << endl;
    }
    cout << right;
}

static void PrintOverview(LinkedList<Flight>& flights) {
    int soTheoTrangThai[4] = { 0, 0, 0, 0 };
    int tongVe = 0, tongGhe = 0, tongGheDaDat = 0;

    for (Node<Flight>* p = flights._pHead; p != nullptr; p = p->_pNext) {
        const Flight& cb = p->_data;
        string status = cb.GetStatus();
        if (status.size() == 1 && status[0] >= '0' && status[0] <= '3') {
            soTheoTrangThai[status[0] - '0']++;
        }
        tongVe += (int)cb.GetDanhSachVe().size();

        if (status != "0") { // chuyen bay bi huy khong tinh ghe
            tongGhe += cb.MaxSeat();
            tongGheDaDat += (int)cb.GetDanhSachGheDaDat().size();
        }
    }

    cout << endl;
    PrintLine("THONG KE TONG QUAN", YELLOW);
    cout << "Tong so chuyen bay          : " << flights.size() << endl;
    setTextColor(MAGENTA);
    cout << "   Huy: " << soTheoTrangThai[0];
    setTextColor(CYAN);
    cout << " | Con ve: " << soTheoTrangThai[1];
    setTextColor(RED);
    cout << " | Het ve: " << soTheoTrangThai[2];
    setTextColor(YELLOW);
    cout << " | Hoan tat: " << soTheoTrangThai[3] << endl;
    ResetColor();
    cout << "Tong so ve da dat           : " << tongVe << endl;
    cout << "Ghe (khong tinh chuyen huy) : " << tongGheDaDat << "/" << tongGhe << " da dat, con trong "
        << tongGhe - tongGheDaDat << endl;
    cout << "Ty le lap day trung binh    : " << FormatPercent(tongGheDaDat, tongGhe) << endl;
    cout << "Yeu cau dat ve dang cho     : " << ReadLines(FILE_XU_LY_DAT_VE).size() << endl;
}

static void PrintFlightDetail(const Flight& cb) {
    cout << endl;
    PrintLine("Da tim thay chuyen bay: ", GREEN);
    PrintLine("Ma chuyen bay: " + cb.GetIdFlight(), CYAN);
    PrintLine("Ngay: " + cb.GetDateStart(), MAGENTA);
    PrintLine("Diem den: " + cb.GetDestination(), BLUE);
    PrintLine("Trang thai: " + StatusName(cb.GetStatus()) + ".", YELLOW);

    int daDat = (int)cb.GetDanhSachGheDaDat().size();
    if (cb.MaxSeat() == 0) {
        PrintLine("Khong tim thay chuyen bay voi ma " + cb.GetIdFlight() + " trong " + FILE_PL_FL + "!", RED);
    }
    else {
        cout << "So cho ngoi: " << cb.MaxSeat() << " | Da dat: " << daDat
            << " | Con trong: " << cb.GetDanhSachGheTrong().size()
            << " | Ty le lap day: " << FormatPercent(daDat, cb.MaxSeat()) << endl;
    }

    const vector<Ticket>& dsVe = cb.GetDanhSachVe();
    if (dsVe.empty()) {
        cout << "Khong co ve nao trong chuyen bay nay." << endl;
    }
    else {
        cout << endl;
        PrintLine("Thong tin khach hang tren chuyen bay " + cb.GetIdFlight() + " (" + to_string(dsVe.size()) + " ve):", YELLOW);
        PrintLine("Ma ve|STT|So CMND|Ho Ten|Ghe", BLUE);
        for (const Ticket& ve : dsVe) {
            ve.Display();
            cout << endl;
        }
    }

    cout << endl;
    if (cb.GetStatus() == "2" || (cb.MaxSeat() > 0 && cb.GetDanhSachGheTrong().empty())) {
        PrintLine("Het ghe trong!", RED);
    }
    else if (cb.MaxSeat() > 0) {
        PrintLine("Danh sach ghe trong cho chuyen bay " + cb.GetIdFlight() + ":", GREEN);
        for (int ghe : cb.GetDanhSachGheTrong()) {
            cout << ghe << " ";
        }
        cout << endl;
    }
}

void SolveStatisticalConsole() {
    do {
        ClearScreen();
        PrintBanner({ "THONG KE" }, MAGENTA);
        cout << SEPARATOR << endl << endl;

        LinkedList<Flight> flights;
        LoadAllFlights(flights);
        if (flights.isEmpty()) {
            PrintLine("Chua co chuyen bay nao de thong ke!", RED);
            continue;
        }

        PrintFlightTable(flights);
        PrintOverview(flights);

        while (true) {
            setTextColor(WHITE);
            cout << endl << "Nhap ma chuyen bay de xem chi tiet (nhap 'z' de bo qua): " << endl;
            ResetColor();
            string input;
            cin >> input;
            if (input == "z" || input == "Z") break;

            string flightId = NormalizeId(input, "FL");
            Node<Flight>* found = flights.search([&](const Flight& cb) { return cb.GetIdFlight() == flightId; });
            if (found != nullptr) {
                PrintFlightDetail(found->_data);
                break;
            }
            PrintLine("Khong tim thay ma chuyen bay! Vui long nhap lai.", RED);
        }
    } while (ShowFooterMenu("thong ke"));
}

#include "Utils.h"
#include "Console.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

using namespace std;

vector<string> Split(const string& line, char delimiter, bool skipEmpty) {
    vector<string> parts;
    size_t start = 0;
    while (true) {
        size_t pos = line.find(delimiter, start);
        string token = line.substr(start, pos == string::npos ? string::npos : pos - start);
        if (!skipEmpty || !token.empty()) {
            parts.push_back(token);
        }
        if (pos == string::npos) break;
        start = pos + 1;
    }
    return parts;
}

string Trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";

    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

bool IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool IsValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return false;
    }
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (IsLeapYear(year)) {
        daysInMonth[1] = 29;
    }
    return day >= 1 && day <= daysInMonth[month - 1];
}

string NhapNgayThangNam() {
    while (true) {
        string input;
        cout << "Nhap ngay khoi hanh (dd/mm/yyyy): ";
        cin >> input;

        vector<string> parts = Split(input, '/');
        try {
            if (parts.size() != 3) throw invalid_argument("date");
            int day = stoi(parts[0]);
            int month = stoi(parts[1]);
            int year = stoi(parts[2]);

            if (IsValidDate(day, month, year)) {
                PrintLine("Ngay thang nam hop le: " + to_string(day) + "/" + to_string(month) + "/" + to_string(year), GREEN);
                return input;
            }
            PrintLine("Ngay thang nam khong hop le! Vui long nhap lai!", RED);
        }
        catch (...) {
            PrintLine("Dinh dang ngay thang khong dung! Vui long nhap lai theo kieu (dd/mm/yyyy).", RED);
        }
    }
}

string GenerateUniqueID(const string& prefix) {
    static mt19937 gen(random_device{}());
    uniform_int_distribution<> dis(100000, 999999);
    return prefix + to_string(dis(gen));
}

string NormalizeId(const string& input, const string& prefix) {
    string id = input;
    transform(id.begin(), id.end(), id.begin(), [](unsigned char c) { return (char)toupper(c); });
    if (id.compare(0, prefix.size(), prefix) == 0) {
        return id;
    }
    return prefix + id;
}

string FormatSeatCode(int soGhe) {
    ostringstream ss;
    ss << "Ghe_" << setw(3) << setfill('0') << soGhe;
    return ss.str();
}

string StatusName(const string& code) {
    if (code == "0") return "Huy";
    if (code == "1") return "Con Ve";
    if (code == "2") return "Het Ve";
    if (code == "3") return "Hoan Tat";
    return "Khong ro";
}

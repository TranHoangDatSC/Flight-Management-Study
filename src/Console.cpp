#include "Console.h"

#include <Windows.h>
#include <conio.h>
#include <climits>
#include <cstdlib>
#include <iostream>

using namespace std;

const int BANNER_WIDTH = 41; // So ky tu ben trong hai dau '*'

void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void ResetColor() {
    setTextColor(DEFAULT_COLOR);
}

void ClearScreen() {
    system("cls");
}

void PrintLine(const string& text, int color) {
    setTextColor(color);
    cout << text << endl;
    ResetColor();
}

void PrintBanner(initializer_list<string> titles, int color) {
    string border(BANNER_WIDTH + 2, '*');

    setTextColor(color);
    cout << border << endl;
    for (const string& title : titles) {
        int left = (BANNER_WIDTH - (int)title.size() + 1) / 2;
        int right = BANNER_WIDTH - (int)title.size() - left;
        cout << "*" << string(left, ' ') << title << string(right, ' ') << "*" << endl;
    }
    cout << border << endl;
    ResetColor();
}

bool TryReadInt(int& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return false;
    }
    return true;
}

int ReadChoice(int min, int max) {
    int choice;
    while (true) {
        if (!TryReadInt(choice)) {
            PrintLine("Vui long nhap lai so nguyen!", RED);
        }
        else if (choice < min || choice > max) {
            PrintLine("Nhap sai! Vui long nhap lai!", RED);
        }
        else {
            return choice;
        }
    }
}

bool ShowFooterMenu(const string& screenName) {
    bool coLamLai = !screenName.empty();

    cout << endl;
    setTextColor(CYAN);
    cout << "1. Quay ve man hinh chinh: " << endl;
    if (coLamLai) {
        setTextColor(YELLOW);
        cout << "2. Quay ve man hinh " << screenName << ": " << endl;
    }
    setTextColor(RED);
    cout << (coLamLai ? 3 : 2) << ". Thoat khoi chuong trinh: " << endl;
    ResetColor();

    int choice = ReadChoice(1, coLamLai ? 3 : 2);
    if (choice == 1) return false;
    if (coLamLai && choice == 2) return true;
    exit(0);
}

string GetPassword() {
    string password;
    setTextColor(DARK_CYAN);
    cout << "Password: ";
    setTextColor(CYAN);
    while (true) {
        char ch = _getch();
        if (ch == '\r') {
            break;
        }
        if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            cout << "*";
            password += ch;
        }
    }
    cout << endl;
    ResetColor();
    return password;
}

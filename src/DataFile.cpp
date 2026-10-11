#include "DataFile.h"
#include "Console.h"
#include "Utils.h"

#include <direct.h>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

// Ghep danh sach thanh chuoi, moi phan tu ket thuc bang ';' (vd "TK1;TK2;")
static string JoinList(const vector<string>& items) {
    string result;
    for (const string& item : items) {
        result += item + ";";
    }
    return result;
}

void EnsureDataFolders() {
    _mkdir(DATA_DIR.c_str());   // thu muc da ton tai thi _mkdir bo qua
    _mkdir(TICKET_DIR.c_str());
}

string TicketFileName(const string& ticketId) {
    return TICKET_DIR + ticketId + ".txt";
}

vector<string> ReadLines(const string& fileName) {
    vector<string> lines;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        line = Trim(line);
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    return lines;
}

bool WriteLines(const string& fileName, const vector<string>& lines) {
    ofstream file(fileName);
    if (!file.is_open()) {
        PrintLine("Khong the mo file " + fileName + " de ghi du lieu!", RED);
        return false;
    }
    for (const string& line : lines) {
        file << line << endl;
    }
    return true;
}

bool AppendLine(const string& fileName, const string& line) {
    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        PrintLine("Khong the mo file " + fileName + " de ghi du lieu!", RED);
        return false;
    }
    file << line << endl;
    return true;
}

bool IsEmptyFile(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        ofstream newFile(fileName);
        return true;
    }
    return ReadLines(fileName).empty();
}

bool CheckAdmin(const string& username, const string& password) {
    ifstream admin(FILE_ADMIN);
    if (!admin) {
        PrintLine("File " + FILE_ADMIN + " khong ton tai!", RED);
        return false;
    }

    string tmpUser, tmpPass;
    getline(admin, tmpUser);
    getline(admin, tmpPass);
    return username == Trim(tmpUser) && password == Trim(tmpPass);
}

bool IsCMNDUsedByOtherName(const string& name, const string& cmnd) {
    for (const string& line : ReadLines(FILE_KHACH_HANG)) {
        vector<string> parts = Split(line, '|');
        if (parts.size() >= 3 && parts[1] == cmnd && parts[2] != name) {
            return true;
        }
    }
    return false;
}

string FindFlightLine(const string& flightId) {
    for (const string& line : ReadLines(FILE_CHUYEN_BAY)) {
        if (Split(line, '|')[0] == flightId) {
            return line;
        }
    }
    return "";
}

vector<string> GetTicketIdsOfFlight(const string& flightId) {
    vector<string> parts = Split(FindFlightLine(flightId), '|');
    if (parts.size() < 5) {
        return vector<string>();
    }
    return Split(parts[4], ';', true);
}

bool UpdateTicketListOfFlight(const string& flightId, const string& ticketId, bool add) {
    vector<string> lines = ReadLines(FILE_CHUYEN_BAY);
    bool flightFound = false;

    for (string& line : lines) {
        vector<string> parts = Split(line, '|');
        if (parts[0] != flightId) continue;

        flightFound = true;
        parts.resize(max<size_t>(parts.size(), 5));
        vector<string> tickets = Split(parts[4], ';', true);
        if (add) {
            tickets.push_back(ticketId);
        }
        else {
            tickets.erase(remove(tickets.begin(), tickets.end(), ticketId), tickets.end());
        }

        line = parts[0] + "|" + parts[1] + "|" + parts[2] + "|" + parts[3] + "|" + JoinList(tickets);
    }

    if (!flightFound) {
        cout << "Chuyen bay " << flightId << " khong tim thay trong file " << FILE_CHUYEN_BAY << "!" << endl;
        return false;
    }
    return WriteLines(FILE_CHUYEN_BAY, lines);
}

bool ReadPlaneOfFlight(const string& flightId, string& planeId, int& seatCount) {
    for (const string& line : ReadLines(FILE_PL_FL)) {
        vector<string> parts = Split(line, '|');
        if (parts.size() >= 3 && parts[1] == flightId) {
            try {
                seatCount = stoi(parts[2]);
            }
            catch (...) {
                return false;
            }
            planeId = parts[0];
            return true;
        }
    }
    return false;
}

set<int> ReadBookedSeats(const string& flightId) {
    set<int> seats;
    for (const string& line : ReadLines(FILE_GHE_DA_DAT)) {
        vector<string> parts = Split(line, '|');
        if (parts[0] != flightId || parts.size() < 2) continue;

        for (const string& seat : Split(parts[1], ';', true)) {
            try {
                seats.insert(stoi(seat));
            }
            catch (...) {
                // bo qua ghe khong hop le
            }
        }
    }
    return seats;
}

bool WriteBookedSeats(const string& flightId, const set<int>& seats) {
    vector<string> seatList;
    for (int seat : seats) {
        seatList.push_back(to_string(seat));
    }
    string newLine = flightId + "|" + JoinList(seatList);

    vector<string> lines = ReadLines(FILE_GHE_DA_DAT);
    bool flightFound = false;
    for (string& line : lines) {
        if (Split(line, '|')[0] == flightId) {
            line = newLine;
            flightFound = true;
        }
    }
    if (!flightFound) {
        lines.push_back(newLine);
    }
    return WriteLines(FILE_GHE_DA_DAT, lines);
}

#include "Ticket.h"
#include "Console.h"
#include "DataFile.h"
#include "Utils.h"

#include <iostream>
#include <vector>

using namespace std;

void Ticket::GetInfo() {
    idVe = GenerateUniqueID("TK");
    cout << "Ma cua ve: " << idVe << endl;

    KhInfo.GetInfo();
    soThuTuGhe = FormatSeatCode(KhInfo.GetSTT());
}

void Ticket::GetFromFile(const string& fileIdVe, const string& fileSTT, const string& fileCMND,
    const string& fileHoTen, const string& fileSTTGhe) {
    idVe = fileIdVe;
    KhInfo.GetFromFile(fileSTT, fileCMND, fileHoTen);
    soThuTuGhe = fileSTTGhe;
}

bool Ticket::FromLine(const string& line) {
    vector<string> parts = Split(line, '|');
    if (parts.size() < 5) return false;
    try {
        GetFromFile(parts[0], parts[1], parts[2], parts[3], parts[4]);
    }
    catch (...) {
        return false; // so thu tu khong phai so
    }
    return true;
}

bool Ticket::LoadFromFile(const string& ticketId) {
    vector<string> lines = ReadLines(TicketFileName(ticketId));
    return !lines.empty() && FromLine(lines[0]);
}

string Ticket::ToLine() const {
    return idVe + "|" + KhInfo.ToLine() + "|" + soThuTuGhe;
}

void Ticket::SaveToFile() const {
    WriteLines(TicketFileName(idVe), { ToLine() });
}

void Ticket::SaveToFileSolve() const {
    if (AppendLine(FILE_XU_LY_DAT_VE, ToLine())) {
        PrintLine("Thong tin ve da duoc luu vao file " + FILE_XU_LY_DAT_VE, GREEN);
    }
}

void Ticket::Display() const {
    cout << ToLine();
}

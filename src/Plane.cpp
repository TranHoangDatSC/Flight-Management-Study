#include "Plane.h"
#include "Console.h"
#include "DataFile.h"
#include "Utils.h"

#include <iostream>

using namespace std;

void Plane::GetInfo() {
    idPlane = GenerateUniqueID("PL");
    cout << "So hieu may bay: " << idPlane << endl;
    cout << "Nhap so cho ngoi cua may bay: " << endl;

    while (true) {
        if (!TryReadInt(soChoNgoi) || soChoNgoi <= 0) {
            PrintLine("So cho ngoi phai la so nguyen duong lon hon khong! Vui long nhap lai!", RED);
        }
        else if (soChoNgoi > MAX_SO_GHE) {
            PrintLine("So cho ngoi khong duoc lon hon " + to_string(MAX_SO_GHE) + "! Vui long nhap lai!", RED);
        }
        else break;
    }
}

void Plane::GetFromFile(const string& fileId, const string& fileSoChoNgoi) {
    idPlane = fileId;
    soChoNgoi = stoi(fileSoChoNgoi);
}

void Plane::SaveToFile() const {
    if (AppendLine(FILE_MAY_BAY, idPlane + "|" + to_string(soChoNgoi))) {
        PrintLine("Thong tin cua may bay da duoc luu vao file " + FILE_MAY_BAY + "!", GREEN);
    }
}

void Plane::Display() const {
    cout << idPlane << "|" << soChoNgoi;
}

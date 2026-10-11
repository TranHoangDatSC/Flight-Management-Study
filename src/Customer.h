#pragma once

#include <string>

class Customer {
private:
    int soThuTu = 0;
    std::string soCMND;
    std::string hoTen;

public:
    void GetInfo();
    void GetFromFile(const std::string& fileSTT, const std::string& fileCMND, const std::string& fileHoTen);
    std::string ToLine() const; // STT|CMND|HoTen
    void SaveToFile() const;
    void Display() const;

    void SetSTT(int _stt) { soThuTu = _stt; }
    void SetCMND(const std::string& _cmnd) { soCMND = _cmnd; }
    void SetName(const std::string& _name) { hoTen = _name; }

    int GetSTT() const { return soThuTu; }
    std::string GetCMND() const { return soCMND; }
    std::string GetName() const { return hoTen; }
};

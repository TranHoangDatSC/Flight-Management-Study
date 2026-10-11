#pragma once

#include <string>

class Plane {
private:
    std::string idPlane;
    int soChoNgoi = 0;

public:
    void GetInfo();
    void GetFromFile(const std::string& fileId, const std::string& fileSoChoNgoi);
    void SaveToFile() const;
    void Display() const;

    void SetIdPlane(const std::string& _id) { idPlane = _id; }
    void SetSeatNumber(int _num) { soChoNgoi = _num; }
    std::string GetIdPlane() const { return idPlane; }
    int GetSeatNumber() const { return soChoNgoi; }
};

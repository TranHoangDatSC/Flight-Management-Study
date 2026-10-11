#pragma once

#include "Customer.h"

#include <string>

class Ticket {
private:
    std::string idVe;
    Customer KhInfo;
    std::string soThuTuGhe;

public:
    void GetInfo();
    void GetFromFile(const std::string& fileIdVe, const std::string& fileSTT, const std::string& fileCMND,
        const std::string& fileHoTen, const std::string& fileSTTGhe);

    // Doc tu dong "MaVe|STT|CMND|HoTen|MaGhe", tra ve false neu dong khong hop le
    bool FromLine(const std::string& line);
    // Doc tu file TKxxxxxx.txt cua ve
    bool LoadFromFile(const std::string& ticketId);
    std::string ToLine() const;

    void SaveToFile() const;       // Ghi file rieng cua ve (TKxxxxxx.txt)
    void SaveToFileSolve() const;  // Them vao danh sach cho xu ly (XuLyDatVe.txt)
    void Display() const;

    void SetIdTicket(const std::string& _id) { idVe = _id; }
    void SetCusInfo(const Customer& _kh) { KhInfo = _kh; }
    void SetSTTSeat(const std::string& _stt) { soThuTuGhe = _stt; }

    std::string GetIdTicket() const { return idVe; }
    const Customer& GetCusInfo() const { return KhInfo; }
    std::string GetSTTGhe() const { return soThuTuGhe; }
};

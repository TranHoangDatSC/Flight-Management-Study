#pragma once

#include "Plane.h"
#include "Ticket.h"

#include <set>
#include <string>
#include <vector>

class Flight {
private:
    std::string idFlight;
    Plane planeInfo;
    std::string ngayKhoiHanh;
    std::string sanBayDen;
    std::string trangThai; // "0": Huy, "1": Con ve, "2": Het ve, "3": Hoan tat
    std::vector<Ticket> danhSachVe;
    std::set<int> danhSachGheTrong;
    std::set<int> danhSachGheDaDat;

    void InitSeats();
    void GetInfoTicketFL();
    void SaveToBookedSeat() const;
    void SaveToPLFLFile() const;

public:
    void GetInfo();      // Nhap chuyen bay moi tu ban phim
    void SaveToFile() const;
    void Display() const;

    // Doc chuyen bay tu mot dong cua ChuyenBay.txt, kem theo may bay (PL_FL.txt),
    // ghe da dat (BookedSeat.txt) va thong tin cac ve (TKxxxxxx.txt)
    bool FromLine(const std::string& line);

    void SetIdFlight(const std::string& _id) { idFlight = _id; }
    std::string GetIdFlight() const { return idFlight; }

    void SetPlaneInfo(const Plane& _plane) { planeInfo = _plane; }
    const Plane& GetPlaneInfo() const { return planeInfo; }

    void SetDateStart(const std::string& _date) { ngayKhoiHanh = _date; }
    std::string GetDateStart() const { return ngayKhoiHanh; }

    void SetDestination(const std::string& _des) { sanBayDen = _des; }
    std::string GetDestination() const { return sanBayDen; }

    void SetStatus(const std::string& _st) { trangThai = _st; }
    std::string GetStatus() const { return trangThai; }

    void SetDanhSachVe(const std::vector<Ticket>& _ve) { danhSachVe = _ve; }
    const std::vector<Ticket>& GetDanhSachVe() const { return danhSachVe; }

    void SetDanhSachGheTrong(const std::set<int>& _gheTrong) { danhSachGheTrong = _gheTrong; }
    const std::set<int>& GetDanhSachGheTrong() const { return danhSachGheTrong; }

    void SetDanhSachGheDaDat(const std::set<int>& _gheDaDat) { danhSachGheDaDat = _gheDaDat; }
    const std::set<int>& GetDanhSachGheDaDat() const { return danhSachGheDaDat; }

    int MaxSeat() const { return planeInfo.GetSeatNumber(); }
};

#pragma once

#include <set>
#include <string>
#include <vector>

// ===== Ten cac file du lieu =====
// ChuyenBay.txt : MaCB|NgayKhoiHanh|SanBayDen|TrangThai|TKxxx;TKyyy;
// KhachHang.txt : STT|CMND|HoTen
// MayBay.txt    : MaMB|SoChoNgoi
// PL_FL.txt     : MaMB|MaCB|SoChoNgoi
// BookedSeat.txt: MaCB|1;2;4;
// XuLyDatVe.txt : MaVe|STT|CMND|HoTen|MaGhe   (cac yeu cau dat ve dang cho xu ly)
// TKxxxxxx.txt  : MaVe|STT|CMND|HoTen|MaGhe   (moi ve da duyet la mot file)
const std::string FILE_ADMIN = "Admin.txt";
const std::string FILE_CHUYEN_BAY = "ChuyenBay.txt";
const std::string FILE_KHACH_HANG = "KhachHang.txt";
const std::string FILE_MAY_BAY = "MayBay.txt";
const std::string FILE_PL_FL = "PL_FL.txt";
const std::string FILE_GHE_DA_DAT = "BookedSeat.txt";
const std::string FILE_XU_LY_DAT_VE = "XuLyDatVe.txt";

std::string TicketFileName(const std::string& ticketId);

// ===== Doc / ghi file chung =====
// Doc tat ca cac dong khong rong (da cat khoang trang 2 dau)
std::vector<std::string> ReadLines(const std::string& fileName);
// Ghi de toan bo file
bool WriteLines(const std::string& fileName, const std::vector<std::string>& lines);
bool AppendLine(const std::string& fileName, const std::string& line);
// File rong hoac chua ton tai (neu chua co thi tao file moi)
bool IsEmptyFile(const std::string& fileName);

// ===== Truy van du lieu =====
bool CheckAdmin(const std::string& username, const std::string& password);
// CMND da duoc dang ky voi mot ho ten khac trong KhachHang.txt
bool IsCMNDUsedByOtherName(const std::string& name, const std::string& cmnd);

// Dong du lieu cua chuyen bay trong ChuyenBay.txt, tra ve "" neu khong co
std::string FindFlightLine(const std::string& flightId);
std::vector<std::string> GetTicketIdsOfFlight(const std::string& flightId);
// Them (add = true) hoac xoa ma ve khoi danh sach ve cua chuyen bay
bool UpdateTicketListOfFlight(const std::string& flightId, const std::string& ticketId, bool add);

// Thong tin may bay cua chuyen bay trong PL_FL.txt
bool ReadPlaneOfFlight(const std::string& flightId, std::string& planeId, int& seatCount);

// Danh sach ghe da dat cua chuyen bay trong BookedSeat.txt
std::set<int> ReadBookedSeats(const std::string& flightId);
bool WriteBookedSeats(const std::string& flightId, const std::set<int>& seats);

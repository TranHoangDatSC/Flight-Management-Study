#pragma once

#include <string>
#include <vector>

const int MAX_SO_GHE = 100; // So cho ngoi toi da cua mot may bay

// Tach chuoi theo ky tu phan cach. Giu ca truong rong (vd "a||b|" -> a, "", b, "")
// tru khi skipEmpty = true.
std::vector<std::string> Split(const std::string& line, char delimiter, bool skipEmpty = false);
std::string Trim(const std::string& str);

bool IsLeapYear(int year);
bool IsValidDate(int day, int month, int year);
std::string NhapNgayThangNam();

// Sinh ma ngau nhien dang <prefix><6 chu so>, vd "FL637713"
std::string GenerateUniqueID(const std::string& prefix);

// Chuan hoa ma nguoi dung nhap: "637713" hoac "fl637713" -> "FL637713"
std::string NormalizeId(const std::string& input, const std::string& prefix);

// So thu tu ghe -> ma ghe, vd 4 -> "Ghe_004"
std::string FormatSeatCode(int soGhe);

// Ma trang thai chuyen bay -> ten hien thi, vd "1" -> "Con Ve"
std::string StatusName(const std::string& code);

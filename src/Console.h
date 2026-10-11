#pragma once

#include <initializer_list>
#include <string>

// Ma mau cua console Windows, dung cho setTextColor()
enum ConsoleColor {
    DARK_GREEN = 2,
    DARK_CYAN = 3,
    DARK_RED = 4,
    DARK_MAGENTA = 5,
    DARK_YELLOW = 6,
    DEFAULT_COLOR = 7,
    GRAY = 8,
    BLUE = 9,
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

const std::string SEPARATOR = "---------------------------------------------";

void setTextColor(int color);
void ResetColor();
void ClearScreen();

// In mot dong voi mau chi dinh, sau do tra ve mau mac dinh
void PrintLine(const std::string& text, int color);

// In khung tieu de dang:
// *******************************************
// *                 DAT VE                  *
// *******************************************
void PrintBanner(std::initializer_list<std::string> titles, int color);

// Doc mot so nguyen tu ban phim. Neu nhap sai kieu thi xoa bo dem va tra ve false
bool TryReadInt(int& value);

// Doc lua chon trong khoang [min, max], nhap sai thi bat nhap lai
int ReadChoice(int min, int max);

// Menu cuoi moi man hinh:
//   1. Quay ve man hinh chinh
//   2. Quay ve man hinh <screenName>   (chi hien khi screenName khac rong)
//   3. Thoat khoi chuong trinh
// Tra ve true neu nguoi dung muon lam lai man hinh hien tai.
bool ShowFooterMenu(const std::string& screenName = "");

// Nhap mat khau, hien thi dau '*'
std::string GetPassword();

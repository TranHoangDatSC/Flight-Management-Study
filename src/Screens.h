#pragma once

#include <string>

// ===== Man hinh nguoi dung (UserScreens.cpp) =====
void ListFlightConsole();   // Khanh
void OrderTicketConsole();  // Dat

// ===== Man hinh quan ly (AdminScreens.cpp) =====
void ManagementConsole();   // Vinh

// ===== Chuc nang cua admin =====
void SolveOrderTicketConsole();   // Dat   - OrderProcessing.cpp
void SolveReturnTicketConsole();  // Khanh - ReturnProcessing.cpp
void SolveStatisticalConsole();   // Vinh  - Statistics.cpp

// ===== Cac buoc dung chung cho man hinh admin (AdminScreens.cpp) =====
// Neu ChuyenBay.txt rong thi cho nhap mot chuyen bay moi. Tra ve true neu da tao moi.
bool CreateFlightIfEmpty();
// In danh sach chuyen bay hien tai trong ChuyenBay.txt
void PrintFlightList();
// Cho nhap ma chuyen bay cho den khi chon duoc chuyen bay co the xu ly.
// allowSoldOut: chuyen bay "Het ve" van duoc xu ly (dung cho tra ve).
// Tra ve ma chuyen bay, hoac "" neu nguoi dung dung lai / chuyen bay da hoan tat.
std::string SelectFlightToProcess(bool allowSoldOut);

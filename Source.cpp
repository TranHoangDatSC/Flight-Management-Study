#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <Windows.h>
#include <string>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <sstream>
#include <ctime>
#include <random>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

/*??t Code*/
vector<string> splitLine(string& line, char delimiter) {
    vector<string> parts;
    stringstream ss(line);
    string token;

    while (getline(ss, token, delimiter)) {
        parts.push_back(token);
    }

    return parts;
}
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";

    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}
void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
bool IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool IsValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return false;
    }
    vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (IsLeapYear(year)) {
        daysInMonth[1] = 29;
    }
    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }
    return true;
}
string NhapNgayThangNam() {
    string dateTime;
    while (true) {
        string input;
        cout << "Nhap ngay khoi hanh (dd/mm/yyyy): ";
        cin >> input;

        stringstream ss(input);
        string dayStr, monthStr, yearStr;
        getline(ss, dayStr, '/');
        getline(ss, monthStr, '/');
        getline(ss, yearStr, '/');

        try {
            int day = stoi(dayStr);
            int month = stoi(monthStr);
            int year = stoi(yearStr);

            if (IsValidDate(day, month, year)) {
                setTextColor(10); // Green
                cout << "Ngay thang nam hop le: " << day << "/" << month << "/" << year << endl;
                dateTime = dayStr + "/" + monthStr + "/" + yearStr;
                setTextColor(7); // Reset
                break;
            }
            else {
                setTextColor(12); // Red
                cout << "Ngay thang nam khong hop le! Vui long nhap lai!" << endl;
                setTextColor(7); // Reset
            }
        }
        catch (...) {
            setTextColor(12); // Red
            cout << "Dinh dang ngay thang khong dung! Vui long nhap lai theo kieu (dd/mm/yyyy)." << endl;
            setTextColor(7); // Reset
        }
    }
    return dateTime;
}


void tokenize(string& str, char delim, vector<string>& out) {
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

bool EmptyFile(string file) {
    ifstream ifile(file);
    if (!ifile) {
        ofstream newFile(file);
        newFile.close();
        return true;
    }
    return ifile.peek() == std::ifstream::traits_type::eof();
}
bool CheckAdmin(string username, string password) {
    string tmpUser, tmpPass;
    ifstream admin("Admin.txt");

    if (!admin) {
        setTextColor(12); // Red
        cout << "File Admin.txt khong ton tai!" << endl;
        return false;
    }

    getline(admin, tmpUser);
    getline(admin, tmpPass);

    if (username == tmpUser && password == tmpPass) {
        return true;
    }
    else return false;
}
string GenerateUniqueID(const string& prefix) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100000, 999999);
    int randomNumber = dis(gen);
    stringstream ss;
    ss << prefix << randomNumber;
    return ss.str();
}

class Plane {
private:
    string idPlane;
    int soChoNgoi;

public:
    void GetInfo() {
        idPlane = GenerateUniqueID("PL");
        cout << "So hieu may bay: " << idPlane << endl;
        cout << "Nhap so cho ngoi cua may bay: " << endl;

        while (true) {
            cin >> soChoNgoi;
            if (cin.fail() || soChoNgoi <= 0) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                setTextColor(12); // Red
                cout << "So cho ngoi phai la so nguyen duong lon hon khong! Vui long nhap lai!" << endl;
                setTextColor(7); // Reset
            }
            else if (soChoNgoi > 100) {
                setTextColor(12); // Red
                cout << "So cho ngoi khong duoc lon hon 100! Vui long nhap lai!" << endl;
                setTextColor(7); // Reset
            }
            else break;
        }
    }
    void GetFromFile(string fileId, string fileSoChoNgoi) {
        idPlane = fileId;
        soChoNgoi = stoi(fileSoChoNgoi);
    }
    void SaveToFile() {
        ofstream outFile("MayBay.txt", ios::app);
        if (outFile.is_open()) {
            outFile << idPlane << "|" << soChoNgoi << endl;
            outFile.close();
            setTextColor(10); // Green
            cout << "Thong tin cua may bay da duoc luu vao file MayBay.txt!" << endl;
            setTextColor(7); // Reset
        }
        else {
            setTextColor(12); // Red
            cerr << "Khong the mo file MayBay.txt de ghi du lieu!" << endl;
            setTextColor(7); // Reset
        }
    }
    void Display() {
        cout << idPlane << "|" << soChoNgoi;
    }

    void SetIdPlane(string _id) { idPlane = _id; }
    void SetSeatNumber(int _num) { soChoNgoi = _num; }
    string GetIdPlane() { return idPlane; }
    int GetSeatNumber() { return soChoNgoi; }
};
bool isValidCMND(string& cmnd) {
    return (cmnd.substr(0, 4) == "CMND");
}
bool isNameInFile(string name, string cmnd, string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << fileName << endl;
        return false;
    }

    string line, fileCMND, fileNameFromFile;
    while (getline(file, line)) {
        size_t firstSep = line.find('|');
        size_t secondSep = line.find('|', firstSep + 1);

        if (firstSep == string::npos || secondSep == string::npos) {
            continue;
        }

        fileCMND = line.substr(firstSep + 1, secondSep - firstSep - 1);
        fileNameFromFile = line.substr(secondSep + 1);

        if (fileCMND == cmnd && fileNameFromFile != name) {
            return true;
        }
    }
    return false;
}

class Customer {
private:
    int soThuTu;
    string soCMND;
    string hoTen;

public:
    void GetInfo() {
        setTextColor(9);
        cout << "Nhap so thu tu cua hang khach:" << endl;
        setTextColor(7); // Reset
        int cnt = 0;
        while (true) {
            cin >> soThuTu;
            if (cin.fail() || soThuTu <= 0) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                setTextColor(12); // Red
                cout << "So thu tu phai la so nguyen duong lon hon khong! Vui long nhap lai!" << endl;
                setTextColor(7); // Reset
            }
            else if (soThuTu > 100) {
                setTextColor(12); // Red
                cout << "So thu tu phai be hon 100!" << endl;
                setTextColor(7); // Reset
            }
            else {
                break;
            }
        }

        while (true) {
            setTextColor(10);
            cout << "Nhap so chung minh nhan dan cua hang khach: (Dang CMND******)" << endl;
            setTextColor(7); // Reset
            cin >> soCMND;
            if (isValidCMND(soCMND)) {
                break;
            }
            else {
                setTextColor(12); // Red
                cout << "CMND khong hop le!" << endl;
                setTextColor(7); // Reset 
            }
        }

        cin.ignore();
        while (true) {
            setTextColor(10);
            cout << "Nhap ho ten cua hang khach:" << endl;
            setTextColor(7); // Reset
            getline(cin, hoTen);

            if (isNameInFile(hoTen, soCMND, "KhachHang.txt")) {
                setTextColor(12); // Red
                cout << "Loi! Ten nay da duoc dang ky voi so CMND khac!" << endl;
                setTextColor(7); // Reset
            }
            else {
                break;
            }
        }
    }
    void GetFromFile(string fileSTT, string fileCMND, string fileHoTen) {
        soThuTu = stoi(fileSTT);
        soCMND = fileCMND;
        hoTen = fileHoTen;
    }
    void SaveToFile() {
        ofstream outFile("KhachHang.txt", ios::app);
        if (outFile.is_open()) {
            outFile << soThuTu << "|" << soCMND << "|" << hoTen << endl;
            outFile.close();
            setTextColor(10); // Green
            cout << "Thong tin khach hang da duoc luu vao file KhachHang.txt!" << endl;
            setTextColor(7); // Reset
        }
        else {
            setTextColor(12); // Red
            cerr << "Khong the mo file KhachHang.txt de ghi du lieu!" << endl;
            setTextColor(7); // Reset
        }
    }
    void Display() {
        cout << soThuTu << "|" << soCMND << "|" << hoTen;
    }

    void SetSTT(int _stt) { soThuTu = _stt; }
    void SetCMND(string _cmnd) { soCMND = _cmnd; }
    void SetName(string _name) { hoTen = _name; }

    int GetSTT() { return soThuTu; }
    string GetCMND() { return soCMND; }
    string GetName() { return hoTen; }

};
class Ticket : Customer {
private:
    string idVe;
    Customer KhInfo;
    string soThuTuGhe;
public:
    void GetInfo() {
        idVe = GenerateUniqueID("TK");
        cout << "Ma cua ve: " << idVe << endl;

        KhInfo.GetInfo();

        if (KhInfo.GetSTT() < 10) {
            soThuTuGhe = "Ghe_00" + to_string(KhInfo.GetSTT());
        }
        else soThuTuGhe = "Ghe_0" + to_string(KhInfo.GetSTT());
    }
    void GetFromFile(string fileIdVe, string fileSTT, string fileCMND
        , string fileHoTen, string fileSTTGhe) {
        idVe = fileIdVe;
        KhInfo.GetFromFile(fileSTT, fileCMND, fileHoTen);
        soThuTuGhe = fileSTTGhe;
    }
    void SaveToFile() {
        string fileName = idVe + ".txt";
        ofstream outFile(fileName);
        if (outFile.is_open()) {
            outFile << idVe << "|"
                << KhInfo.GetSTT() << "|"
                << KhInfo.GetCMND() << "|"
                << KhInfo.GetName() << "|"
                << soThuTuGhe << endl;
        }
        else {
            setTextColor(12); // Red
            cerr << "Khong the mo file " << fileName << " de ghi du lieu!" << endl;
            setTextColor(7); // Reset
        }
        outFile.close();
    }

    void SaveToFileSolve() {
        string fileName = "XuLyDatVe.txt";
        ofstream outFile(fileName, ios::app);
        if (outFile.is_open()) {
            outFile << idVe << "|"
                << KhInfo.GetSTT() << "|"
                << KhInfo.GetCMND() << "|"
                << KhInfo.GetName() << "|"
                << soThuTuGhe << endl;
            outFile.close();
            setTextColor(10); // Green
            cout << "Thong tin ve da duoc luu vao file " << fileName << endl;
            setTextColor(7); // Reset
        }
        else {
            setTextColor(12); // Red
            cerr << "Khong the mo file " << fileName << " de ghi du lieu!" << endl;
            setTextColor(7); // Reset
        }
    }

    void Display() {
        cout << idVe << "|";
        KhInfo.Display();
        cout << "|" << soThuTuGhe;
    }

    void SetIdTicket(string _id) { idVe = _id; }
    void SetCusInfo(Customer _kh) { KhInfo = _kh; }
    void SetSTTSeat(string _stt) { soThuTuGhe = _stt; }

    string GetIdTicket() { return idVe; }
    Customer GetCusInfo() { return KhInfo; }
    string GetSTTGhe() { return soThuTuGhe; }
};

class Flight : public Plane {
private:
    string idFlight;
    Plane planeInfo;
    string ngayKhoiHanh;
    string sanBayDen;
    string trangThai;
    vector<Ticket> danhSachVe;
    set<int> danhSachGheTrong;
    set<int> danhSachGheDaDat;

public:
    void SetIdFlight(string _id) { idFlight = _id; }
    string GetIdFlight() { return idFlight; }

    void SetPlaneInfo(Plane _plane) { planeInfo = _plane; }
    Plane GetPlaneInfo() { return planeInfo; }

    void SetDateStart(string _date) { ngayKhoiHanh = _date; }
    string GetDateStart() { return ngayKhoiHanh; }

    void SetDestination(string _des) { sanBayDen = _des; }
    string GetDestination() { return sanBayDen; }

    void SetStatus(string _st) { trangThai = _st; }
    string GetStatus() { return trangThai; }

    void SetDanhSachVe(vector<Ticket>& _ve) { danhSachVe = _ve; }
    vector<Ticket> GetDanhSachVe() { return danhSachVe; }

    void SetDanhSachGheTrong(set<int>& _gheTrong) { danhSachGheTrong = _gheTrong; }
    set<int> GetDanhSachGheTrong() { return danhSachGheTrong; }

    void SetDanhSachGheDaDat(set<int>& _gheDaDat) { danhSachGheDaDat = _gheDaDat; }
    set<int> GetDanhSachGheDaDat() { return danhSachGheDaDat; }

    int MaxSeat() { return GetPlaneInfo().GetSeatNumber(); }

    void InitSeats() {
        danhSachGheTrong.clear();
        for (int i = 1; i <= planeInfo.GetSeatNumber(); ++i) {
            danhSachGheTrong.insert(i);
        }
        danhSachGheDaDat.clear();
    }


    void GetInfo() {
        SetIdFlight(GenerateUniqueID("FL"));
        cout << "Ma cua chuyen bay: " << GetIdFlight() << endl;

        planeInfo.GetInfo();
        planeInfo.SaveToFile();

        InitSeats();
        SetDateStart(NhapNgayThangNam());

        cout << endl;
        cin.ignore();
        cout << "San bay den: ";
        do {
            getline(cin, sanBayDen);
            if (sanBayDen.empty()) {
                setTextColor(12); // Red
                cout << "Vui long nhap lai! San bay den khong duoc de trong.\n";
                setTextColor(7); // Reset
            }
        } while (sanBayDen.empty());

        while (true) {
            cout << "Nhap trang thai cua chuyen bay ";
            setTextColor(13); // Purple
            cout << "(0: Huy,";
            setTextColor(11); // Blue Light
            cout << " 1 : Con Ve,";
            setTextColor(12); // Red
            cout << " 2 : Het Ve,";
            setTextColor(14); // Yellow
            cout << " 3 : Hoan Tat) : ";
            setTextColor(7); // Reset
            cin >> trangThai;
            if (cin.fail() || (trangThai != "0" && trangThai != "1" && trangThai != "2" && trangThai != "3")) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                setTextColor(12); // Red
                cout << "Trang thai khong hop le. Vui long nhap lai." << endl;
                setTextColor(7); // Reset
            }
            else {
                break;
            }
        }

        GetInfoTicketFL();
    }

    void GetInfoTicketFL() {
        cout << endl;
        setTextColor(14); // Yellow
        cout << "Nhap danh sach ve:\n";
        while (true) {
            setTextColor(11); // Light Blue
            cout << "Nhap bat ky de tiep tuc, nhap 'x' de dung: ";
            setTextColor(7); // Reset
            char choice;
            cin >> choice;

            if (choice == 'x' || choice == 'X') break;

            setTextColor(10); // Green
            cout << "\nHien thi danh sach ghe trong:\n";
            setTextColor(7); // Reset
            for (int ghe : danhSachGheTrong) {
                cout << ghe << " ";
            }
            cout << endl;

            Ticket ve;
            while (true) {
                ve.GetInfo();
                int soGhe = ve.GetCusInfo().GetSTT();

                if (soGhe < 1 || soGhe > GetPlaneInfo().GetSeatNumber()) {
                    setTextColor(12); // Red
                    cout << "So thu tu ghe khong hop le! Vui long nhap lai tu dau!" << endl;
                    setTextColor(7); // Reset
                }
                else if (danhSachGheTrong.find(soGhe) == danhSachGheTrong.end()) {
                    setTextColor(12); // Red
                    cout << "Ghe nay da duoc dat! Vui long chon ghe khac." << endl;
                    setTextColor(7); // Reset
                }
                else {
                    danhSachGheTrong.erase(soGhe);
                    danhSachGheDaDat.insert(soGhe);
                    ve.GetCusInfo().SaveToFile();
                    ve.SaveToFile();
                    break;
                }
            }
            danhSachVe.push_back(ve);
        }
    }

    void SaveToBookedSeat() {
        ofstream outFile("BookedSeat.txt", ios::app);
        if (outFile.is_open()) {
            outFile << idFlight << "|";

            for (auto& ghe : danhSachGheDaDat) {
                outFile << ghe << ";";
            }
            outFile << endl;
            outFile.close();
            setTextColor(10); // Green
            cout << "Danh sach ghe da dat da duoc luu vao file BookedSeat.txt." << endl;
            setTextColor(7); // Reset
        }
        else {
            setTextColor(12); // Red
            cerr << "Khong the mo file BookedSeat.txt de ghi du lieu!" << endl;
            setTextColor(7); // Reset
        }
    }



    void SaveToFile() {
        ofstream outFile("ChuyenBay.txt", ios::app);
        if (outFile.is_open()) {
            outFile << idFlight << "|" << ngayKhoiHanh << "|" << sanBayDen << "|" << trangThai << "|";
            for (auto& ve : danhSachVe) {
                outFile << ve.GetIdTicket() << ";";
            }
            outFile << endl;
            outFile.close();

            setTextColor(10); // Green
            cout << "Thong tin chuyen bay da duoc luu vao file ChuyenBay.txt." << endl;
            setTextColor(7); // Reset
        }
        else {
            setTextColor(12); // Red
            cerr << "Khong the mo file ChuyenBay.txt de ghi du lieu!" << endl;
            setTextColor(7); // Reset
        }
        SaveToBookedSeat();
        SaveToPLFLFile();
    }

    void SaveToPLFLFile() {
        ofstream outFile("PL_FL.txt", ios::app);
        if (outFile.is_open()) {
            outFile << planeInfo.GetIdPlane() << "|";
            outFile << GetIdFlight() << "|";
            outFile << GetPlaneInfo().GetSeatNumber() << endl;

            outFile.close();
            setTextColor(10);
            cout << "Da luu vao file PL_FL.txt." << endl;
            setTextColor(7);
        }
        else {
            setTextColor(12);
            cerr << "Khong mo duoc file PL_FL.txt!" << endl;
            setTextColor(7);
        }
    }


    void Display() {
        string status;
        if (trangThai == "0") status = "Huy";
        else if (trangThai == "1") status = "Con Ve";
        else if (trangThai == "2") status = "Het Ve";
        else if (trangThai == "3") status = "Hoan Tat";

        cout << idFlight << "|" << ngayKhoiHanh << "|" << sanBayDen << "|" << status << "|";
        for (auto& ve : danhSachVe) {
            ve.Display();
        }
        cout << endl;

        cout << "Danh sach ghe trong: ";
        for (int ghe : danhSachGheTrong) {
            cout << ghe << " ";
        }
        cout << endl;
    }
};
/*??t Code t?t c? các hàm phía trên*/

void ListFlightConsole(); /*Khanh Code*/
void OrderTicketConsole(); /*??t Code*/
void OrderTicket(); /*??t Code*/

void ManagementConsole(); /*Vinh Code*/
string GetPassword();  /*Vinh Code*/
void AdminConsole();  /*Vinh Code*/ 

void SolveOrderTicketConsole(); /*??t Code*/
void SolveOrderTicket(string line, string flightId); /*??t Code*/
bool IsSeatBooked(string flightId, int stt); /*??t Code*/
bool FindTicketInFileSolve(string flightId, string ticketId); /*??t Code*/
void AddSeatToFile(string flightId, int stt); /*??t Code*/
void AddCustomerFromTicket(string ticketId, string flightId); /*??t Code*/
void RemoveSolve(vector<string>& veChuaXuLy); /*??t Code*/

void SolveReturnTicketConsole(); /*Khanh Code*/ 
void SolveReturnTicket(string line, string flightId); /*Khanh Code*/ 
bool FindTicketInFileFlight(string ticketId); /*Khanh Code*/ 
void RemoveTicketFromFlight(string ticketId, string flightId); /*Khanh Code*/ 
void RemoveCustomer(string ticketId, string flightId); /*Khanh Code*/ 
void DeleteSeat(string flightId, int stt); /*Khanh Code*/ 

void SolveStatisticalConsole();  /*Vinh Code*/ 
void DisplayCustomerInfo(vector<string>& ticketFiles, string flightId);  /*Vinh Code*/
void DisplayEmptySeats(string flightId);  /*Vinh Code*/


/*Khanh Code Node + LinkedList*/
template <class DataType>
class Node
{
public:
    DataType _data;
    Node* _pNext;
public:
    Node(DataType data);
    void display();
};

template <class DataType>
Node<DataType>::Node(DataType data)
{
    _data = data;
    _pNext = NULL;
}

template <class DataType>
void Node<DataType>::display()
{
    _data.Display();
}

template <class DataType>
class LinkedList
{
public:
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;

    LinkedList();
    ~LinkedList();
    void addTail(DataType data);
    Node<DataType>* search(DataType data);
    void display();
    void remove(DataType data);
};

template <class DataType>
LinkedList<DataType>::LinkedList()
{
    _pHead = NULL;
    _pTail = NULL;
    _iSize = 0;
}

template <class DataType>
void LinkedList<DataType>::addTail(DataType data)
{
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (_pHead == NULL)
    {
        _pHead = _pTail = pAdd;
    }
    else
    {
        _pTail->_pNext = pAdd;
        _pTail = pAdd;
    }
    _iSize++;
}

template <class DataType>
void LinkedList<DataType>::display()
{
    Node<DataType>* pWalker = _pHead;
    while (pWalker != NULL) {
        pWalker->display();
        pWalker = pWalker->_pNext;
    }
}

template <class DataType>
Node<DataType>* LinkedList<DataType>::search(DataType data)
{
    Node<DataType>* p = _pHead;
    while ((p != NULL) && (p->_data.ID != data.ID))
    {
        p = p->_pNext;
    }
    return p;
}

template <class DataType>
void LinkedList<DataType>::remove(DataType data)
{
    Node<DataType>* pWalker = _pHead, * pTemp = NULL;
    if (pWalker->_data == _pHead->_data)
    {
        pTemp = _pHead->_pNext;
        _pHead = pTemp;
        delete pWalker;
        return;
    }
    while ((pWalker != NULL) && (pWalker->_data != data))
    {
        pTemp = pWalker; pWalker = pWalker->_pNext;
    }
    if (pWalker == NULL) return;
    if (pTemp != NULL)
    {
        if (pWalker == _pTail)
        {
            _pTail = pTemp;
            _pTail->_pNext = NULL;
        }
        pTemp->_pNext = pWalker->_pNext;
        delete pWalker;
        _iSize--;
    }
}

template <class DataType>
LinkedList<DataType>::~LinkedList()
{
    Node<DataType>* pWalker = _pHead;
    while (pWalker != NULL)
    {
        Node<DataType>* pTemp = pWalker;
        pWalker = pWalker->_pNext;
        delete pTemp;
    }
    _pHead = _pTail = NULL;
    _iSize = 0;
}

int main()
{
    setTextColor(11); // Light Blue
    cout << "*******************************************" << endl;
    cout << "*           CHUONG TRINH QUAN LY          *" << endl;
    cout << "*                CHUYEN BAY               *" << endl;
    cout << "*******************************************" << endl;
    cout << endl;

    setTextColor(10); // Green
    cout << "1. Hien thi danh sach cac chuyen bay:" << endl;
    setTextColor(14); // Yellow
    cout << "2. Dat ve:" << endl;
    setTextColor(9); // Pink
    cout << "3. Quan ly:" << endl;
    setTextColor(12); // Red
    cout << "4. Thoat:" << endl;
    cout << endl;
    int choice;

    setTextColor(7); // Reset
    cout << "Vui long nhap lua chon: ";
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            setTextColor(12); // Red
            cout << "Vui long nhap lai so nguyen!" << endl;
            setTextColor(7); // Reset
            continue;
        }
        switch (choice) {
        case 1: {
            ListFlightConsole();
            break;
        }
        case 2: {
            OrderTicketConsole();
            break;
        }
        case 3: {
            ManagementConsole();
            break;
        }
        case 4:
        {
            exit(0);
            break;
        }
        default: {
            setTextColor(6); // Red
            cout << "Nhap sai! Vui long nhap lai!" << endl;
            setTextColor(7); // Reset
        }
        }
    }
    return 0;
}

void ListFlightConsole() {
    system("cls");
    string file = "ChuyenBay.txt";

    if (EmptyFile(file)) {
        setTextColor(12); // Red
        cout << "File rong! Vui long nhap them thong tin cua chuyen bay:" << endl << endl;
        setTextColor(7); // Reset
        Flight chuyenBay;
        chuyenBay.GetInfo();
        chuyenBay.SaveToFile();

        setTextColor(11); // Light Blue
        cout << "1. Quay ve man hinh chinh: " << endl;
        setTextColor(12); // Red
        cout << "2. Thoat khoi chuong trinh: " << endl;
        setTextColor(7); // Reset

        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                setTextColor(12); // Red
                cout << "Vui long nhap lai so nguyen!" << endl;
                setTextColor(7); // Reset
                continue;
            }
            switch (choice) {
            case 1: {
                system("cls");
                main();
                break;
            }
            case 2: {
                exit(0);
                break;
            }
            default: {
                setTextColor(6); // Red
                cout << "Nhap sai! Vui long nhap lai!" << endl;
                setTextColor(7); // Reset
            }
            }
        }
    }
    else if (!EmptyFile(file)) {
        setTextColor(10); // Green
        cout << "Ma chuyen bay|Ngay khoi hanh|San bay den|Trang thai|Danh sach ve " << endl;
        fstream f;
        setTextColor(7); // Reset
        f.open(file);
        string line;;

        while (!f.eof()) {
            getline(f, line); cout << line << endl;
        } f.close();

        setTextColor(14); // Yellow
        cout << "Vui long chon lua chon: " << endl;
        cout << endl;

        setTextColor(11); // Light Blue
        cout << "1. Quay ve man hinh chinh: " << endl;
        setTextColor(12); // Red
        cout << "2. Thoat khoi chuong trinh: " << endl;
        setTextColor(7); // Reset

        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                setTextColor(12); // Red
                cout << "Vui long nhap lai so nguyen!" << endl;
                setTextColor(7); // Reset
                continue;
            }
            switch (choice) {
            case 1: {
                system("cls");
                main();
                break;
            }
            case 2: {
                exit(0);
                break;
            }
            default: {
                setTextColor(6); // Red
                cout << "Nhap sai! Vui long nhap lai!" << endl;
                setTextColor(7); // Reset
            }
            }
        }
    }
}

void OrderTicketConsole() {
    system("cls");

    setTextColor(10); // Green
    cout << "*******************************************" << endl;
    cout << "*                 DAT VE                  *" << endl;
    cout << "*******************************************" << endl;
    cout << endl;

    setTextColor(13); // Purple
    cout << "1. Dat ve:" << endl;
    setTextColor(11); // Light Blue
    cout << "2. Quay ve man hinh chinh: " << endl;
    setTextColor(12); // Red
    cout << "3. Thoat khoi chuong trinh: " << endl;

    setTextColor(7); // Reset
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            setTextColor(12); // Red
            cout << "Vui long nhap lai so nguyen!" << endl;
            setTextColor(7); // Reset
            continue;
        }
        switch (choice) {
        case 1: {
            OrderTicket();
            break;
        }
        case 2: {
            system("cls");
            main();
            break;
        }
        case 3: {
            exit(0);
            break;
        }
        default: {
            setTextColor(6); // Red
            cout << "Nhap sai! Vui long nhap lai!" << endl;
            setTextColor(7); // Reset
        }
        }
    }
}

void OrderTicket() {
    Ticket newTicket;
    LinkedList<Ticket> ticketList;

    newTicket.GetInfo();
    ticketList.addTail(newTicket);

    newTicket.SaveToFileSolve();
    setTextColor(12); // Yellow
    cout << "Hay cho doi Admin xu ly!" << endl << endl;

    setTextColor(7); // Reset
    cout << "Hien thi lai thong tin cua ve: " << endl;
    ticketList.display();

    setTextColor(11); // Light Blue
    cout << endl << "1. Quay ve man hinh chinh: " << endl;
    setTextColor(12); // Red
    cout << "2. Thoat khoi chuong trinh: " << endl;

    setTextColor(7); // Reset
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            setTextColor(12); // Red
            cout << "Vui long nhap lai so nguyen!" << endl;
            setTextColor(7); // Reset
            continue;
        }
        switch (choice) {
        case 1: {
            system("cls");
            main();
            break;
        }
        case 2: {
            exit(0);
            break;
        }
        default: {
            setTextColor(6); // Red
            cout << "Nhap sai! Vui long nhap lai!" << endl;
            setTextColor(7); // Reset
        }
        }
    }
}
string GetPassword() {
    string password;
    char ch;
    setTextColor(3); // Blue 
    cout << "Password: ";
    while (true) {
        setTextColor(11); // Blue Light
        ch = _getch();
        if (ch == '\r') {
            break;
        }
        else if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            cout << "*";
            password += ch;
        }
    }
    cout << endl;
    return password;
}
void ManagementConsole() {
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    setTextColor(14); // Yellow
    cout << "*******************************************" << endl;
    cout << "*            DANG NHAP HE THONG           *" << endl;
    cout << "*******************************************" << endl;
    string username;
    string password;
    int count = 0;
    while (true) {

        setTextColor(3); // Blue
        cout << "User:      ";
        setTextColor(11); // Light Blue
        cin >> username;
        setTextColor(14); // Yellow
        password = GetPassword();

        setTextColor(7); // Reset
        if (CheckAdmin(username, password)) {
            cout << "Dang nhap thanh cong!" << endl;
            AdminConsole();
            break;
        }
        else {
            setTextColor(12); // Red
            cout << "Tai khoan hoac mat khau khong dung. Vui long thu lai!" << endl;
            setTextColor(7); // Reset
            count += 1;
        }
        if (count == 3) {
            setTextColor(12); // Red
            cout << "Ban da nhap sai qua 3 lan. Dang xuat chuong trinh!" << endl;
            exit(0);
        }
    }
}

void AdminConsole() {
    system("cls");
    setTextColor(2); // Green

    cout << "Chao mung den voi giao dien quan ly he thong!" << endl;
    setTextColor(8); // Gray
    cout << "---------------------------------------------" << endl;

    int choice;

    setTextColor(10); // Green
    cout << "1. Xu ly dat ve                   " << endl;
    setTextColor(14); // Yellow
    cout << "2. Xu ly tra ve                   " << endl;
    setTextColor(13); // Purple
    cout << "3. Thong ke                       " << endl;
    setTextColor(11); // Light Blue
    cout << "4. Quay ve man hinh chinh:        " << endl;
    setTextColor(12); // Red
    cout << "5. Thoat khoi chuong trinh:       " << endl;
    setTextColor(8); // Gray
    cout << "---------------------------------------------" << endl;
    setTextColor(7); // Reset
    cout << "Xin vui long nhap lua chon: ";

    cin >> choice;

    switch (choice) {
    case 1: {
        SolveOrderTicketConsole();
        break;
    }
    case 2: {
        SolveReturnTicketConsole();
        break;
    }
    case 3: {
        SolveStatisticalConsole();
        break;
    }
    case 4: {
        system("cls");
        main();
        break;
    }
    case 5: {
        exit(0);
        break;
    }
    default: {
        setTextColor(12); // Red
        cout << "Nhap sai!! Vui long nhap lai!";
    }
    }
}
void SolveOrderTicketConsole() {
    system("cls");
    setTextColor(2); // Green
    cout << "*******************************************" << endl;
    cout << "*               XU LY DAT VE              *" << endl;
    cout << "*******************************************" << endl;
    setTextColor(7); // Reset
    cout << "---------------------------------------------" << endl;

    string flightFile = "ChuyenBay.txt";
    ifstream inFile(flightFile);
    Flight chuyenBay;

    if (!inFile.is_open()) {
        cerr << "Khong the mo file ChuyenBay.txt!" << endl;
        return;
    }
    else if (EmptyFile(flightFile)) {
        setTextColor(12); // Red
        cout << "File rong! Vui long nhap them thong tin cua chuyen bay:" << endl << endl;
        setTextColor(7); // Reset
        chuyenBay.GetInfo();
        chuyenBay.SaveToFile();
        cout << endl;

        cout << "Da khoi tao du lieu cho file ChuyenBay.txt!" << endl;
        setTextColor(11); // Light Blue
        cout << "1. Quay ve man hinh chinh: " << endl;
        setTextColor(12); // Red
        cout << "2. Thoat khoi chuong trinh: " << endl;

        setTextColor(7); // Reset

        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                setTextColor(12); // Red
                cout << "Vui long nhap lai so nguyen!" << endl;
                setTextColor(7); // Reset
                continue;
            }
            switch (choice) {
            case 1: {
                system("cls");
                main();
                break;
            }
            case 2: {
                exit(0);
                break;
            }
            default: {
                setTextColor(12); // Red
                cout << "Nhap sai! Vui long nhap lai!" << endl;
                setTextColor(7); // Reset
            }
            }
        }
    }
    else {
        cout << "Hien thi cac chuyen bay hien tai:" << endl;
        setTextColor(10); // Green
        cout << "Ma chuyen bay|Ngay khoi hanh|San bay den|Trang thai|Danh sach ve" << endl;
        setTextColor(7); // Reset
        ifstream f(flightFile);
        string line;

        while (getline(f, line)) {
            line = trim(line);
            if (!line.empty()) {
                cout << line << endl;
            }
        }
        f.close();

        cout << "\nHien thi cac yeu cau xu ly dat ve:" << endl;
        setTextColor(14); // Yellow
        cout << "Ma ve|So thu tu|So CMND|Ho Ten|Ma ghe ngoi" << endl;
        setTextColor(7); // Reset
        ifstream ff("XuLyDatVe.txt");
        string linee;

        while (getline(ff, linee)) {
            linee = trim(linee);
            if (!linee.empty()) {
                cout << linee << endl;
            }
        }
        ff.close();
    }

    setTextColor(13); // Purple
    cout << endl << "Nhap vao cac so cuoi cua ma chuyen bay:" << endl;
    setTextColor(7); // Reset
    while (true) {
        string cacSoCuoi;
        cin >> cacSoCuoi;
        string flightId = "FL" + cacSoCuoi;

        ifstream flightStream(flightFile);
        string line;
        bool found = false;

        while (getline(flightStream, line)) {
            if (line.find(flightId) != string::npos) {
                found = true;

                vector<string> parts;
                stringstream ss(line);
                string token;

                while (getline(ss, token, '|')) {
                    parts.push_back(token);
                }

                string id = parts[0];
                string status = parts[3];
                setTextColor(10); // Green
                cout << "Da tim thay chuyen bay: " << line << endl;
                setTextColor(7); // Reset

                if (status == "0") {
                    setTextColor(4); // Red
                    cout << "Trang thai: Huy. Vui long chon chuyen bay khac!" << endl;
                    setTextColor(14); // Yellow
                    cout << "Xin quy khach hay den quay thanh toan de lay lai tien va mang theo ve de xac minh!" << endl;
                    setTextColor(7); // Reset
                    found = false;
                }

                else if (status == "1") {
                    setTextColor(5); // Purple
                    cout << "Trang thai: Con ve. Ban co the tiep tuc." << endl;
                    setTextColor(7); // Reset
                    SolveOrderTicket(line, flightId);
                }
                else if (status == "2") {
                    setTextColor(12); // Red Dark
                    cout << "Trang thai: Het ve. Vui long chon chuyen bay khac." << endl;
                    setTextColor(7); // Reset
                    found = false;
                }
                else if (status == "3") {
                    setTextColor(14); // Dark Yellow
                    cout << "Trang thai: Hoan tat. Vui long chon chuyen bay khac." << endl;
                    setTextColor(7); // Reset
                    found = true;
                }
                else {
                    cerr << status << endl;
                }
                cout << "----------------------------------------" << endl;
            }
        }
        flightStream.close();

        if (found) {
            break;
        }
        else {
            setTextColor(12); // Red
            cout << "Khong tim thay chuyen bay voi ma " << flightId
                << " hoac trang thai khong hop le! Thu lai? Dung thi nhap (n/N): " << endl;
            setTextColor(7); // Reset
            char choice;
            cin >> choice;
            setTextColor(14); // Yellow
            if (choice == 'n' || choice == 'N') {
                exit(0);
            }
            else cout << "Nhap lai:" << endl;
            setTextColor(7); // Reset
        }
    }

    setTextColor(11); // Light Blue
    cout << "1. Quay ve man hinh chinh: " << endl;
    setTextColor(14); // Yellow
    cout << "2. Quay ve man hinh xu ly dat ve: " << endl;
    setTextColor(12); // Red
    cout << "3. Thoat khoi chuong trinh: " << endl;

    setTextColor(7); // Reset

    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            setTextColor(12); // Red
            cout << "Vui long nhap lai so nguyen!" << endl;
            setTextColor(7); // Reset
            continue;
        }
        switch (choice) {
        case 1: {
            system("cls");
            main();
            break;
        }
        case 2: {
            system("cls");
            SolveOrderTicketConsole();
            break;
        }
        case 3: {
            exit(0);
            break;
        }
        default: {
            setTextColor(12); // Red
            cout << "Nhap sai! Vui long nhap lai!" << endl;
            setTextColor(7); // Reset
        }
        }
    }
}


void SolveOrderTicket(string line, string flightId) {
    while (true) {
        string cacSoCuoi;
        cout << endl << "Nhap vao cac so cuoi cua ma ve can xu ly dat ve hoac nhap 'z' de dung:" << endl;
        cin >> cacSoCuoi;
        string ticketId = "TK" + cacSoCuoi;

        if (FindTicketInFileSolve(flightId, cacSoCuoi)) {
            ofstream outFlight("ChuyenBay.txt", ios::app);
            outFlight.close();
            AddCustomerFromTicket(ticketId, flightId);

            break;
        }
        else if (cacSoCuoi == "Z" || cacSoCuoi == "z") {
            exit(0);
        }
        else {
            setTextColor(12); // Red
            cout << "Loi!" << endl;
            setTextColor(7); // Reset
        }
    }
}

bool IsSeatBooked(string flightId, int stt) {
    ifstream bookedFile("BookedSeat.txt");
    if (!bookedFile.is_open()) {
        cerr << "Khong the mo file BookedSeat.txt!" << endl;
        return false;
    }

    string line;
    while (getline(bookedFile, line)) {
        stringstream ss(line);
        string idFlight;
        getline(ss, idFlight, '|');

        if (idFlight == flightId) {
            string seats;
            getline(ss, seats);
            if (seats.find(to_string(stt)) != string::npos) {
                bookedFile.close();
                return false;
            }
        }
    }

    bookedFile.close();
    return true;
}


bool FindTicketInFileSolve(string idFlight, string ticketId) {
    ifstream veFile("XuLyDatVe.txt");
    if (!veFile.is_open()) {
        cerr << "Khong the mo file XuLyDatVe.txt!" << endl;
        return false;
    }

    string line;
    bool found = false;
    int stt = -1;

    while (getline(veFile, line)) {
        if (line.find("TK" + ticketId) != string::npos) {
            cout << "Tim thay ve: " << line << endl;
            found = true;

            stringstream ss(line);
            string temp;
            getline(ss, temp, '|');
            getline(ss, temp, '|');
            stt = stoi(temp);
            break;
        }
    }

    veFile.close();

    if (found && stt != -1) {
        if (!IsSeatBooked(idFlight, stt)) {
            setTextColor(14); // Yellow
            cout << "Ghe da duoc khach hang khac dat! Khong the dat ghe nay nua!" << endl;
            setTextColor(7); // Reset
            return false;
        }
        else AddSeatToFile(idFlight, stt);
    }

    return found;
}

void AddSeatToFile(string flightId, int stt) {
    ifstream bookedSeatFile("BookedSeat.txt");
    if (!bookedSeatFile.is_open()) {
        cerr << "Khong the mo file BookedSeat.txt!" << endl;
        return;
    }

    vector<string> bookedSeats;
    string line;
    bool flightFound = false;

    while (getline(bookedSeatFile, line)) {
        bookedSeats.push_back(line);
    }
    bookedSeatFile.close();

    ofstream outBookedSeat("BookedSeat.txt");
    if (!outBookedSeat.is_open()) {
        cerr << "Khong the mo file BookedSeat.txt de ghi!" << endl;
        return;
    }

    for (auto& bookedSeat : bookedSeats) {
        vector<string> flightParts;
        stringstream ss(bookedSeat);
        string token;

        while (getline(ss, token, '|')) {
            flightParts.push_back(token);
        }

        if (flightParts[0] == flightId) {
            flightFound = true;

            if (flightParts.size() > 1) {
                flightParts[1] += to_string(stt) + ";";
            }
            else {
                flightParts.push_back(to_string(stt) + ";");
            }
        }

        outBookedSeat << flightParts[0] << "|";
        if (flightParts.size() > 1) {
            outBookedSeat << flightParts[1];
        }
        outBookedSeat << endl;
    }

    if (!flightFound) {
        outBookedSeat << flightId << "|" << to_string(stt) + ";" << endl;
    }

    outBookedSeat.close();
}


void AddCustomerFromTicket(string ticketId, string flightId) {
    ifstream veFile("XuLyDatVe.txt");
    if (!veFile.is_open()) {
        cerr << "Khong the mo file XuLyDatVe.txt!" << endl;
        return;
    }

    vector<string> veList;
    vector<string> veChuaXuLy;
    string line;
    bool found = false;

    while (getline(veFile, line)) {
        veList.push_back(line);
    }
    veFile.close();

    ofstream fileKhachHang("KhachHang.txt", ios::app);
    if (!fileKhachHang.is_open()) {
        cerr << "Khong the mo file KhachHang.txt!" << endl;
        return;
    }

    string veContent;
    for (string& ve : veList) {
        vector<string> parts;
        size_t pos = 0;
        string token;
        string veLine = ve;

        while ((pos = veLine.find('|')) != string::npos) {
            token = veLine.substr(0, pos);
            parts.push_back(token);
            veLine.erase(0, pos + 1);
        }
        parts.push_back(veLine);

        string idVe = parts[0];
        if (idVe == ticketId) {
            fileKhachHang << parts[1] << "|" << parts[2] << "|" << parts[3] << endl;
            veContent = ve;
            found = true;
        }
        else {
            veChuaXuLy.push_back(ve);
        }
    }
    RemoveSolve(veChuaXuLy);
    fileKhachHang.close();

    string veFileName = ticketId + ".txt";
    ofstream newVeFile(veFileName);
    if (!newVeFile.is_open()) {
        cerr << "Khong the tao file " << veFileName << "!" << endl;
        return;
    }
    newVeFile << veContent << endl;
    newVeFile.close();

    if (!found) {
        cout << "Khong thay ma ve " << ticketId << endl;
        return;
    }
    ifstream flightFile("ChuyenBay.txt");
    if (!flightFile.is_open()) {
        cerr << "Khong the mo file ChuyenBay.txt!" << endl;
        return;
    }

    vector<string> flights;
    while (getline(flightFile, line)) {
        flights.push_back(line);
    }
    flightFile.close();

    ofstream outFlight("ChuyenBay.txt");
    if (!outFlight.is_open()) {
        cerr << "Khong the mo file ChuyenBay.txt de ghi!" << endl;
        return;
    }

    bool flightFound = false;
    for (auto& flight : flights) {
        vector<string> flightParts;
        stringstream ss(flight);
        string token;
        while (getline(ss, token, '|')) {
            flightParts.push_back(token);
        }

        if (flightParts[0] == flightId) {
            outFlight << flight;
            outFlight << ticketId << ";" << endl;
            flightFound = true;
        }
        else {
            outFlight << flight << endl;
        }
    }

    if (!flightFound) {
        cout << "Chuyen bay " << flightId << " khong tim thay trong file!" << endl;
    }

    outFlight.close();
}
void RemoveSolve(vector<string>& veChuaXuLy) {
    ofstream veFileOut("XuLyDatVe.txt");
    if (!veFileOut.is_open()) {
        cerr << "Khong the mo file XuLyDatVe.txt de ghi!" << endl;
        return;
    }

    for (string& ve : veChuaXuLy) {
        veFileOut << ve << endl;
    }

    veFileOut.close();
    setTextColor(2); // Green
    cout << "Thong tin ve da duoc luu vao KhachHang.txt va xoa khoi XuLyDatVe.txt." << endl;
}

void SolveReturnTicketConsole() {
    system("cls");
    setTextColor(2); // Yellow
    cout << "*******************************************" << endl;
    cout << "*               XU LY TRA VE              *" << endl;
    cout << "*******************************************" << endl;
    setTextColor(7); // Reset
    cout << "---------------------------------------------" << endl;

    string flightFile = "ChuyenBay.txt";
    ifstream inFile(flightFile);
    Flight chuyenBay;

    if (!inFile.is_open()) {
        cerr << "Khong the mo file ChuyenBay.txt!" << endl;
        return;
    }
    else if (EmptyFile(flightFile)) {
        setTextColor(12); // Red
        cout << "File rong! Vui long nhap them thong tin cua chuyen bay:" << endl << endl;
        setTextColor(7); // Reset
        chuyenBay.GetInfo();
        chuyenBay.SaveToFile();
        cout << endl;

        cout << "Da khoi tao du lieu cho file ChuyenBay.txt!" << endl;
        setTextColor(11); // Light Blue
        cout << "1. Quay ve man hinh chinh: " << endl;
        setTextColor(12); // Red
        cout << "2. Thoat khoi chuong trinh: " << endl;

        setTextColor(7); // Reset

        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                setTextColor(12); // Red
                cout << "Vui long nhap lai so nguyen!" << endl;
                setTextColor(7); // Reset
                continue;
            }
            switch (choice) {
            case 1: {
                system("cls");
                main();
                break;
            }
            case 2: {
                exit(0);
                break;
            }
            default: {
                setTextColor(12); // Red
                cout << "Nhap sai! Vui long nhap lai!" << endl;
                setTextColor(7); // Reset
            }
            }
        }
    }
    else {
        cout << "Hien thi cac chuyen bay hien tai:" << endl;
        setTextColor(10); // Green
        cout << "Ma chuyen bay|Ngay khoi hanh|San bay den|Trang thai|Danh sach ve" << endl;
        setTextColor(7); // Reset
        ifstream f(flightFile);
        string line;

        while (getline(f, line)) {
            line = trim(line);
            if (!line.empty()) {
                cout << line << endl;
            }
        }
        f.close();
    }

    cout << endl << "Nhap vao cac so cuoi cua ma chuyen bay:" << endl;
    while (true) {
        string cacSoCuoi;
        cin >> cacSoCuoi;
        string flightId = "FL" + cacSoCuoi;

        ifstream flightStream(flightFile);
        string line;
        bool found = false;

        while (getline(flightStream, line)) {
            if (line.find(flightId) != string::npos) {
                found = true;

                vector<string> parts;
                stringstream ss(line);
                string token;

                while (getline(ss, token, '|')) {
                    parts.push_back(token);
                }

                string id = parts[0];
                string status = parts[3];
                setTextColor(10); // Green
                cout << "Da tim thay chuyen bay: " << line << endl;
                setTextColor(7); // Reset

                if (status == "0") {
                    setTextColor(4); // Red
                    cout << "Trang thai: Huy. Vui long chon chuyen bay khac!" << endl;
                    setTextColor(14); // Yellow
                    cout << "Xin quy khach hay den quay thanh toan de lay lai tien va mang theo ve de xac minh!" << endl;
                    setTextColor(7); // Reset
                    found = false;
                }

                else if (status == "1") {
                    setTextColor(5); // Purple
                    cout << "Trang thai: Con ve. Ban co the tiep tuc." << endl;
                    setTextColor(7); // Reset
                    SolveReturnTicket(line, flightId);
                }
                else if (status == "2") {
                    setTextColor(12); // Red Dark
                    cout << "Trang thai: Het ve. Ban co the tiep tuc." << endl;
                    setTextColor(7); // Reset
                    SolveReturnTicket(line, flightId);
                }
                else if (status == "3") {
                    setTextColor(14); // Dark Yellow
                    cout << "Trang thai: Hoan tat. Vui long chon chuyen bay khac." << endl;
                    setTextColor(7); // Reset
                    found = true;

                }
                else {
                    cerr << status << endl;
                }
                cout << "----------------------------------------" << endl;
            }
        }
        flightStream.close();

        if (found) {
            break;
        }
        else {
            setTextColor(12); // Red
            cout << "Khong tim thay chuyen bay voi ma " << flightId
                << " hoac trang thai khong hop le! Thu lai? Dung thi nhap (n/N): " << endl;
            setTextColor(7); // Reset
            char choice;
            cin >> choice;
            if (choice == 'n' || choice == 'N') {
                exit(0);
            }
            else cout << "Nhap lai:" << endl;
        }
    }

    setTextColor(11); // Light Blue
    cout << "1. Quay ve man hinh chinh: " << endl;
    setTextColor(14); // Yellow
    cout << "2. Quay ve man hinh xu ly tra ve: " << endl;
    setTextColor(12); // Red
    cout << "3. Thoat khoi chuong trinh: " << endl;

    setTextColor(7); // Reset

    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            setTextColor(12); // Red
            cout << "Vui long nhap lai so nguyen!" << endl;
            setTextColor(7); // Reset
            continue;
        }
        switch (choice) {
        case 1: {
            system("cls");
            main();
            break;
        }
        case 2: {
            system("cls");
            SolveReturnTicketConsole();
            break;
        }
        case 3: {
            exit(0);
            break;
        }
        default: {
            setTextColor(12); // Red
            cout << "Nhap sai! Vui long nhap lai!" << endl;
            setTextColor(7); // Reset
        }
        }
    }
}

void SolveReturnTicket(string line, string idFlight) {
    while (true) {
        string cacSoCuoi;
        cout << endl << "Nhap vao cac so cuoi cua ma ve can xu ly tra ve:" << endl;
        cin >> cacSoCuoi;
        string ticketId = "TK" + cacSoCuoi;

        if (FindTicketInFileFlight(ticketId)) {
            ofstream outFlight("ChuyenBay.txt", ios::app);
            outFlight.close();
            RemoveTicketFromFlight(ticketId, idFlight);
            RemoveCustomer(ticketId, idFlight);
            break;
        }
        else {
            cout << "Khong tim thay ve, vui long nhap lai!" << endl;
        }
    }
}

bool FindTicketInFileFlight(string ticketId) {
    ifstream flightFile("ChuyenBay.txt");
    if (!flightFile.is_open()) {
        cerr << "Khong the mo file ChuyenBay.txt!" << endl;
        return false;
    }

    string line;
    while (getline(flightFile, line)) {
        size_t lastPipe = line.find_last_of('|');
        if (lastPipe == string::npos) {
            continue;
        }
        string ticketList = line.substr(lastPipe + 1);

        size_t pos = ticketList.find(ticketId);
        if (pos != string::npos) {
            bool isExactMatch =
                (pos == 0 || ticketList[pos - 1] == ';') &&
                (pos + ticketId.length() == ticketList.length() || ticketList[pos + ticketId.length()] == ';');
            if (isExactMatch) {
                flightFile.close();
                return true;
            }
        }
    }

    flightFile.close();
    return false;
}

void RemoveTicketFromFlight(string ticketId, string flightId) {
    ifstream flightFile("ChuyenBay.txt");
    if (!flightFile.is_open()) {
        cerr << "Khong the mo file ChuyenBay.txt!" << endl;
        return;
    }

    vector<string> flights;
    string line;

    while (getline(flightFile, line)) {
        flights.push_back(line);
    }
    flightFile.close();

    ofstream outFlight("ChuyenBay.txt");
    if (!outFlight.is_open()) {
        cerr << "Khong the mo file ChuyenBay.txt de ghi!" << endl;
        return;
    }

    bool flightFound = false;

    for (auto& flight : flights) {
        vector<string> flightParts;
        stringstream ss(flight);
        string token;

        while (getline(ss, token, '|')) {
            flightParts.push_back(token);
        }

        if (flightParts.size() < 5) {
            outFlight << flight << endl;
            continue;
        }

        if (flightParts[0] == flightId) {
            flightFound = true;

            string ticketList = flightParts[4];
            size_t pos = ticketList.find(ticketId);

            if (pos != string::npos) {
                if (pos > 0 && ticketList[pos - 1] == ';') {
                    pos--;
                }
                ticketList.erase(pos, ticketId.length() + 1);
            }
            outFlight << flightParts[0] << "|"
                << flightParts[1] << "|"
                << flightParts[2] << "|"
                << flightParts[3] << "|"
                << ticketList << endl;
        }
        else {
            outFlight << flight << endl;
        }
    }

    if (!flightFound) {
        cout << "Khong tim thay chuyen bay voi ma " << flightId << "!" << endl;
    }

    outFlight.close();

    setTextColor(2); // Green
    cout << "Ma ve " << ticketId << " da duoc xoa khoi chuyen bay " << flightId << "." << endl;
}

void RemoveCustomer(string ticketId, string flightId) {
    ifstream ticketFile(ticketId + ".txt");
    if (!ticketFile.is_open()) {
        cerr << "Khong the mo file " << ticketId << ".txt!" << endl;
        return;
    }

    string stt = "";
    string name = "";
    string cmnd = "";
    string line;
    bool ticketFound = false;

    while (getline(ticketFile, line)) {
        vector<string> ticketParts;
        stringstream ss(line);
        string token;

        while (getline(ss, token, '|')) {
            ticketParts.push_back(token);
        }
        if (ticketParts.size() >= 3 && ticketParts[0] == ticketId) {
            stt = ticketParts[1];
            cmnd = ticketParts[2];
            name = ticketParts[3];
            ticketFound = true;
            break;
        }
    }

    ticketFile.close();

    if (!ticketFound) {
        cout << "Khong tim thay khach hang voi ma " << ticketId << "!" << endl;
        return;
    }

    ifstream customerFile("KhachHang.txt");
    if (!customerFile.is_open()) {
        cerr << "Khong the mo file KhachHang.txt!" << endl;
        return;
    }

    vector<string> customers;
    bool customerRemoved = false;

    while (getline(customerFile, line)) {
        vector<string> customerParts;
        stringstream ss(line);
        string token;

        while (getline(ss, token, '|')) {
            customerParts.push_back(token);
        }

        if (customerParts[1] == cmnd && customerParts[0] == stt && customerParts[2] == name) {
            customerRemoved = true;
            cout << "Da xoa khach hang " + stt + "|" + cmnd + "|" + name << "!" << endl;
        }
        else {
            customers.push_back(line);
        }
    }

    customerFile.close();

    if (!customerRemoved) {
        cout << "Khong tim thay khach hang " + stt + "|" + cmnd + "|" + name + "!" << endl;
    }

    ofstream outCustomer("KhachHang.txt");
    if (!outCustomer.is_open()) {
        cerr << "Khong the mo file KhachHang.txt de ghi!" << endl;
        return;
    }

    for (auto& customer : customers) {
        outCustomer << customer << endl;
    }
    outCustomer.close();

    if (customerRemoved) {
        if (remove((ticketId + ".txt").c_str()) == 0) {
            setTextColor(14); // Yellow
            cout << "File cua ve " << ticketId << " da xoa thanh cong!" << endl;
            cout << "Tra ve ghe so " << stt << "!" << endl;
            DeleteSeat(flightId, stoi(stt));
            setTextColor(7); // Reset
        }
        else {
            setTextColor(12); // Red
            cerr << "Khong the xoa file " << ticketId << ".txt!" << endl;
            setTextColor(7); // Reset
        }
    }
    else {
        setTextColor(12); // Red
        cout << "Khong tim thay khach hang de xoa!" << endl;
        setTextColor(7); // Reset
    }
}
void DeleteSeat(string flightId, int stt) {
    ifstream bookedSeatFile("BookedSeat.txt");
    if (!bookedSeatFile.is_open()) {
        cerr << "Khong the mo file BookedSeat.txt!" << endl;
        return;
    }

    vector<string> updatedSeats;
    string line;
    bool flightFound = false;

    while (getline(bookedSeatFile, line)) {
        stringstream ss(line);
        string id, seats;
        getline(ss, id, '|');
        getline(ss, seats);

        if (id == flightId) {
            flightFound = true;
            stringstream seatStream(seats);
            string seat;
            string updatedSeatList;

            while (getline(seatStream, seat, ';')) {
                if (!seat.empty() && stoi(seat) != stt) {
                    updatedSeatList += seat + ";";
                }
            }
            updatedSeats.push_back(id + "|" + updatedSeatList);
        }
        else {
            updatedSeats.push_back(line);
        }
    }
    bookedSeatFile.close();
    ofstream outBookedSeat("BookedSeat.txt");
    if (!outBookedSeat.is_open()) {
        cerr << "Khong the mo file BookedSeat.txt de ghi!" << endl;
        return;
    }

    for (auto& seatLine : updatedSeats) {
        outBookedSeat << seatLine << endl;
    }

    outBookedSeat.close();

    if (!flightFound) {
        cout << "Chuyen bay " << flightId << " khong tim thay trong file BookedSeat.txt!" << endl;
    }
    else {
        cout << "Da xoa ghe " << stt << " cua chuyen bay " << flightId << "!" << endl;
    }
}

void SolveStatisticalConsole() {
    system("cls");
    setTextColor(13); // Purple
    cout << "*******************************************" << endl;
    cout << "*                 THONG KE                *" << endl;
    cout << "*******************************************" << endl;
    setTextColor(7); // Reset color
    cout << "---------------------------------------------" << endl << endl;

    int completedFlightsCount = 0;

    bool foundIdFL = false;
    string flightId;

    cout << "Hien thi cac chuyen bay hien tai:" << endl;
    setTextColor(10); // Green
    cout << "Ma chuyen bay|Ngay khoi hanh|San bay den|Trang thai|Danh sach ve" << endl;
    setTextColor(7); // Reset
    fstream f;
    setTextColor(7); // Reset
    f.open("ChuyenBay.txt");
    string line;;

    while (!f.eof()) {
        getline(f, line); cout << line << endl;
    } f.close();
    cout << endl;

    ifstream fff("ChuyenBay.txt");
    string linee;

    while (getline(fff, linee)) {
        linee = trim(linee);
        if (!linee.empty()) {

            vector<string> parts = splitLine(linee, '|');
            if (parts.size() < 5) {
                continue;
            }
            string status = parts[3];
            if (status != "0") {
                completedFlightsCount++;
            }
        }
    }
    fff.close();
    cout << endl;

    while (!foundIdFL) {
        ifstream flightFile("ChuyenBay.txt");
        if (!flightFile.is_open()) {
            cerr << "Khong the mo file ChuyenBay.txt!" << endl;
            return;
        }

        setTextColor(15); // White
        cout << "Nhap ma chuyen bay: " << endl;
        cin >> flightId;

        string line;
        while (getline(flightFile, line)) {
            vector<string> parts = splitLine(line, '|');
            if (parts.size() < 5) {
                continue;
            }

            if (parts[0] == flightId) {
                foundIdFL = true;
                string id = parts[0];
                string ngay = parts[1];
                string diemDen = parts[2];
                string trangThai = parts[3];
                string danhSachVe = parts[4];

                cout << endl;
                setTextColor(10); // Green
                cout << "Da tim thay chuyen bay: " << endl;
                setTextColor(11); // Light Blue
                cout << "Ma chuyen bay: " << id << endl;
                setTextColor(13); // Pink
                cout << "Ngay: " << ngay << endl;
                setTextColor(9); // Purple
                cout << "Diem den: " << diemDen << endl;

                setTextColor(14); // Yellow
                cout << "Trang thai: ";
                if (trangThai == "0") { cout << "Huy." << endl; }
                else if (trangThai == "1") { cout << "Con ve." << endl; }
                else if (trangThai == "2") { cout << "Het ve." << endl; }
                else if (trangThai == "3") { cout << "Hoan tat." << endl; }
                setTextColor(7); // Reset color

                vector<string> ticketFiles;
                if (danhSachVe.empty()) {
                    cout << "Khong co ve nao trong chuyen bay nay." << endl;
                }
                else {
                    vector<string> rawTicketFiles = splitLine(danhSachVe, ';');
                    for (const string& ticketId : rawTicketFiles) {
                        ticketFiles.push_back(ticketId + ".txt");
                    }
                    setTextColor(6); // Dark Yellow 
                    cout << endl << "Cac ve dat tim duoc trong chuyen bay " << id << " :" << endl;
                    setTextColor(3); // Blue
                    for (const string& file : rawTicketFiles) {
                        cout << file << " ";
                    }
                    cout << endl << endl;
                    setTextColor(7); // Reset
                    DisplayCustomerInfo(ticketFiles, flightId);

                    cout << endl;

                    if (trangThai == "1" || trangThai == "0" || trangThai == "3") {
                        DisplayEmptySeats(flightId);
                    }
                    else {
                        setTextColor(12); // Red;
                        cout << "Het ghe trong!" << endl;
                        setTextColor(7); // Reset
                    }
                }
                break;
            }
        }
        flightFile.close();

        if (!foundIdFL) {
            setTextColor(12); // Red
            cout << "Khong tim thay ma chuyen bay! Vui long nhap lai." << endl;
            setTextColor(7); // Reset color
        }
    }

    cout << endl;
    setTextColor(11); // Light Blue
    cout << "1. Quay ve man hinh chinh: " << endl;
    setTextColor(14); // Yellow
    cout << "2. Quay ve man hinh thong ke: " << endl;
    setTextColor(12); // Red
    cout << "3. Thoat khoi chuong trinh: " << endl;
    setTextColor(7); // Reset

    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            setTextColor(12); // Red
            cout << "Vui long nhap lai so nguyen!" << endl;
            setTextColor(7); // Reset
            continue;
        }
        switch (choice) {
        case 1:
            system("cls");
            main();
            break;
        case 2:
            SolveStatisticalConsole();
            break;
        case 3:
            exit(0);
            break;
        default:
            setTextColor(12); // Red
            cout << "Nhap sai! Vui long nhap lai!" << endl;
            setTextColor(7); // Reset
        }
    }
}


void DisplayCustomerInfo(vector<string>& ticketFiles, string flightId) {
    ifstream customerFile("KhachHang.txt");
    if (!customerFile.is_open()) {
        cerr << "Khong the mo file KhachHang.txt!" << endl;
        return;
    }

    vector<string> customerData;
    string line;
    while (getline(customerFile, line)) {
        customerData.push_back(line);
    }
    customerFile.close();

    setTextColor(14); // Yellow
    cout << "Thong tin khach hang tren chuyen bay " << flightId << ":" << endl << endl;
    setTextColor(9); // Avg Yellow
    cout << "STT|So CMND|Ho Ten" << endl;
    setTextColor(7); // Reset
    for (const string& ticketFile : ticketFiles) {
        ifstream ticket(ticketFile);
        if (!ticket.is_open()) {
            cerr << "Khong the mo file " << ticketFile << "!" << endl;
            continue;
        }

        string ticketLine;
        getline(ticket, ticketLine);
        ticket.close();

        vector<string> ticketParts = splitLine(ticketLine, '|');
        if (ticketParts.size() < 5) {
            cerr << "File " << ticketFile << " khong hop le!" << endl;
            continue;
        }

        string ticketId = ticketParts[0];
        string sothutu = ticketParts[1];
        string cmnd = ticketParts[2];
        string hoten = ticketParts[3];
        string ghe = ticketParts[4];

        bool foundCustomer = false;
        for (string& customerLine : customerData) {
            vector<string> customerParts = splitLine(customerLine, '|');
            if (customerParts.size() >= 3 && customerParts[1] == cmnd) {
                cout << customerParts[0] + "|" + customerParts[1] + "|" + customerParts[2] << endl;
                foundCustomer = true;
                break;
            }
        }
        if (!foundCustomer) {
            cout << "Khong tim thay khach hang voi CMND: " << cmnd << endl;
        }
    }
}

void DisplayEmptySeats(string flightId) {
    ifstream PLFL("PL_FL.txt");
    if (!PLFL.is_open()) {
        setTextColor(12); // Red
        cerr << "Khong the mo file PL_FL.txt!" << endl;
        setTextColor(7); // Reset
        return;
    }

    string line;
    int maxSeats = 0;
    while (getline(PLFL, line)) {
        stringstream ss(line);
        string planeId, currentFlightId;
        int max;
        getline(ss, planeId, '|');
        getline(ss, currentFlightId, '|');
        ss >> max;

        if (currentFlightId == flightId) {
            maxSeats = max;
            break;
        }
    }

    if (maxSeats == 0) {
        setTextColor(12); // Red
        cerr << "Khong tim thay chuyen bay voi ma " << flightId << " trong PL_FL.txt!" << endl;
        setTextColor(7); // Reset
        return;
    }

    PLFL.close();

    ifstream bookedSeatsFile("BookedSeat.txt");
    if (!bookedSeatsFile.is_open()) {
        setTextColor(12); // Red
        cerr << "Khong the mo file BookedSeat.txt!" << endl;
        setTextColor(7); // Reset
        return;
    }
    vector<int> bookedSeats;
    while (getline(bookedSeatsFile, line)) {
        stringstream ss(line);
        string currentFlight;
        getline(ss, currentFlight, '|');

        if (currentFlight == flightId) {
            string seat;
            while (getline(ss, seat, ';')) {
                if (!seat.empty()) {
                    bookedSeats.push_back(stoi(seat));
                }
            }
        }
    }

    bookedSeatsFile.close();

    setTextColor(10);  // Green
    cout << "Danh sach ghe trong cho chuyen bay " << flightId << ":\n";
    setTextColor(7);   // Reset

    for (int i = 1; i <= maxSeats; i++) {
        bool isBooked = false;
        for (int j = 0; j < bookedSeats.size(); j++) {
            if (bookedSeats[j] == i) {
                isBooked = true;
                break;
            }
        }
        if (!isBooked) {
            cout << i << " ";
        }
    }
    cout << endl;
}

# Flight Management Study

Do an Cau truc du lieu - Nhom Phan Dau: chuong trinh console quan ly chuyen bay, dat ve, tra ve va thong ke.

## Chay chuong trinh

Mo `DoAn5_NhomPhanDau_CTDL.vcxproj` bang Visual Studio 2022 roi chay (F5).
Chuong trinh doc/ghi cac file `.txt` trong thu muc goc cua project (thu muc lam viec mac dinh cua Visual Studio).

Tai khoan admin nam trong `Admin.txt` (dong 1: user, dong 2: password).

## Cau truc ma nguon

```
src/
  main.cpp              Menu chinh
  Console.h/.cpp        Mau chu, khung tieu de, nhap lua chon, menu cuoi man hinh, nhap mat khau
  Utils.h/.cpp          Tach chuoi, kiem tra ngay thang, sinh ma, chuan hoa ma
  DataFile.h/.cpp       Ten cac file du lieu va ham doc/ghi file
  LinkedList.h          Danh sach lien ket don (template)
  Plane, Customer,      Cac lop du lieu: may bay, khach hang, ve, chuyen bay
  Ticket, Flight
  Screens.h             Khai bao cac man hinh
  UserScreens.cpp       Xem danh sach chuyen bay, dat ve
  AdminScreens.cpp      Dang nhap, menu quan ly, cac buoc dung chung
  OrderProcessing.cpp   Xu ly dat ve
  ReturnProcessing.cpp  Xu ly tra ve
  Statistics.cpp        Thong ke
```

## Cau truc du lieu su dung

- `LinkedList<T>` (danh sach lien ket don): luu yeu cau dat ve vua tao va toan bo chuyen bay khi thong ke (tim chuyen bay bang `search`).
- `std::set<int>`: danh sach ghe trong / ghe da dat cua chuyen bay (tu dong sap xep, tim kiem nhanh).
- `std::vector`: danh sach ve cua chuyen bay, cac dong doc tu file.

## File du lieu

| File | Dinh dang |
|---|---|
| `ChuyenBay.txt` | `MaCB\|NgayKhoiHanh\|SanBayDen\|TrangThai\|TK1;TK2;` (trang thai 0: Huy, 1: Con ve, 2: Het ve, 3: Hoan tat) |
| `KhachHang.txt` | `STT\|CMND\|HoTen` |
| `MayBay.txt` | `MaMB\|SoChoNgoi` |
| `PL_FL.txt` | `MaMB\|MaCB\|SoChoNgoi` |
| `BookedSeat.txt` | `MaCB\|1;2;4;` |
| `XuLyDatVe.txt` | `MaVe\|STT\|CMND\|HoTen\|MaGhe` - yeu cau dat ve dang cho admin duyet |
| `TKxxxxxx.txt` | `MaVe\|STT\|CMND\|HoTen\|MaGhe` - moi ve da duyet mot file |

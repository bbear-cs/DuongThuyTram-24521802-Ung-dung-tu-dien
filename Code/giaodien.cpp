#include <windows.h>
#include <sstream>

vector<MucTu> ds;
Node root = create();

HWND txtTu, txtNghia;
HWND btnThem, btnXoa, btnTimTu, btnLamMoi;
HWND listBangGoc, txtIndex, lblTrangThai;

#define ID_TXT_TU       101
#define ID_TXT_NGHIA    102
#define ID_BTN_THEM     201
#define ID_BTN_XOA      202
#define ID_BTN_TIM_TU   203
#define ID_BTN_LAMMOI   204
#define ID_LIST_BANGGOC 301
#define ID_TXT_INDEX    302
#define ID_LBL_STATUS   401

string LayText(HWND h) {
    int len = GetWindowTextLengthA(h);
    char *buf = new char[len + 1];
    GetWindowTextA(h, buf, len + 1);
    string s = buf;
    delete[] buf;
    return s;
}

void DatText(HWND h, string s) {
    SetWindowTextA(h, s.c_str());
}

void DatTrangThai(string s) {
    SetWindowTextA(lblTrangThai, s.c_str());
}

void CapNhatBangGoc() {
    SendMessageA(listBangGoc, LB_RESETCONTENT, 0, 0);

    if(ds.size() == 0) {
        SendMessageA(listBangGoc, LB_ADDSTRING, 0, (LPARAM)"Tu dien rong.");
        return;
    }

    for(int i = 0; i < (int)ds.size(); i++) {
        string dong = ds[i].tu + " | " + ds[i].nghia;
        SendMessageA(listBangGoc, LB_ADDSTRING, 0, (LPARAM)dong.c_str());
    }
}

void CapNhatIndex() {
    string s;
    CayToString(root, s);
    SetWindowTextA(txtIndex, s.c_str());
}

void CapNhatTatCa() {
    CapNhatBangGoc();
    CapNhatIndex();
}

void XoaNhapLieu() {
    DatText(txtTu, "");
    DatText(txtNghia, "");
}

void XuLyThem() {
    string tu = LayText(txtTu);
    string nghia = LayText(txtNghia);

    if(tu == "" || nghia == "") {
        DatTrangThai("Vui long nhap day du tu va nghia");
        return;
    }

    tu = ChuanHoa(tu);

    if(find(root, tu) != -1) {
        DatTrangThai("Tu da ton tai");
        return;
    }

    MucTu mt;
    mt.tu = tu;
    mt.nghia = nghia;
    ds.push_back(mt);

    insert(root, mt.tu, (int)ds.size() - 1);

    CapNhatTatCa();
    DatTrangThai("Da them muc tu");
    XoaNhapLieu();
}

void XuLyXoa() {
    string tu = LayText(txtTu);

    if(tu == "") {
        DatTrangThai("Nhap tu de xoa");
        return;
    }

    if(xoaTu(ds, root, tu)) {
        CapNhatTatCa();
        DatTrangThai("Da xoa muc tu");
        XoaNhapLieu();
    }
    else {
        DatTrangThai("Khong tim thay tu can xoa");
    }
}

void XuLyTimTu() {
    string tu = LayText(txtTu);

    if(tu == "") {
        DatTrangThai("Nhap tu de tim.");
        return;
    }

    int pos = find(root, tu);

    if(pos == -1) {
        DatTrangThai("Khong tim thay tu.");
    }
    else {
        string s = "Tim thay: " + ds[pos].tu + " - " + ds[pos].nghia;
        DatTrangThai(s);
    }
}

void TaoControl(HWND hwnd) {
    CreateWindowA("STATIC", "UNG DUNG TU DIEN TIENG ANH",
        WS_VISIBLE | WS_CHILD, 280, 20, 320, 25, hwnd, NULL, NULL, NULL);

    CreateWindowA("STATIC", "Tu:", WS_VISIBLE | WS_CHILD,
        40, 70, 80, 20, hwnd, NULL, NULL, NULL);
    txtTu = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
        120, 68, 240, 24, hwnd, (HMENU)ID_TXT_TU, NULL, NULL);

    CreateWindowA("STATIC", "Nghia:", WS_VISIBLE | WS_CHILD,
        40, 105, 80, 20, hwnd, NULL, NULL, NULL);
    txtNghia = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
        120, 103, 360, 24, hwnd, (HMENU)ID_TXT_NGHIA, NULL, NULL);

    btnThem = CreateWindowA("BUTTON", "Them", WS_VISIBLE | WS_CHILD,
        520, 68, 100, 28, hwnd, (HMENU)ID_BTN_THEM, NULL, NULL);
    btnXoa = CreateWindowA("BUTTON", "Xoa", WS_VISIBLE | WS_CHILD,
        630, 68, 100, 28, hwnd, (HMENU)ID_BTN_XOA, NULL, NULL);
    btnTimTu = CreateWindowA("BUTTON", "Tim nghia", WS_VISIBLE | WS_CHILD,
        520, 103, 100, 28, hwnd, (HMENU)ID_BTN_TIM_TU, NULL, NULL);
    btnLamMoi = CreateWindowA("BUTTON", "Lam moi", WS_VISIBLE | WS_CHILD,
        630, 103, 100, 28, hwnd, (HMENU)ID_BTN_LAMMOI, NULL, NULL);

    CreateWindowA("STATIC", "Bang goc hien tai", WS_VISIBLE | WS_CHILD,
        40, 165, 160, 20, hwnd, NULL, NULL, NULL);
    listBangGoc = CreateWindowA("LISTBOX", "", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
        40, 190, 330, 290, hwnd, (HMENU)ID_LIST_BANGGOC, NULL, NULL);

    CreateWindowA("STATIC", "Index Trie", WS_VISIBLE | WS_CHILD,
        410, 165, 120, 20, hwnd, NULL, NULL, NULL);
    txtIndex = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER |
        ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_READONLY,
        410, 190, 360, 290, hwnd, (HMENU)ID_TXT_INDEX, NULL, NULL);

    lblTrangThai = CreateWindowA("STATIC", "San sang.",
        WS_VISIBLE | WS_CHILD, 40, 505, 730, 24, hwnd, (HMENU)ID_LBL_STATUS, NULL, NULL);

    CapNhatTatCa();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CREATE:
            TaoControl(hwnd);
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case ID_BTN_THEM:
                    XuLyThem();
                    break;
                case ID_BTN_XOA:
                    XuLyXoa();
                    break;
                case ID_BTN_TIM_TU:
                    XuLyTimTu();
                    break;
                case ID_BTN_LAMMOI:
                    CapNhatTatCa();
                    XoaNhapLieu();
                    DatTrangThai("Da lam moi hien thi.");
                    break;
            }
            break;

        case WM_DESTROY:
            xoa(root);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
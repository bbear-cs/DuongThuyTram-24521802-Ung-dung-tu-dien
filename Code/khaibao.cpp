#include<bits/stdc++.h>
using namespace std;

struct MucTu{
    string tu;
    string nghia;
};

struct node{
    bool ketthuc;
    int key;
    string nhan;
    map<string, node*> con;
};
typedef node* Node;

struct NutVe{
    string nhan;
    vector<int> con;
    int cha;
    int x, y;
};

Node create(string nhan = "") {
    Node tmp = new node;
    tmp->ketthuc = false;
    tmp->key = -1;
    tmp->nhan = nhan;
    return tmp;
}

string ChuanHoa(string s) {
    for(int i = 0; i < (int)s.size(); i++) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
    return s;
}

int TienToChung(string a, string b) {
    int n = min((int)a.size(), (int)b.size());
    int i = 0;
    while(i < n && a[i] == b[i]) i++;
    return i;
}

void xoa(Node &root) {
    if(root == NULL) return;
    for(auto &it : root->con) {
        xoa(it.second);
    }
    delete root;
    root = NULL;
}

void insert(Node root, string tu, int key) {
    tu = ChuanHoa(tu);
    Node p = root;
    string s = tu;

    while(true) {
        bool check = false;

        for(auto it = p->con.begin(); it != p->con.end(); ++it) {
            string canh = it->first;
            Node q = it->second;

            int chung = TienToChung(s, canh);
            if(chung == 0) continue;

            // Trung khop hoan toan
            if(chung == (int)s.size() && chung == (int)canh.size()) {
                q->ketthuc = true;
                q->key = key;
                return;
            }

            // Canh la tien to cua tu can chen -> di xuong duoi
            if(chung == (int)canh.size() && chung < (int)s.size()) {
                s = s.substr(chung);
                p = q;
                check = true;
                break;
            }

            // Tu can chen la tien to cua canh hien tai -> tach node
            if(chung == (int)s.size() && chung < (int)canh.size()) {
                string du = canh.substr(chung);

                Node giua = create(s);
                giua->ketthuc = true;
                giua->key = key;

                q->nhan = du;
                giua->con[du] = q;

                p->con.erase(it);
                p->con[s] = giua;
                return;
            }

            // Trung 1 phan -> tach thanh node chung
            if(chung < (int)s.size() && chung < (int)canh.size()) {
                string dau = s.substr(0, chung);
                string duTu = s.substr(chung);
                string duCanh = canh.substr(chung);

                Node giua = create(dau);

                q->nhan = duCanh;
                giua->con[duCanh] = q;

                Node moi = create(duTu);
                moi->ketthuc = true;
                moi->key = key;
                giua->con[duTu] = moi;

                p->con.erase(it);
                p->con[dau] = giua;
                return;
            }
        }

        if(check) continue;

        Node moi = create(s);
        moi->ketthuc = true;
        moi->key = key;
        p->con[s] = moi;
        return;
    }
}

int find(Node root, string tu) {
    tu = ChuanHoa(tu);
    Node p = root;
    string s = tu;

    while(true) {
        bool check = false;

        for(auto it = p->con.begin(); it != p->con.end(); ++it) {
            string canh = it->first;
            Node q = it->second;

            int chung = TienToChung(s, canh);
            if(chung == 0) continue;

            if(chung == (int)s.size() && chung == (int)canh.size()) {
                if(q->ketthuc) return q->key;
                return -1;
            }

            if(chung == (int)canh.size() && chung < (int)s.size()) {
                s = s.substr(chung);
                p = q;
                check = true;
                break;
            }

            return -1;
        }

        if(!check) return -1;
    }
}

bool xoaTu(vector<MucTu> &ds, Node &root, string tu) {
    tu = ChuanHoa(tu);
    int vt = -1;

    for(int i = 0; i < (int)ds.size(); i++) {
        if(ChuanHoa(ds[i].tu) == tu) {
            vt = i;
            break;
        }
    }

    if(vt == -1) return false;

    ds.erase(ds.begin() + vt);
    xoa(root);
    root = create();

    for(int i = 0; i < (int)ds.size(); i++) {
        insert(root, ds[i].tu, i);
    }
    return true;
}

string InHoa(string s) {
    for(int i = 0; i < (int)s.size(); i++) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
    return s;
}

string LayNhan(Node p, string pref) {
    if(pref == "") return "RONG";
    return InHoa(p->nhan);
}

void TaoDanhSachNut(Node root, vector<NutVe> &dsNut, string pref = "", int cha = -1, int depth = 0) {
    int id = (int)dsNut.size();

    NutVe t;
    t.nhan = LayNhan(root, pref);
    t.cha = cha;
    t.x = 0;
    t.y = depth * 2;
    dsNut.push_back(t);

    if(cha != -1) dsNut[cha].con.push_back(id);

    for(auto it = root->con.begin(); it != root->con.end(); it++) {
        TaoDanhSachNut(it->second, dsNut, pref + it->first, id, depth + 1);
    }
}

int GanViTriX(int u, vector<NutVe> &dsNut, int &la) {
    if(dsNut[u].con.empty()) {
        dsNut[u].x = la;
        la += 12;
        return dsNut[u].x;
    }

    vector<int> pos;
    for(int v : dsNut[u].con) {
        pos.push_back(GanViTriX(v, dsNut, la));
    }

    dsNut[u].x = (pos.front() + pos.back()) / 2;
    return dsNut[u].x;
}

int TamNode(NutVe t) {
    return t.x;
}

void VeChuoi(vector<string> &bang, int dong, int cot, string s) {
    if(dong < 0 || dong >= (int)bang.size()) return;
    if(cot < 0) return;

    for(int i = 0; i < (int)s.size(); i++) {
        if(cot + i >= 0 && cot + i < (int)bang[dong].size()) {
            bang[dong][cot + i] = s[i];
        }
    }
}

void CayToString(Node root, string &out) {
    if(root == NULL) {
        out = "Cay rong.\r\n";
        return;
    }

    vector<NutVe> dsNut;
    TaoDanhSachNut(root, dsNut);

    int la = 10;
    GanViTriX(0, dsNut, la);

    int maxX = 0, maxY = 0;
    for(int i = 0; i < (int)dsNut.size(); i++) {
        maxX = max(maxX, dsNut[i].x + 8);
        maxY = max(maxY, dsNut[i].y);
    }

    vector<string> bang(maxY + 3, string(maxX + 30, ' '));

    for(int i = 0; i < (int)dsNut.size(); i++) {
        int cot = dsNut[i].x - (int)dsNut[i].nhan.size() / 2;
        VeChuoi(bang, dsNut[i].y, cot, dsNut[i].nhan);

        for(int v : dsNut[i].con) {
            int x1 = TamNode(dsNut[i]);
            int x2 = TamNode(dsNut[v]);
            int y = dsNut[i].y + 1;

            if(y >= 0 && y < (int)bang.size()) {
                if(x2 < x1) {
                    bang[y][x1 - 4] = '/';
                }
                else if(x2 > x1) {
                    bang[y][x1 + 4] = '\\';
                }
                else {
                    bang[y][x1] = '|';
                }
            }
        }
    }

    out.clear();
    for(int i = 0; i < (int)bang.size(); i++) {
        int cuoi = (int)bang[i].size() - 1;
        while(cuoi >= 0 && bang[i][cuoi] == ' ') cuoi--;
        if(cuoi < 0) out += "\r\n";
        else out += bang[i].substr(0, cuoi + 1) + "\r\n";
    }
}
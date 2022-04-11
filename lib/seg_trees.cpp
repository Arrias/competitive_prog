//
// Created by arrias on 04.06.2021.
//

template<int SZ>
struct DO {
    ll t[4 * SZ];

    DO() {
        fill(t, t + 4 * SZ, LINF);
    }

    void setVal(int i, int tl, int tr, int pos, ll key) {
        if (tl + 1 == tr) {
            ckmin(t[i], key);
            if (key == LINF) t[i] = key;
            return;
        }
        int md = (tl + tr) / 2;
        if (pos < md) setVal(i * 2, tl, md, pos, key);
        else setVal(i * 2 + 1, md, tr, pos, key);
        t[i] = min(t[i * 2], t[i * 2 + 1]);
    }

    void setVal(int pos, ll key) {
        setVal(1, 0, SZ, pos, key);
    }

    ll get(int i, int tl, int tr, int l, int r) {
        if (l <= tl && tr <= r)
            return t[i];
        if (tl >= r || l >= tr)
            return LINF;
        int md = (tl + tr) / 2;
        return min(get(i * 2, tl, md, l, r), get(i * 2 + 1, md, tr, l, r));
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r + 1);
    }
};







const int N = 1e5 + 40;
const ll LINF = 1e18;
// ДО, в котором можно min на отрезке и присваивание в точку
ll t1[4 * N];
ll p1[4 * N];

void push(int i, int tl, int tr) {
    ckmin(t1[i], p1[i]);
    if (tl + 1 != tr) {
        ckmin(p1[i * 2], p1[i]);
        ckmin(p1[i * 2 + 1], p1[i]);
    }
    p1[i] = LINF;
}

void min_on_seg(int i, int tl, int tr, int l, int r, ll k) {
    push(i, tl, tr);
    if (l <= tl && tr <= r) {
        ckmin(p1[i], k);
        push(i, tl, tr);
        return;
    }
    if (tl >= r || l >= tr) return;
    int md = (tl + tr) / 2;
    min_on_seg(i * 2, tl, md, l, r, k);
    min_on_seg(i * 2 + 1, md, tr, l, r, k);
    t1[i] = min(t1[i * 2], t1[i * 2 + 1]);
}

void upd_at_point(int i, int tl, int tr, int pos, ll k) {
    push(i, tl, tr);
    if (tl + 1 == tr) {
        p1[i] = LINF;
        t1[i] = k;
        return;
    }
    int md = (tl + tr) / 2;
    if (pos < md)
        upd_at_point(i * 2, tl, md, pos, k);
    else
        upd_at_point(i * 2 + 1, md, tr, pos, k);
    t1[i] = min(t1[i * 2], t1[i * 2 + 1]);
}

// ДО, в котором можно присвоить в точку и взять максимум
pair<ll, ll> t2[4 * N];

void upd2_at_point(int i, int tl, int tr, int pos, ll k) {
    if (tl + 1 == tr) {
        t2[i].first = k;
        t2[i].second = tl;
        return;
    }
    int md = (tl + tr) / 2;
    if (pos < md)
        upd2_at_point(i * 2, tl, md, pos, k);
    else
        upd2_at_point(i * 2 + 1, md, tr, pos, k);
    t2[i] = min(t2[i * 2], t2[i * 2 + 1]);
}

pair<ll, ll> getMax(int i, int tl, int tr, int l, int r) {
    if (l <= tl && tr <= r)
        return t2[i];
    if (l >= tr || tl >= r) {
        return {-LINF, LINF};
    }
    int md = (tl + tr) / 2;
    return max(getMax(i * 2, tl, md, l, r), getMax(i * 2 + 1, md, tr, l, r));
}

struct Edge {
    int l, r;
    ll cost;
};

int n, q, s;
vector<Edge> g[N];
map<int, vector<Edge>>

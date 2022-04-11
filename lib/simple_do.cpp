//
// Created by arrias on 26.12.2020.
//

template<typename T, class F = function < T(T, T)>>

struct DO { // change at point
    vector <T> mas;
    vi pos;
    F upd, chg;
    T inf;
    int siz;

    DO(const int &n, const T &neu, const F &u, const F &c) : siz(n), upd(u), chg(c), inf(neu) {
        mas.assign(n * 4 + 5, neu);
        pos.resize(n * 4 + 5);
    }

    void modify(int i, int tl, int tr, int id, T value) {
        if (tl + 1 == tr) {
            mas[i] = chg(mas[i], value);
            pos[i] = tl;
            return;
        }
        int mid = (tl + tr) / 2;
        if (id < mid) {
            modify(i * 2, tl, mid, id, value);
        } else {
            modify(i * 2 + 1, mid, tr, id, value);
        }
        mas[i] = upd(mas[i * 2], mas[i * 2 + 1]);
        if (mas[i] == mas[i * 2 + 1]) {
            pos[i] = pos[i * 2 + 1];
        }
    }

    void setValue(int point, T value) {
        modify(1, 0, siz, point, value);
    }

    T getValue(int i, int tl, int tr, int l, int r) {
        if (l <= tl && tr <= r) {
            return mas[i];
        }
        if (tl >= r || l >= tr) {
            return inf;
        }
        int mid = (tl + tr) / 2;
        return upd(getValue(i * 2, tl, mid, l, r), getValue(i * 2 + 1, mid, tr, l, r));
    }

    T get(int l, int r) {
        return getValue(1, 0, siz, l, r + 1);
    }

    pair<T, int> getValueWithIndex(int i, int tl, int tr, int l, int r) {
        if (l <= tl && tr <= r) {
            return {mas[i], pos[i]};
        }
        if (tl >= r || l >= tr)
            return {inf, inf};
        int mid = (tl + tr) / 2;
        auto le = getValueWithIndex(i * 2, tl, mid, l, r);
        auto re = getValueWithIndex(i * 2 + 1, mid, tr, l, r);
        if (upd(le.first, re.first) == le.first)
            return le;
        return re;
    }

    pair<T, int> getValueWithIndex(int l, int r) {
        return getValueWithIndex(1, 0, siz, l, r + 1);
    }
};

// sample
DO<int> phi(N, N, [ ](int a, int b) { return min(a, b); }, [ ](int a, int b) { return b; });
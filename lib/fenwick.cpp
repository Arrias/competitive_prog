//
// Created by arrias on 22.06.2021.
//

template<int N>
struct Fenwick_tree {
    int t[N];
    int n;

    void init(int nn) {
        n = nn;
        fill(t, t + n + 1, 0);
    }

    int sum(int r) {
        int result = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            result += t[r];
        return result;
    }

    void inc(int i, int delta) {
        for (; i < n; i = (i | (i + 1)))
            t[i] += delta;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
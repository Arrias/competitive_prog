//
// Created by arrias on 26.12.2020.
//


template<typename T, class F = function<T(const T &, const T &)>>
class SparseTable {
public:
    int n, l;
    vector<vector<T>> mat;
    vector<int> logs;
    F func;

    SparseTable(const vector<T> &a, const F &f) : func(f) {
        n = a.size();
        l = 19; // max_log
        logs.resize(n + 2);
        for (int i = 2; i < n + 2; ++i)
            logs[i] = logs[i / 2] + 1;
        mat.assign(l, vector<int>(n, 0));
        mat[0] = a;
        for (int i = 1; i < l; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j + (1 << (i - 1)) >= n) break;
                mat[i][j] = func(mat[i - 1][j], mat[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T getVal(int l, int r) {
        int c = logs[r - l + 1];
        ++r;
        return func(mat[c][l], mat[c][r - (1 << c)]);
    }
};

template<typename T, class F = function<T(const T &, const T &)>>
class SparseTable {
public:
    int n, l;
    vector<vector<T>> mat;
    vector<T> data;
    vector<int> logs;
    F func;

    SparseTable(const vector<T> &a, const F &f) : func(f), data(a) {
        n = a.size();
        l = 25; // max_log
        logs.resize(n + 2);
        for (int i = 2; i < n + 2; ++i)
            logs[i] = logs[i / 2] + 1;
        mat.assign(l, vector<int>(n, 0));
        iota(mat[0].begin(), mat[0].end(), 0);
        for (int i = 1; i < l; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j + (1 << (i - 1)) >= n) break;
                T c = func(a[mat[i - 1][j]], a[mat[i - 1][j + (1 << (i - 1))]]);
                mat[i][j] = ((c == a[mat[i - 1][j]]) ? mat[i - 1][j] : mat[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int getId(int l, int r) {
        int c = logs[r - l + 1];
        r++;
        T val = func(data[mat[c][l]], data[mat[c][r - (1 << c)]]);
        return ((val == data[mat[c][l]]) ? mat[c][l] : mat[c][r - (1 << c)]);
    }

    T getVal(int l, int r) {
        return data[getId(l, r)];
    }
};
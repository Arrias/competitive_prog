//
// Created by arrias on 26.12.2020.
//

class matrix {
private:
    vector<vector<int>> data;
public:
    int n{}, m{};

    matrix() = default;

    matrix(int nn, int mm) {
        n = nn;
        m = mm;
        data.assign(n, vector<int>(m, 0));
    }

    void init(int nn, int mm) {
        n = nn;
        m = mm;
        data.assign(n, vector<int>(m, 0));
    }

    int &operator()(int i, int j) {
        return data[i][j];
    }

    const int &operator()(int i, int j) const {
        return data[i][j];
    }

    void print() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << data[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int add(int a, int b) {
    return (a + b);
}

int mul(int a, int b) {
    return a * b;
}

matrix operator*(matrix a, matrix b) {
    matrix c(a.n, b.m);
    for (int i = 0; i < a.n; ++i) {
        for (int j = 0; j < b.m; ++j) {
            for (int k = 0; k < b.n; ++k) {
                c(i, j) = add(c(i, j), mul(a(i, k), b(k, j)));
            }
        }
    }
    return c;
}

matrix get_null(int n, int m) {
    matrix c(n, m);
    for (int i = 0; i < n; ++i)
        c(i, i) = 1;
    return c;
}

matrix pow(matrix a, int k) {
    if (k == 0) {
        return get_null(a.n, a.m);
    }
    auto half = pow(a, k / 2);
    half = half * half;
    if (k % 2) half = half * a;
    return half;
}
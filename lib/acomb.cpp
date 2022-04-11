template<int mod = (int) 1e9 + 7>
        struct Mint {
    int value;

    Mint(int value = 0) : value(value) {}

    Mint operator+(Mint b) {
        Mint ret(*this);
        ret.value += b.value;
        if (ret.value >= mod) ret.value -= mod;
        return ret;
    }

    Mint operator-(Mint b) {
        Mint ret(*this);
        ret.value -= b.value;
        if (ret.value < 0) ret.value += mod;
        return ret;
    }

    Mint operator*(Mint b) {
        Mint ret(*this);
        ret.value = (1ll * ret.value * b.value) % mod;
        return ret;
    }

    Mint operator^(int k) {
        if (k == 0) return 1;
        auto ret = *this ^ (k / 2);
        ret *= ret;
        if (k & 1) ret *= *this;
        return ret;
    }

    Mint operator/(Mint b) {
        auto ret(*this);
        ret = ret * (b ^ (mod - 2));
        return ret;
    }

    void operator+=(Mint b) { *this = *this + b; }

    void operator-=(Mint b) { *this = *this - b; }

    void operator*=(Mint b) { *this = *this * b; }

    void operator/=(Mint b) { *this = *this / b; }
};

template<int T>
ostream &operator<<(ostream &out, const Mint<T> &v) {
    out << v.value;
    return out;
}

template<int T>
istream &operator>>(istream &in, Mint<T> &v) {
    in >> v.value;
    return in;
}

template<int mod = (int) 1e9 + 7>
        struct Combinator {
    void extgcd(ll a, ll b, ll &x0, ll &y0) {
        if (b == 0) {
            x0 = 1, y0 = 0;
            return;
        }
        ll xs, ys;
        extgcd(b, a % b, xs, ys);
        x0 = ys;
        y0 = xs - ys * (a / b);
    }

    vector<Mint<mod>> degrees(Mint<mod> k, int sz) {
        vector<Mint<mod>> ret(sz);
        ret[0] = 1;
        for (int i = 1; i < sz; ++i) {
            ret[i] = (ret[i - 1] * k);
        }
        return ret;
    }

    Mint<mod> fact(int n) {
        static vector<Mint<mod>> vec(1, Mint(1));
        while (n >= (int) vec.size()) {
            vec.push_back(vec.back() * Mint(vec.size()));
        }
        return vec[n];
    }

    Mint<mod> inv_fact(int n) {
        static vector<Mint<mod>> vec(1, Mint(1));
        while (n >= (int) vec.size()) {
            vec.push_back(vec.back() / Mint(vec.size()));
        }
        return vec[n];
    }

    Mint<mod> binom(int n, int r) {
        if (n < r) return 0;
        return fact(n) * inv_fact(n - r) * inv_fact(r);
    }

    Mint<mod> on_terms(int n, int r) {
        return binom(n + r - 1, r - 1);
    }
};

int mod;

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

ostream &operator<<(ostream &out, const Mint &v) {
    out << v.value;
    return out;
}

istream &operator>>(istream &in, Mint &v) {
    in >> v.value;
    return in;
}

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

    vector<Mint> degrees(Mint k, int sz) {
        vector<Mint> ret(sz);
        ret[0] = 1;
        for (int i = 1; i < sz; ++i) {
            ret[i] = (ret[i - 1] * k);
        }
        return ret;
    }

    Mint fact(int n) {
        static vector<Mint> vec(1, Mint(1));
        while (n >= (int) vec.size()) {
            vec.push_back(vec.back() * Mint(vec.size()));
        }
        return vec[n];
    }

    Mint inv_fact(int n) {
        static vector<Mint> vec(1, Mint(1));
        while (n >= (int) vec.size()) {
            vec.push_back(vec.back() / Mint(vec.size()));
        }
        return vec[n];
    }

    Mint binom(int n, int r) {
        if (n < r) return 0;
        return fact(n) * inv_fact(n - r) * inv_fact(r);
    }

    Mint on_terms(int n, int r) {
        return binom(n + r - 1, r - 1);
    }
};
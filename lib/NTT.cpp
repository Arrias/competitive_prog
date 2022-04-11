int mod = 998244353;

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

template<int BIT, int rt>
struct CNTT {
    // BIT = log_2(ord(rt))
    Mint root = Mint(rt);
    int sz = 1 << BIT;
    Mint deg[1 << BIT];
    int ord[1 << BIT];

    int nxt_ord(int a, int bt) {
        int i = bt - 1;
        while ((a>>i)&1) a ^= (1 << (i--));
        a ^= (1 << i);
        return a;
    }

    void init() {
        deg[0] = 1;
        for (int i = 1; i < sz; ++i) {
            deg[i] = (deg[i-1] * root);
        }
    }    

    void NTT(vector<Mint> &a, int dg, bool isRev = false) {
        // a.size() = (1 << dg)
        forn(i, a.size()) {
            if (ord[i] < i) {
                swap(a[i], a[ord[i]]);
            }
        }

        auto get_id = [&] (int id) {
            if (isRev) return id ? sz - id : 0;
            return id;
        };

        for (int lvl = 0, id0 = (1 << (BIT - 1)); lvl < dg; ++lvl, id0 /= 2) {
            int step = (1 << lvl);

            for (int i = 0; i < a.size(); i += (2 * step)) {
                for (int j = 0; j < step; ++j) {
                    auto A = a[i + j];
                    auto B = a[i + j + step];
                    a[i + j] = A + deg[get_id(id0 * j)] * B;
                    a[i + j + step] = A + deg[get_id(id0 * (j + step))] * B;
                }
            }
        }

        if (isRev) {
            auto rv = Mint(1) / Mint(1 << dg);
            for (auto &i : a) i *= rv;
        }
    }

    void mult(vector<Mint> &a, vector<Mint> &b) {
        int v = a.size() + b.size() - 1;
        int l = 0;
        while ((1 << l) < v) ++l;
        while (a.size() < (1 << l)) a.push_back(0);
        while (b.size() < (1 << l)) b.push_back(0);

        for (int i = 1; i < (1 << l); ++i) {
            ord[i] = (i & 1) * (1 << (l - 1)) + (ord[i>>1] >> 1);
        }

        NTT(a, l);
        NTT(b, l);
        forn(i, a.size()) {
            a[i] *= b[i];
        }

        NTT(a, l, true);
    }
};

CNTT<23, 15311432> ntt;


 for (int i=1, j=0; i<a.size(); ++i) {
            int bit = a.size() >> 1;
                for (; j>=bit; bit>>=1)
                    j -= bit;
            j += bit;
        if (i < j)
            swap (a[i], a[j]);
}
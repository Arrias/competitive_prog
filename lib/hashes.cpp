//
// Created by arrias on 18.06.2021.
//

auto cmp = [&](int l1, int r1, int l2, int r2) -> int {
    int len = min(r2 - l2 + 1, r1 - l1 + 1);
    int l = -1, r = len;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (h.get_seg(l1, l1 + mid) == h.get_seg(l2, l2 + mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (l == len - 1) {
        if (r1 - l1 == r2 - l2) return 0;
        if (r1 - l1 < r2 - l2) return -1;
        return 1;
    }
    if (s[l1 + l + 1] > s[l2 + l + 1]) return 1;
    return -1;
};

namespace hashes {
    const int N = 5e5 + 20;
    ll mod = 1e9 + 7;
    ll base = 239017;
    ll st[N];

    ll mul(ll a, ll b) {
        return (a * b) % mod;
    }

    ll add(ll a, ll b) {
        return (a + b + mod) % mod;
    }

    void prec() {
        st[0] = 1;
        for (int i = 1; i < N; ++i)
            st[i] = mul(st[i - 1], base);
    }

    template<class T>
    struct Hash {
        vector <ll> imp;

        Hash(T s) {
            imp.resize(s.size());
            imp[0] = s[0];
            for (int i = 1; i < imp.size(); ++i) {
                imp[i] = add(mul(imp[i - 1], base), s[i]);
            }
        }

        ll value() {
            assert(imp.size());
            return imp.back();
        }

        ll get_pref(int num) {
            if (num < 0)
                return 0;
            return imp[num];
        }

        ll get_seg(int l, int r) {
            return add(get_pref(r), -mul(get_pref(l - 1), st[r - l + 1]));
        }
    };
};

ll slay(ll le, ll re, int sz) {
    return add(mul(le, pw[sz]), re);
}

const ll base = 239017;
const ll N = 2e6;

ll mod[2] = {2971215073, 1000000007};

ll pw[N][2];

ll mul(ll a, ll b, int f) {
    return (a * b) % mod[f];
}

ll add(ll a, ll b, int f) {
    ll res = a + b;
    if (res < 0)
        res += mod[f];
    return res % mod[f];
}

void prec() {
    pw[0][0] = pw[0][1] = 1;
    for (int i = 1; i < N; ++i) {
        pw[i][0] = mul(pw[i - 1][0], base, 0);
        pw[i][1] = mul(pw[i - 1][1], base, 1);
    }
}

struct Hash {
    vector <pair<ll, ll>> imp;

    Hash() {

    }

    pair <ll, ll> value() {
        assert(imp.size());
        return imp.back();
    }

    Hash(string s) {
        imp.resize(s.size());
        imp[0].first = imp[0].second = s[0];
        for (int i = 1; i < imp.size(); ++i) {
            imp[i].first = add(mul(imp[i - 1].first, base, 0), s[i], 0);
            imp[i].second = add(mul(imp[i - 1].second, base, 1), s[i], 1);
        }
    }

    void init(string s) {
        imp.resize(s.size());
        imp[0].first = imp[0].second = s[0];
        for (int i = 1; i < imp.size(); ++i) {
            imp[i].first = add(mul(imp[i - 1].first, base, 0), s[i], 0);
            imp[i].second = add(mul(imp[i - 1].second, base, 1), s[i], 1);
        }
    }

    pair <ll, ll> get_pref(int num) {
        if (num < 0)
            return make_pair(0, 0);
        return imp[num];
    }

    pair <ll, ll> get_seg(int l, int r) {
        return make_pair(add(get_pref(r).first, -mul(get_pref(l - 1).first, pw[r - l + 1][0], 0), 0),
                         add(get_pref(r).second, -mul(get_pref(l - 1).second, pw[r - l + 1][1], 1), 1));
    }
};
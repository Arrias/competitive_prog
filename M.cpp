#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>
#include <complex>
#include <queue>
#include <cassert>
#include <stack>
#include <random>
#include <chrono>
#include <map>
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) begin(a), end(a)
#define int long long
#define sqr(x) ((x) * (x))

#ifndef _debug
    #define debug(...) 42
    #define debr(...) 42
#else
    #define debug(x) cout << #x << " = " << x << endl
    #define debr(...) { cout << #__VA_ARGS__ << " = ";  _debr(__VA_ARGS__); }
#endif

using namespace std;

template<class Iter> 
void _debr(Iter l, Iter r) {
    cout << "[";
    for (auto it = l; it != r; ++it) {
        if (it != l) {
            cout << ", ";   
        }
        cout << *it;
    }
    cout << "]" << endl;
}

template<class C, class F> 
ostream& operator<<(ostream &out, pair<C, F> p) {
    return out << "(" << p.first << ", " << p.second << ")";
}

using ll = long long;

mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 40;
const int BUBEN = 2;
const int INF = 1e18;

int n, m;

struct Block {
    vector<pair<int, int>> values;

    int pref_len = 0;
    int suff_len = 0;
    int max_len = 0;

    void build() {
        pref_len = suff_len = max_len = 0;

        int prv = values[0].first;
        int id = 0;
        while (id < values.size() && values[id].first == prv && values[id].second) {
            ++pref_len;
            ++prv;
            ++id;
        }        

        id = (int) values.size() - 1;
        prv = values.back().first;
        while (id >= 0 && values[id].first == prv && values[id].second) {
            ++suff_len;
            --prv;
            --id;
        }

        prv = values[0].first;
        int s = 0;

        for (auto &[x, cnt] : values) {
            if (x == prv && cnt) {
                ++s;
            } else if (cnt) {
                prv = x;
                s = 1;
            } else {
                prv = x;
                s = 0;
            }
            max_len = max(max_len, s);
        }
    }

    void info() {
        debug(pref_len);
        debug(max_len);
        debug(suff_len);
        cout << "\n";
        print(all(values));
    }
};

void solve() {
    cin >> n >> m;

    vector<int> a(n);
    vector<pair<int, int>> changes;
    map<int, int> cnt;

    forn(i, n) {
        cin >> a[i];
        int need = m - a[i] % m;
        if (need < m) {
            changes.push_back({need, a[i] / m + 1});
        }
        cnt[a[i] / m]++;
        cnt[a[i] / m + 1];
    }

    vector<Block> blocks;
    blocks.push_back({});

    for (auto &[x, y] : cnt) {
        if (blocks.back().values.size() == BUBEN) {
            blocks.push_back({});
        }
        blocks.back().values.push_back({x, y});
    }

    map<int, pair<int, int>> pos;
    for (int i = 0; i <blocks.size(); ++i) {
        for (int j = 0; j <blocks[i].values.size(); ++j) {
            pos[blocks[i].values[j].first] = {i, j};
        }
    }

    for (auto &block : blocks) {
        block.build();
       // block.info();
    }

    auto get_ans = [&] () {
        int res = 0;
        res = max(res, blocks[0].max_len);
        int cur_value = blocks[0].values.back().first;
        int cur_len = blocks[0].suff_len;

        for (int i = 1; i < blocks.size(); ++i) {
            res = max(res, blocks[i].max_len);

            if (blocks[i].values[0].first == cur_value + 1) {
                cur_len += blocks[i].pref_len;
                res = max(res, cur_len);
            }

            cur_value = blocks[i].values.back().first;
            if (blocks[i].suff_len == blocks[i].values.size() && blocks[i].values[0].first == cur_value + 1) {
                cur_len += blocks[i].values.size();
            } else {
                cur_len = blocks[i].suff_len;
            }
        }
        return res;
    };

    sort(all(changes));

    int res = -INF;
    int shift = -1;
    int ptr = 0;

    forn(i, m) {
        int cur = get_ans();

        if (cur > res) {
            res = cur;
            shift = i;
        }

        while (ptr < changes.size() && changes[ptr].first == i + 1) {
            auto pos1 = pos[changes[ptr].second];
            auto pos2 = pos[changes[ptr].second + 1];

            blocks[pos1.first].values[pos1.second].second--;
            blocks[pos2.first].values[pos2.second].second++;

            blocks[pos1.first].build();
            if (pos2.first != pos1.first) {
                blocks[pos2.first].build();
            }

            ++ptr;
        }
    }

    cout << res << " " << shift << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); 

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
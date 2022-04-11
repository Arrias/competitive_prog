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

struct point {
    int x, y;
    void scan() {
        cin >> x >> y;
    }
};

point operator-(point a, point b) {
    return point{a.x-b.x,a.y-b.y};
}

int operator*(point a, point b) {
    return a.x * b.y - b.x * a.y;
}

const int MAXN = 2e5 + 100;
const int MAXL = 1e6 + 100;
pair<int, int> p[MAXN][26];
int h[MAXL];

bool check(vector<int> a) {
    if(a.size() <= 1) return 1;
    for(int i = 0; i < 26; i++) {
        bool bad = 0;
        for(auto &j : a)
            if(!p[j][i].first)
                bad = 1;
        if(!bad) {
            bool res = 1;
            unordered_map<int, vector<int>> hashes;
            for(auto &j : a)
                hashes[p[j][i].second].push_back(j);
            if(hashes.size() == 1) continue;
            for(auto &j : hashes)
                if(!check(j.second))
                    res = 0;
            return res;
        }
    }
    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int l, n;
    cin >> l >> n;
    vector<string> s(n);
    for(auto &i : s)
        cin >> i;

    for(int i = 0; i < l; i++)
        h[i] = rnd();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < s[i].size(); j++) {
            p[i][s[i][j] - 'a'].first = 1;
            p[i][s[i][j] - 'a'].second ^= h[j];
        }
    }

    vector<int> inds(n);
    for(int i = 0; i < n; i++)
        inds[i] = i;
    cout << ((check(inds)) ? "YES" : "NO");
    return 0;
}
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
//#define all(a) begin(a), end(a)
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

using ll = long long;
using ld = long double;

struct lol {
    int t, x, y;
};

ld dist(ll x1, ll y1, ll x2, ll y2) {
    return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

void solve() {
    int sx, sy, fx, fy;
    cin >> sx >> sy >> fx >> fy;
    int n, k, v;
    cin >> n >> k >> v;
    vector <lol> all;
    ll xR = sx, yR = sy;
    forn (i, n) {
        ll t, x, y;
        cin >> t >> x >> y;
        all.push_back({t, x, y});
    }
    ll temp = 0;
    forn (i, k) {
        if (temp < n && all[temp + 1].t == i)
            temp++;
        //debug(temp);
        xR += all[temp].x; yR += all[temp].y;
    }
    ld kek = dist(xR, yR, fx, fy);
    if (kek > v * k) {
        cout << "No\n";
        return;
    }
    //debug(xR); debug(yR);
    ld kx = (ld)(fx - xR) / (ld)k, ky = (ld)(fy - yR) / (ld)k;
    cout << "Yes\n";
    ld cx = sx, cy = sy;
    cout << fixed;
    cout << setprecision(7);
    temp = 0;
    //debug(cx); debug(cy);
    forn (i, k) {
        if (temp < n && all[temp + 1].t == i)
            temp++;
        cx += all[temp].x; cy += all[temp].y;
        if (i == k - 1) {
            cout << fx << " " << fy << '\n';
        } else {
            cx += kx, cy += ky;
            cout << cx << " " << cy << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);   

    // freopen("joy.in", "r", stdin);
    // freopen("joy.out", "w", stdout);  

    solve();
    return 0;
}
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
//#define int long long
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
typedef long double ld;

mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

void solve() {  
        
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector <ld> t(4);

    forn (i, 4)
        cin >> t[i];

    vector <ll> a(4);
    a[0] = 0; a[1] = 1; a[2] = 2; a[3] = 3;
    vector <ll> pans;
    vector <ld> ans;
    ld ma = 0.0;
    do {
        ld l = 1.0, r = (ld)t[a[0]];
        while (r - l > 1e-7) {
            ld m = (l + r) / 2.0;
            ld fi = m * (ld)t[a[3]] + (ld)t[a[2]] + (ld)t[a[1]];
            ld se = m + (ld)t[a[3]] + (ld)t[a[2]] * (ld)t[a[1]];
            if (fi > se)
                r = m;
            else l = m;
        }
        ld fi = l * (ld)t[a[3]] + (ld)t[a[2]] + (ld)t[a[1]];
        ld se = l + (ld)t[a[3]] + (ld)t[a[2]] * (ld)t[a[1]];
        if (abs(fi - se) < 1e-6 && fi > ma) {
            ma = fi;
            pans = a;
            ans = t;
            ans[0] = l;
        }
        l = 1.0, r = (ld)t[a[1]];
        while (r - l > 1e-7) {
            ld m = (l + r) / 2.0;
            ld fi = (ld)t[a[0]] * (ld)t[a[3]] + (ld)t[a[2]] + m;
            ld se = (ld)t[a[0]] + (ld)t[a[3]] + (ld)t[a[2]] * m;
            if (fi < se)
                r = m;
            else l = m;
        }
        fi = (ld)t[a[0]] * (ld)t[a[3]] + (ld)t[a[2]] + l;
        se = (ld)t[a[0]] + (ld)t[a[3]] + (ld)t[a[2]] * l;
        if (abs(fi - se) < 1e-6 && fi > ma) {
            ma = fi;
            pans = a;
            ans = t;
            ans[1] = l;
        }

        l = 1.0, r = (ld)t[a[2]];
        while (r - l > 1e-7) {
            ld m = (l + r) / 2.0;
            ld fi = (ld)t[a[0]] * (ld)t[a[3]] + m + (ld)t[a[1]];
            ld se = (ld)t[a[0]] + (ld)t[a[3]] + m * (ld)t[a[1]];
            if (fi < se)
                r = m;
            else l = m;
        }
        fi = (ld)t[a[0]] * (ld)t[a[3]] + l + (ld)t[a[1]];
        se = (ld)t[a[0]] + (ld)t[a[3]] + l * (ld)t[a[1]];
        if (abs(fi - se) < 1e-6 && fi > ma) {
            ma = fi;
            pans = a;
            ans = t;
            ans[2] = l;
        }

        l = 1.0, r = (ld)t[a[3]];
        while (r - l > 1e-7) {
            ld m = (l + r) / 2.0;
            ld fi = (ld)t[a[0]] * m + (ld)t[a[2]] + (ld)t[a[1]];
            ld se = (ld)t[a[0]] + m + (ld)t[a[2]] * (ld)t[a[1]];
            if (fi > se)
                r = m;
            else l = m;
        }
        fi = (ld)t[a[0]] * l + (ld)t[a[2]] + (ld)t[a[1]];
        se = (ld)t[a[0]] + l + (ld)t[a[2]] * (ld)t[a[1]];
        if (abs(fi - se) < 1e-6 && fi > ma) {
            ma = fi;
            pans = a;
            ans = t;
            ans[3] = l;
        }
        //debug(a[0]); //debug(a[1]); debug(a[2]); debug(a[3]);
    }
    while (next_permutation(a.begin(), a.end()));

    debug(pans[0]);
    forn (i, 4)
        cout << pans[i] + 1 << " ";
    cout << '\n';
    cout << fixed;
    cout << setprecision(7);
    forn (i, 4)
        cout << ans[pans[i]] << " ";

    cout << "\n";
    debug(ans[pans[1]] * ans[pans[2]] + ans[pans[0]] + ans[pans[3]]);
    debug(ans[pans[1]] + ans[pans[2]] + ans[pans[0]] * ans[pans[3]]);
    return 0;
}

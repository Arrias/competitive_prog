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
#include <deque>
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

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    deque<int> a(n);
    forn(i, n) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    auto b = a;
    sort(all(b));
    deque<int> lens(m);
    forn(i, m) cin >> lens[i];
    vector<vector<int>> v;
    forn(i, m) {
        v.push_back({});
        while (lens[i]--) {
            v.back().push_back(a.front());
            a.pop_front();
        }
    }

    sort(all(v));
    for (auto i : v) {
        debr(all(i));
    }
    deque<int> newb;
    for (auto i : v) {
        for (auto j : i) {
            newb.push_back(j);
        }
    }
    //debr(all(newb));
    cout << (b == newb) << "\n";

    return 0;
}
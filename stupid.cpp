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

mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 5e5 + 40;
const int L = 3;

int a[3][N];
int n;

int used[3][N];
void paint(int i, int j, int l, int r, int cl) {
    if (i < 0 || j < 0 || i >= 3 || j < l || j > r || !a[i][j] || used[i][j]) return;
    used[i][j] = cl;
    paint(i-1,j,l,r, cl);
    paint(i+1,j,l,r,cl);
    paint(i,j+1, l,r,cl);
    paint(i,j-1,l,r,cl);
}

void solve() {
    cin >> n;
    forn(i, 3) {
        string b;
        cin >> b;
        forn(j, n) {
            a[i][j] = b[j] - '0';
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;

        forn(i, 3) forn(j, n) used[i][j] = 0;

        int cl = 1;
        forn(i, 3) {
            for (int j = l; j <= r; ++j) {
                if (used[i][j] || !a[i][j]) continue;
                paint(i, j, l, r, cl);
                cl++;
            }
        }

        cout << cl - 1 << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout.setf(ios::fixed);
    cout.precision(10);

    solve();

    return 0;
}


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

void solve() { 

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;

    queue <ll> a;
    forn (i, n) {
        ll lol;
        cin >> lol;
        a.push(lol - 1);
    }
    debug(1);
    vector <ll> all(n, -1);
    ll now = 0;
    deque <ll> fi, se;
    while (now < n) {
        if (all[now] == -1) {
            while (!a.empty()) {
                ll curr = a.front();
                a.pop();
                all[curr] = 1;
                fi.push_back(curr);
                cout << "1\n";
                if (curr == now)
                    break;
            }
        } 
        if (all[now] == 1) {
            while (!fi.empty()) {
                ll curr = fi.back();
                fi.pop_back();
                if (curr == now) {
                    all[curr] = 3;
                    cout << "-1\n";
                    break;
                }
                all[curr] = 2;
                cout << "12\n";
                se.push_back(curr);
            }
        }
        if (all[now] == 2) {
            while (!se.empty()) {
                ll curr = se.back();
                se.pop_back();
                if (curr == now) {
                    all[curr] = 3;
                    cout << "-2\n";
                    break;
                }
                all[curr] = 1;
                cout << "21\n";
                fi.push_back(curr);
            }
        }
        now++;
    }

    return 0;
}
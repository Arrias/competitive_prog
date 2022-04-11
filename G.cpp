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

    ld mx = 0;
    vector<int> perm;
    vector<ld> ans;

    vector<ld> a(4);
    for(auto &i : a)
        cin >> i;
    vector<int> p(4);
    for(int i = 0; i < 4; i++)
        p[i] = i;
    do {
        ld l = 3, r = 3;
        for(int i = 0; i < 1000; i++) {
            ld d = (l + r) / 2;
            ld D = pow(a[p[1]] * a[p[2]] - d, 2) - 4 * (d - a[p[1]] - a[p[2]]);
            vector<ld> arr(4);
            for(int i = 0; i < 4; i++)
                arr[i] = a[p[i]];
            //debug(arr[0]);
            //debug(arr[1]);
            arr[1] = (d - arr[2] - arr[3] * d + arr[3] * arr[3]) / (1 - arr[2] * arr[3]);
            arr[0] = d - arr[3] - arr[1] * arr[2];    
            if(arr[0] > a[p[0]] || arr[1] > a[p[1]])
                r = d;
            else l = d;
        }
        vector<ld> arr(4);
        for(int i = 0; i < 4; i++)
            arr[i] = a[p[i]];
        arr[1] = (l - arr[2] - arr[3] * l + arr[3] * arr[3]) / (1 - arr[2] * arr[3]);
        arr[0] = l - arr[3] - arr[1] * arr[2];
        debug(arr[0] * arr[3] + arr[1] + arr[2]);
        if(arr[0] * arr[3] + arr[1] + arr[2] > mx) {
            perm = p;
            ans = arr;
        }
    } while(next_permutation(all(p)));
        
    for(auto &i : perm)
        cout << i << " ";
    cout << "\n";
    for(auto &i : ans)
        cout << i << " ";
    return 0;
}

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

struct node {
    int lb, rb;
    pair<int, int> ans = { 0LL, 0LL };
    pair<int, int> lazy = { -1LL, -1LL };
    node *l, *r;

    node(int lq, int rq) : lb(lq), rb(rq) {
        if(lb + 1 < rb) {
            int mid = (lb + rb) / 2;
            l = new node(lb, mid);
            r = new node(mid, rb);
        }
    }

    void push() {
        if(lazy == make_pair(-1LL, -1LL)) return;
        ans.first = (rb - lb) * lazy.first;
        ans.second = (rb - lb) * lazy.second;
        if(lb + 1 < rb) {
            l->lazy = lazy;
            r->lazy = lazy;
        }
        lazy = make_pair(-1LL, -1LL);
    }

    void update() {
        if(lb + 1 < rb) {
            ans.first = l->ans.first + r->ans.first;
            ans.second = l->ans.second + r->ans.second;
        }
    }

    void setval(int lq, int rq, pair<int, int> x) {
        push();
        if(rq <= lb || rb <= lq)
            return;
        else if(lq <= lb && rb <= rq) {
            lazy = x;
            push();
        }
        else {
            l->setval(lq, rq, x);
            r->setval(lq, rq, x);
            update();
        }
    }

    pair<int, int> getval(int x) {
        push();
        if(x < lb || rb <= x)
            return {0, 0};
        else if(lb + 1 == rb)
            return ans;
        else {
            pair<int, int> left = l->getval(x);
            pair<int, int> right = r->getval(x);  
            return { left.first + right.first, left.second + right.second };
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    vector<pair<pair<int, int>, int>> p(n);
    for(auto &i : p)
        cin >> i.first.first >> i.first.second;
    for(int i = 0; i < n; i++)
        p[i].second = i;
    sort(all(p));

    vector<int> pfmax(n, 0), sfmin(n, 1e9);
    
    pfmax[0] = p[0].first.second;
    for(int i = 1; i < n; i++)
        pfmax[i] = max(pfmax[i - 1], p[i].first.second);
    for(int i = n - 2; i >= 0; i--)
        sfmin[i] = min(sfmin[i + 1], p[i + 1].first.second);

    vector<bool> merged(n);
    for(int i = 0; i < n; i++)
        merged[i] = (pfmax[i] > sfmin[i]);
    
    int cntr = 0;
    vector<int> ans(n);
    for(int i = n - 1; i >= 0; i--) {
        if(merged[i])
            cntr++;
        else cntr = 0;
        ans[p[i].second] = i + cntr;
    }
    for(int i = 0; i < n; i++)
        cout << ans[i] << "\n";
    return 0;
}

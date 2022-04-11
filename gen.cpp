#include <bits/stdc++.h>
#include "lib/gen/gen_functions.h"

#define all(a) begin(a), end(a)
#define forn(i, n) for (int i = 0; i < n; ++i)

using namespace std;

string symbs = "a.AbB/";

char get_next_symb() {
    return symbs[getRnd(0, symbs.size() - 1)];
}

string ggget(int n) {
    string ret;
    while (n--) { 
        ret += (char) (getRnd(0, 4) + 'a');
    }
    return ret;
}

void gen_graph() {
    int n = getRnd(2, 15);
    int m = getRnd(3, 15);
    cout << n << " " << m << "\n";
    forn(i, m) {
        int u = getRnd(1, n - 1);
        int v = getRnd(u + 1, n);
        int w = getRnd(1, 10);
        cout << u << " " << v << " " << w << "\n";
    }
    int u = getRnd(1, n - 1);
    int v = getRnd(u + 1, n);
    cout << u << " " << v << "\n";
}

void gen_tree(int n) {
    for (int i = 2; i <= n; ++i) {
        cout << getRnd(1, i - 1) << " " << i << "\n";
    }
}

int main() {
    int n = getRnd(1, 10);
    cout << n << "\n";
    forn(i,3) {
        forn(j,n) {
            cout << getRnd(0,1);
        }
        cout << "\n";
    }
    int q = getRnd(1,5);
    cout << q << "\n";
    while(q--) {
        int l = getRnd(1,n);
        int r = getRnd(l,n);
        cout << l << " " << r << "\n";
    }
    return 0;
}



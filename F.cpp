
#include <iostream>
#include <chrono>
#include <random>
#include <map>
#include <algorithm>
using namespace std;

#define all(X) begin(X), end(X)
#define mp make_pair
typedef long long ll;

signed main() {
    ios::sync_with_stdio(0);

    ll a, b, c, d, e, f, g;
    cin >> a >> b >> c >> d >> e >> f >> g;

    cout << e * f * g * (a * b + c * d);
    return 0;
} 

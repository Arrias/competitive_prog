//
// Created by arrias on 13.03.2021.
//

#pragma once 

#include <vector>
#include <string>

typedef long long ll;
using namespace std;

#include <cassert>
#include <random>
#include <chrono>

ll getRnd(ll l, ll r) {
    mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());
    return rnd() % (r - l + 1) + l;
}

ll getZnRnd(ll l, ll r) {
    mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());
    if (rnd() % 2)
        return getRnd(l, r);
    else
        return -getRnd(l, r);
}

vector<ll> getRndArray(ll n, ll l, ll r) {
    vector<ll> ret;
    for (int i = 0; i < n; ++i)
        ret.push_back(getRnd(l, r));
    return ret;
}

vector<ll> getUniqueArray(ll n, ll firL, ll firR, ll delta) {
    assert(delta > 0);
    vector<ll> ret;
    ret.push_back(getRnd(firL, firR));
    for (int i = 0; i < n - 1; ++i) {
        ret.push_back(getRnd(ret.back() + 1, ret.back() + delta));
    }
    return ret;
}

string getRandString(int n) {
    string ret;
    while (n--) {
        ret += (char) (getRnd(0, 25) + 'a');
    }
    return ret;
}


// #ifndef CF_GEN_FUNCTIONS_H
// #define CF_GEN_FUNCTIONS_H

// #include <vector>
// #include <string>

// typedef long long ll;
// using namespace std;

// ll getRnd(ll l, ll r);

// ll getZnRnd(ll l, ll r);

// vector<ll> getRndArray(ll n, ll l, ll r);

// vector<ll> getUniqueArray(ll n, ll firL, ll firR, ll delta);

// string getRandString(int n);

// #endif //CF_GEN_FUNCTIONS_H

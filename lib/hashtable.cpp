//
// Created by arrias on 27.05.2021.
//

template<int SZ>
struct HashTable {
    const int P = 1e9 + 7;
    vector<pi> chaines[SZ];
    int a, b;

    HashTable() : a(rnd() % P + 1), b(rnd() % P) {}

    int getHash(int x) {
        ll v = (((ll) a * (ll) x) % P + (ll) b) % P;
        return v % SZ;
    }

    int changeValue(int k, int newVal) {
        int pos = getHash(k);
        int finded = false;
        for (auto &[x, y] : chaines[pos]) {
            if (x == k) {
                y = newVal;
                finded = true;
                break;
            }
        }
        if (!finded) {
            chaines[pos].template emplace_back(k, newVal);
            return 0;
        }
        return 1;
    }

    int inc(int k, int add) {
        int pos = getHash(k);
        int finded = false;
        for (auto &[x, y] : chaines[pos]) {
            if (x == k) {
                y += add;
                finded = true;
                break;
            }
        }
        if (!finded) {
            chaines[pos].template emplace_back(k, add);
            return 0;
        }
        return 1;
    }

    int get(int k) {
        int pos = getHash(k);
        for (auto &[x, y] : chaines[pos]) {
            if (x == k) return y;
        }
        chaines[pos].template emplace_back(k, 0);
        return 0;
    }
};
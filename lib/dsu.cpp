struct dsu {
    vector<int> p, sz;

    dsu(int n) {
        p.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 0; i < p.size(); ++i) {
            p[i] = i;
        }
    }

    int get(int a) {
        if (p[a] == a) {
            return a;
        } else {
            return p[a] = get(p[a]);
        }
    }

    int merge(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return 0;
        if (rand() & 1) {
            p[b] = a;
            sz[a] += sz[b];
        } else {
            p[a] = b;
            sz[b] += sz[a];
        }
        return 1;
    }
};
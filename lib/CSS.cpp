struct Edge {
    int u, v;
    ll len;

    Edge(int u, int v, ll len) : u(u), v(v), len(len) {}

    int getOther(int a) {
        return (u == a) ? v : u;
    }

    bool operator<(Edge &o) {
        return len < o.len;
    }
};

template<int SZ>
struct CSS {
    vint g[SZ], p, rev[SZ], vis, tp;
    vlint dist;
    vector<Edge> e;
    int n = SZ;

    void clear(int lim) {
        rep(i, 0, lim + 1) g[i].clear();
    }

    void setSize(int sz) {
        n = sz;
    }

    void addDirEdge(int u, int v, ll len) {
        e.push_back(Edge(u, v, len));
        g[u].push_back((int) size(e) - 1);
        rev[v].push_back((int) size(e) - 1);
    }

    void topsort(int u) {
        vis[u] = 1;
        for (int num : g[u]) {
            int v = e[num].getOther(u);
            if (!vis[v]) {
                topsort(v);
            }
        }
        tp.push_back(u);
    }

    void paint(int u, int cl) {
        vis[u] = cl;
        for (int num : rev[u]) {
            int v = e[num].getOther(u);
            if (!vis[v]) {
                paint(v, cl);
            }
        }
    }

    int buildCSS() {
        tp.clear();
        vis.resize(n);
        rep(i, 0, n) {
            if (!vis[i]) {
                topsort(i);
            }
        }
        reverse(all(tp));
        fill(all(vis), 0);
        int cur_cl = 0;
        rep(i, 0, n) {
            if (!vis[tp[i]]) {
                paint(tp[i], ++cur_cl);
            }
        }
        return cur_cl;
    }
};

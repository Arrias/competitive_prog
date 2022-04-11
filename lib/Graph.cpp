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
struct Graph {
    vint g[SZ], p;
    vlint dist;
    vector <Edge> e;
    int n = SZ;

    void clear(int lim) {
        rep(i, 0, lim + 1);
        g[i].clear();
    }

    void setSize(int sz) {
        n = sz;
    }

    void addDirEdge(int u, int v, ll len) {
        e.push_back(Edge(u, v, len));
        g[u].push_back((int) size(e) - 1);
    }

    void addIndEdge(int u, int v, ll len) {
        addDirEdge(u, v, len);
        addDirEdge(v, u, len);
    }

    void dijkstra(int u) {
        using pli = pair<ll, int>;
        priority_queue <pli, vector<pli>, greater<pli>> q;
        dist.assign(n, 1e18);
        p.assign(n, -1);
        dist[u] = 0;
        q.push({0, u});
        while (q.size()) {
            auto[x, y] = q.top();
            q.pop();
            if (dist[y] != x) continue;
            for (int num : g[y]) {
                auto[to, edge] = make_pair(e[num].getOther(y), e[num].len);
                if (dist[to] > x + edge) {
                    p[to] = y;
                    dist[to] = x + edge;
                    q.push({dist[to], to});
                }
            }
        }
    }

    ll getDist(int u, int v) {
        dijkstra(u);
        return dist[v];
    }

    auto getDists(int u) {
        dijkstra(u);
        return dist;
    }

    auto getShortestPath(int v) { // after dijkstra
        vector<int> ret;
        while (v != -1) {
            ret.push_back(v);
            v = p[v];
        }
        reverse(all(ret));
        return ret;
    }
};

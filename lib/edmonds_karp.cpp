//
// Created by arrias on 26.12.2020.
//

class Edge {
public:
    int u, v, capacity, flow;
    Edge(int a, int b, int c, int d) : u(a), v(b), capacity(c), flow(d) {}
    int other(int x) {
        return (u == x) ? v : u;
    }
    int capacityTo(int x) {
        return (x == v) ? capacity - flow : flow;
    }
    void addFlow(int x, int y) {
        flow += (x == v) ? y : -y;
    }
};

class Graph {
public:
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> used;
    vector<int> edgeTo;
    void bfs(int v) {
        queue <int> q;
        q.push(v);
        used[v] = 1;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int num : g[now]) {
                int to = edges[num].other(now);
                if (!used[to] && edges[num].capacityTo(to)) {
                    used[to] = 1;
                    edgeTo[to] = num;
                    q.push(to);
                }
            }
        }
    }
    int hasPath(int from, int to) {
        fill(all(used), 0);
        bfs(from);
        return used[to];
    }
    int minEdge(int from, int to) {
        int ret = 2e9;
        for (int v = to; v != from; v = edges[edgeTo[v]].other(v)) {
            ret = min(ret, edges[edgeTo[v]].capacityTo(v));
        }
        return ret;
    }
    void addFlow(int from, int to, int x) {
        for (int v = to; v != from; v = edges[edgeTo[v]].other(v)) {
            edges[edgeTo[v]].addFlow(v, x);
        }
    }
    int maxFlow(int from, int to) {
        int ret = 0;
        while (hasPath(from, to)) {
            int d = minEdge(from, to);
            ret += d;
            addFlow(from, to, d);
        }
        return ret;
    }
    Graph(int n) {
        g.resize(n);
        used.resize(n);
        edgeTo.resize(n);
    }
    void addEdge(int u, int v, int len) {
        edges.push_back(Edge(u, v, len, 0));
        g[u].push_back(edges.size() - 1);
        g[v].push_back(edges.size() - 1);
    }
};
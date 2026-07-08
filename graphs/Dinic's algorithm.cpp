struct Dinic {
    struct edge {
        int v, u, c, f;
        edge() = default;
        edge(int v2, int u2, int c2, int f2) : v(v2), u(u2), c(c2), f(f2) {}
    };

    static const int INF = 1e9;
    vector<int> level, ptr;
    vector<vector<int>> g;
    vector<edge> edges;

    void add_edge(int v, int u, int c) { //add directed edge
        g[v].push_back((int) edges.size());
        edges.emplace_back(v, u, c, 0);
        g[u].push_back((int) edges.size());
        edges.emplace_back(u, v, 0, 0);
    }

    Dinic(int n) {//initialization
        level.resize(n), ptr.resize(n);
        g.resize(n);
    }

    bool bfs(int s, int t) {
        fill(all(level), -1);
        level[s] = 0;
        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int id: g[v]) {
                int u = edges[id].v ^ edges[id].u ^ v;
                if (level[u] == -1 && edges[id].c - edges[id].f > 0) {
                    level[u] = level[v] + 1;
                    Q.push(u);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int t, int f) {
        if (f == 0) return 0;
        if (v == t) return f;
        int pushed = 0;
        for (; ptr[v] < g[v].size(); ptr[v]++) {
            int id = g[v][ptr[v]];
            int u = edges[id].v ^ edges[id].u ^ v;
            if (level[u] != level[v] + 1)
                continue;
            int f2 = dfs(u, t, min(f, edges[id].c - edges[id].f));
            if (f2 != 0) {
                edges[id].f += f2;
                edges[id ^ 1].f -= f2;
                pushed += f2;
                if (pushed == f)
                    return f;
            }
        }
        return pushed;
    }

    int MaxFlow(int s, int t) {//get maximal flow from s to t
        int flow = 0;
        while (bfs(s, t)) {
            fill(all(ptr), 0);
            while (int pushed = dfs(s, t, INF))
                flow += pushed;
        }
        return flow;
    }
};

struct FordFalkerson {
    const int INF = 1e9;
    vector<vector<int>> g;
    vector<vector<int>> f, c;

    FordFalkerson(int n) {
        g.resize(n);
        f.resize(n, vector<int> (n));
        c.resize(n, vector<int> (n));
    }

    void add_edge(int v, int u, int _c) {
        g[v].push_back(u);
        c[v][u] += _c;
        g[u].push_back(v);
    }

    int dfs(int v, int t, int cur_flow, vector<bool> &used) {
        if (v == t)
            return cur_flow;
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u] && c[v][u] - f[v][u] > 0) {
                int flow = dfs(u, t, min(cur_flow, c[v][u] - f[v][u]), used);
                if (flow > 0) {
                    f[v][u] += flow;
                    f[u][v] -= flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    int MaxFlow(int s, int t) {
        int flow = 0, new_flow;
        vector<bool> used(g.size());
        while (new_flow = dfs(s, t, INF, used)) {
            flow += new_flow;
            fill(all(used), false);
        }
        return flow;
    }
};

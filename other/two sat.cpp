struct TwoSat {
    vector<vector<int>> g, gr;
    vector<int> comp, order;
    vector<bool> used;
    int n;

    TwoSat(int n) : n(n) {
        g.resize(n * 2), gr.resize(n * 2);
        comp.resize(n * 2), used.resize(n * 2);
    }

private:
    void add_edge(int v, int u) {
        g[v].push_back(u);
        gr[u].push_back(v);
    }

public:
    void add_or(int v, int u) {
        add_edge(v ^ 1, u);
        add_edge(u ^ 1, v);
    }

    vector<int> get() {
        auto dfs = [&](auto &&self, int v)->void {
            used[v] = true;
            for (int u : g[v]) {
                if (!used[u])
                    self(self, u);
            }
            order.push_back(v);
        };
        for (int v = 0; v < 2 * n; v++) {
            if (!used[v])
                dfs(dfs, v);
        }
        reverse(all(order));
        auto dfs2 = [&](auto &&self, int v, int c)->void {
            comp[v] = c;
            for (int u : gr[v]) {
                if (comp[u] == 0)
                    self(self, u, c);
            }
        };
        int c = 0;
        for (int v : order) {
            if (comp[v] == 0)
                dfs2(dfs2, v, ++c);
        }
        vector<int> ans(n);
        for (int v = 0; v < 2 * n; v += 2) {
            if (comp[v] == comp[v ^ 1]) {
                fill(all(ans), -1);
                return ans;
            }
            if (comp[v] > comp[v ^ 1])
                ans[v >> 1] = 1;
        }
        return ans;
    }
};

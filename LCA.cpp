struct LCA {
    const int k = 20;// (1 << (k + 1)) >= n !!!
    int t = 0;
    vector<vector<int>> g;
    vector<vector<int>> up;
    vector<int> tin, tout, depth;
    
    void dfs(int v, int p) {
        tin[v] = t++;
        up[v][0] = p;
        for (int i = 1; i < k; i++)
            up[v][i] = up[up[v][i - 1]][i - 1];
        for (int u : g[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
        tout[v] = t;
    }
    
    LCA(vector<vector<int>> g, int root=0) : g(g) {
        int n = (int) g.size();
        up.resize(n, vector<int> (k));
        tin.resize(n), tout.resize(n), depth.resize(n);
        dfs(root, root);
    }
    
    int get_lca(int v, int u) {
        auto is_par = [this](int v, int u){
            return tin[v] <= tin[u] && tout[v] >= tout[u];
        };
        if (is_par(v, u)) return v;
        if (is_par(u, v)) return u;
        for (int i = k - 1; i >= 0; i--) {
            int v2 = up[v][i];
            if (!is_par(v2, u))
                v = v2;
        }
        return up[v][0];
    }
    
    int get_dist(int v, int u) {
        int lca = get_lca(v, u);
        return depth[v] + depth[u] - depth[lca] * 2;
    }
};

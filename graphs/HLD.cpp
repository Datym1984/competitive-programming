// 1) set val in v
// 2) search max in path from v to u v->...->u
struct Segtree {
    vector<int> t;

    Segtree(int n = 0) : t(n * 4) {}

    void resize(int n) {
        t.resize(n * 4);
    }

    void upd(int v, int l, int r, int idx, int val) {
        if (l + 1 == r) {
            t[v] = val;
            return;
        }
        int m = (l + r) / 2;
        if (idx < m)
            upd(v * 2 + 1, l, m, idx, val);
        else
            upd(v * 2 + 2, m, r, idx, val);
        t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
    }

    int get(int v, int l, int r, int L, int R) {
        if (r <= L || R <= l)
            return 0;
        if (L <= l && r <= R)
            return t[v];
        int m = (l + r) / 2;
        return max(get(v * 2 + 1, l, m, L, R), get(v * 2 + 2, m, r, L, R));
    }
};

int n;
vector<int> A, tin, tout;
vector<int> head, sz, par;
vector<vector<int>> g;
Segtree segtree;
int timer = 0;

void dfs(int v, int p) {
    par[v] = p;
    sz[v] = 1;
    for (int i = 0; i + (v != p) < g[v].size(); i++) {
        if (g[v][i] == p)
            swap(g[v][i], g[v].back());
        int u = g[v][i];
        dfs(u, v);
        sz[v] += sz[u];
        if (sz[u] > sz[g[v][0]])
            swap(g[v][0], g[v][i]);
    }
    if (v != p)
        g[v].pop_back();
}

void build_hld(int v) {
    tin[v] = timer++;
    segtree.upd(0, 0, n, tin[v], A[v]);
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];
        if (i == 0)
            head[u] = head[v];
        else
            head[u] = u;
        build_hld(u);
    }
    tout[v] = timer;
}

bool is_ancestor(int p, int v) {
    return tin[p] <= tin[v] && tout[p] >= tout[v];
}

int get_hld(int v, int u) {
    if (tin[v] > tin[u])
        swap(v, u);
    int ans = 0;
    int cnt = 0;
    while (!is_ancestor(head[u], v)) {
        int res = segtree.get(0, 0, n, tin[head[u]], tin[u] + 1);
        ans = max(ans, res);
        u = par[head[u]];

        ++cnt;
        assert(cnt <= 100);
    }
    cnt = 0;
    while (!is_ancestor(head[v], u)) {
        int res = segtree.get(0, 0, n, tin[head[v]], tin[v] + 1);
        ans = max(ans, res);
        v = par[head[v]];

        ++cnt;
        assert(cnt <= 100);
    }
    int res = segtree.get(0, 0, n, min(tin[u], tin[v]), max(tin[u], tin[v]) + 1);
    ans = max(ans, res);
    return ans;
}

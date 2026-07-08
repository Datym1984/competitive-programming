struct DSU {
    int n, ans;
    vector<int> sz_cc, par_cc, par_2cc, par_t;
    vector<int> used;
    int t = 0;

    DSU(int n) : n(n) {
        ans = 0;
        sz_cc.resize(n, 1);
        par_cc.resize(n), iota(all(par_cc), 0);
        par_2cc.resize(n), iota(all(par_2cc), 0);
        par_t.resize(n), iota(all(par_t), 0);
        used.resize(n);
    }

    int get_comp(int v) {
        if (par_cc[v] == v)
            return v;
        return par_cc[v] = get_comp(par_cc[v]);
    }

    int get_main(int v) {
        if (par_2cc[v] == v)
            return v;
        return par_2cc[v] = get_main(par_2cc[v]);
    }

    void make_root(int v) {
        v = get_main(v);

        int last = v;
        v = get_main(par_t[v]);
        while (last != v) {
            int u = get_main(par_t[v]);
            par_t[v] = last;
            last = v;
            v = u;
        }
    }

    int get_lca(int v, int u) {
        t++;
        while (v != u) {
            if (v != -1 && used[v] == t)
                break;
            if (u != -1 && used[u] == t) {
                swap(v, u);
                break;
            }
            if (v != -1) used[v] = t;
            if (u != -1) used[u] = t;
            int pv = get_main(par_t[v]);
            v = v == -1 || pv == v ? -1 : pv;
            int pu = get_main(par_t[u]);
            u = u == -1 || pu == u ? -1 : pu;
        }
        return v;
    }

    void add_edge(int v, int u) {
        int cv = get_comp(v);
        int cu = get_comp(u);
        if (cv != cu) {//разные компоненты связности
            if (sz_cc[cv] < sz_cc[cu])
                swap(cv, cu);
            par_cc[cu] = cv;
            sz_cc[cv] += sz_cc[cu];

            cv = get_main(v);
            cu = get_main(u);
            make_root(cu);
            par_t[cu] = cv;
            ++ans;
            return;
        }
        cv = get_main(v);
        cu = get_main(u);
        if (cv == cu)//одна компонента рёберной двусвязности
            return;

        int lca = get_lca(cv, cu);
        while (cv != lca) {//сжатия вершин на пути от cv до cu в lca
            --ans;
            int p = get_main(par_t[cv]);
            par_2cc[cv] = lca;
            cv = p;
        }
        while (cu != lca) {
            --ans;
            int p = get_main(par_t[cu]);
            par_2cc[cu] = lca;
            cu = p;
        }
    }
};

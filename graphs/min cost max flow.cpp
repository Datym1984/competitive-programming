// search min cost max flow in O(V*E + F*E*log(V)), when F - max flow
struct MCMF {
    struct edge {
        int v, u;
        int f, c, w;

        edge(int v, int u, int f, int c, int w) : v(v), u(u), f(f), c(c), w(w) {}
    };

    int n;
    vector<vector<int>> g;
    vector<edge> e;
    vector<ll> P;

    MCMF(int n) : n(n), g(n), P(n) {}

    void add_edge(int v, int u, int c, int w) {
        g[v].push_back(e.size());
        e.emplace_back(v, u, 0, c, w);
        g[u].push_back(e.size());
        e.emplace_back(u, v, 0, 0, -w);
    }

    void ford_belman(int s) {
        fill(all(P), 1e18);
        P[s] = 0;
        bool changed = false;
        for (int i = 0; i < n; i++) {
            changed = false;
            for (int j = 0; j < e.size(); j++) {
                if (e[j].c - e[j].f == 0) continue;
                int v = e[j].v, u = e[j].u;
                if (P[v] + e[j].w < P[u]) {
                    P[u] = P[v] + e[j].w;
                    changed = true;
                }
            }
            if (!changed)
                break;
        }
    }

    pair<ll, ll> dijkstra(int s, int t) {
        vector<ll> dist(n, 1e18);
        dist[s] = 0;
        set<pair<ll, int>> Q;
        Q.emplace(0, s);
        vector<int> par(n, -1);
        while (!Q.empty()) {
            int v = Q.begin()->second;
            Q.erase(Q.begin());
            for (int i : g[v]) {
                if (e[i].c - e[i].f == 0) continue;
                int u = e[i].u;
                ll w = P[v] + e[i].w - P[u];
                if (dist[v] + w < dist[u]) {
                    Q.erase({dist[u], u});
                    dist[u] = dist[v] + w;
                    Q.emplace(dist[u], u);

                    par[u] = i;
                }
            }
        }
        ll cost = (dist[t] - P[s] + P[t]);
        for (int v = 0; v < n; v++)
            P[v] += dist[v];

        if (par[t] == -1)
            return mp(0, 0);
        ll flow = 1e18;
        int u = t;
        while (u != s) {
            flow = min<ll>(flow, e[par[u]].c - e[par[u]].f);
            u = e[par[u]].v;
        }
        cost *= flow;
        u = t;
        while (u != s) {
            e[par[u]].f += flow;
            e[par[u] ^ 1].f -= flow;
            u = e[par[u]].v;
        }
        return mp(flow, cost);
    }

    pair<ll, ll> min_cost_max_flow(int s, int t) {
        ll flow = 0, cost = 0;
        ford_belman(s);
        while (true) {
            auto [f, c] = dijkstra(s, t);
            flow += f;
            cost += c;
            if (f == 0)
                break;
        }
        return mp(flow, cost);
    }
};

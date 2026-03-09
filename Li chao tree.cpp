const ll inf = 2e18 + 10;
const int c = 1e9 + 10;

struct line {
    ll k=0, b=-inf;
    int idx=-1;

    line() = default;
    line(ll k, ll b, int idx) : k(k), b(b), idx(idx) {}

    ll operator[](ll x) {
        return k * x + b;
    }
};

struct li_chao {
    struct node {
        node *lc=nullptr, *rc=nullptr;
        line ln;
    };

    node *root = new node();

    ~li_chao() {
        del(root);
    }

    void del(node *v) {
        if (v == nullptr) return;
        del(v->lc), del(v->rc);
        delete v;
    }

    void expand(node *v) {
        if (v->lc == nullptr)
            v->lc = new node();
        if (v->rc == nullptr)
            v->rc = new node();
    }

    void add_line(node *v, int l, int r, line ln) {
        int m = (l + r) / 2;
        if (v->ln[m] < ln[m])
            swap(v->ln, ln);
        if (l + 1 == r) return;
        expand(v);
        if (ln[l] > v->ln[l]) {
            add_line(v->lc, l, m, ln);
        }
        if (ln[r] > v->ln[r]) {
            add_line(v->rc, m, r, ln);
        }
    }

    line get(node *v, int l, int r, ll x) {
        if (v == nullptr) return line();
        if (l + 1 == r)
            return v->ln;
        int m = (l + r) / 2;
        line res;
        if (x < m)
            res = get(v->lc, l, m, x);
        else
            res = get(v->rc, m, r, x);
        return (res[x] > v->ln[x] ? res : v->ln);
    }
};

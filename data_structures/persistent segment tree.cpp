//add to range and get sum on [:), can roll back to previous versions
struct node {
    ll sm=0, p=0;
    node *lc=nullptr, *rc=nullptr;
    node() = default;
    node(ll sm, ll p, node *lc, node *rc) :
        sm(sm), p(p), lc(lc), rc(rc) {}
    node(node *l, node *r) {
        sm = l->sm + r->sm;
        lc = l, rc = r;
    }

    node* apply(int l, int r, ll val) {
        node *v2 = new node(*this);
        v2->sm += val * (r - l);
        v2->p += val;
        return v2;
    }

    void push(int l, int r) {
        int m = (l + r) / 2;
        node *vl = lc->apply(l, m, p);
        node *vr = rc->apply(m, r, p);
        lc = vl, rc = vr;
        p = 0;
    }

    void expand() {
        if (lc == nullptr)
            lc = new node();
        if (rc == nullptr)
            rc = new node();
    }

    node* upd(int l, int r, int L, int R, ll val) {
        if (r <= L || R <= l || L >= R)
            return this;
        if (L <= l && r <= R)
            return apply(l, r, val);
        expand();
        push(l, r);
        int m = (l + r) / 2;
        node *vl = lc->upd(l, m, L, R, val);
        node *vr = rc->upd(m, r, L, R, val);
        return new node(vl, vr);
    }

    ll get(int l, int r, int L, int R) {
        if (r <= L || R <= l || L >= R)
            return 0ll;
        if (L <= l && r <= R)
            return sm;
        expand();
        push(l, r);
        int m = (l + r) / 2;
        return lc->get(l, m, L, R) + rc->get(m, r, L, R);
    }
};

template<typename T>
node* build(int l, int r, vector<T> &A) {
    if (l + 1 == r)
        return new node(-A[l], 0, nullptr, nullptr);
    int m = (l + r) / 2;
    return new node(build(l, m, A), build(m, r, A));
}

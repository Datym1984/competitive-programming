mt19937 gen(1984);

struct node {
    node *l=nullptr, *r=nullptr;
    int y;
    int sz=1, val, sm;
    node(int val) : val(val), sm(val), y(gen()) {}
};

int get_sz(node *v) {
    return v == nullptr ? 0 : v->sz;
}

int get_sm(node *v) {
    return v == nullptr ? 0 : v->sm;
}

void upd(node *v) {
    if (v == nullptr) return;
    v->sz = get_sz(v->l) + 1 + get_sz(v->r);
    v->sm = get_sm(v->l) + v->val + get_sm(v->r);
}

pair<node*, node*> splitk(node *v, int k) {
    if (v == nullptr) return mp(nullptr, nullptr);
    int lsz = get_sz(v->l);
    if (lsz >= k) {
        auto [v1, v2] = splitk(v->l, k);
        v->l = v2;
        upd(v);
        return mp(v1, v);
    }
    auto [v1, v2] = splitk(v->r, k - lsz - 1);
    v->r = v1;
    upd(v);
    return mp(v, v2);
}

node* merge(node *v1, node *v2) {
    if (v1 == nullptr) return v2;
    if (v2 == nullptr) return v1;
    if (v1->y < v2->y) {
        v2->l = merge(v1, v2->l);
        upd(v2);
        return v2;
    }
    v1->r = merge(v1->r, v2);
    upd(v1);
    return v1;
}

node* insert(node *v, int pos, int val) {
    auto [v1, v3] = splitk(v, pos);
    node* v2 = new node(val);
    return merge(merge(v1, v2), v3);
}

node* erase(node *v, int pos) {
    auto [v1, v23] = splitk(v, pos);
    auto [v2, v3] = splitk(v23, 1);
    delete v2;
    return merge(v1, v3);
}

pair<node*, int> get(node *v, int l, int r) {
    if (v == nullptr) return mp(v, 0);
    auto [v1, v23] = splitk(v, l);
    auto [v2, v3] = splitk(v23, r - l + 1);
    int res = v2->sm;
    return mp(merge(merge(v1, v2), v3), res);
}

void del(node *v) {
    if (v == nullptr) return;
    del(v->l), del(v->r);
    delete v;
}

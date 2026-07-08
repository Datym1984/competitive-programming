mt19937 gen(228);

struct node {
    node *l=nullptr, *r=nullptr;
    int x, y;
    int mn=0, mx=0;

    node(int val) : x(val), mn(val), mx(val), y(gen()) {}
};

int get_max(node *v) {
    return v == nullptr ? -inf : v->mx;
}

int get_min(node *v) {
    return v == nullptr ? inf : v->mn;
}

void update(node *v) {
    if (v == nullptr) return;
    v->mx = max({get_max(v->l), v->x, get_max(v->r)});
    v->mn = min({get_min(v->l), v->x, get_min(v->r)});
}

pair<node*, node*> split(node *v, int val) {
    if (v == nullptr) return mp(nullptr, nullptr);
    if (v->x < val) {
        auto [v1, v2] = split(v->r, val);
        v->r = v1;
        update(v), update(v2);
        return mp(v, v2);
    }
    auto [v1, v2] = split(v->l, val);
    v->l = v2;
    update(v1), update(v);
    return mp(v1, v);
}

node* merge(node *v1, node *v2) {
    if (v1 == nullptr) return v2;
    if (v2 == nullptr) return v1;
    if (v1->y < v2->y) {
        v2->l = merge(v1, v2->l);
        update(v2);
        return v2;
    }
    v1->r = merge(v1->r, v2);
    update(v1);
    return v1;
}

bool find(node *v, int val) {
    if (v == nullptr) return false;
    if (v->x == val) return true;
    if (v->x < val)
        return find(v->r, val);
    return find(v->l, val);
}

node* insert(node *v, int val) {
    if (find(v, val)) return v;
    auto [v1, v3] = split(v, val);
    node *v2 = new node(val);
    return merge(merge(v1, v2), v3);
}

node* erase(node *v, int val) {
    if (!find(v, val)) return v;
    auto [v1, v23] = split(v, val);
    auto [v2, v3] = split(v23, val + 1);
    return merge(v1, v3);
}

pair<node*, int> nxt(node *v, int val) {
    auto [v1, v2] = split(v, val + 1);
    int res = get_min(v2);
    return mp(merge(v1, v2), res);
}

pair<node*, int> prv(node *v, int val) {
    auto [v1, v2] = split(v, val);
    int res = get_max(v1);
    return mp(merge(v1, v2), res);
}

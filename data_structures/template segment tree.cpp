struct segtree {
    struct node {
        
    };
    vector<node> t;
    
    segtree(int n) {
        t.resize(n * 4);
    }
    
    void apply(int v, int l, int r, int val) {
        
    }
    
    void push(int v, int l, int r) {
        
    }
    
    node merge(node v1, node v2) {
        
    }
    
    template<class elem>
    void build(int v, int l, int r, vector<elem> &A) {
        if (l + 1 == r) {
            apply(v, l, r, A[l]);
            return;
        }
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m, A);
        build(v * 2 + 2, m, r, A);
        t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
    }
    
    node get(int v, int l, int r, int L, int R) {//get on subsegment[l:r)
        if (r <= L || R <= l)
            return node();
        if (L <= l && r <= R)
            return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return merge(get(v * 2 + 1, l, m, L, R), get(v * 2 + 2, m, r, L, R));
    }
    
    void upd(int v, int l, int r, int L, int R, int val) {// update on subsegment[l:r)
        if (r <= L || R <= l)
            return;
        if (L <= l && r <= R) {
            apply(v, l, r, val);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        upd(v * 2 + 1, l, m, L, R, val);
        upd(v * 2 + 2, m, r, L, R, val);
        merge(t[v * 2 + 1], t[v * 2 + 2]);
    }
};

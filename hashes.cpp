const int maxn = 1e5 + 10;

struct ModInt {
    static const int base1 = 29, mod1 = 1e9 + 7;
    static const int base2 = 31, mod2 = 999973423;//1e9 + 9;

    int val1, val2;

    ModInt(int val1=0, int val2=0) : val1(val1), val2(val2) {}
    
    friend ModInt operator+(const ModInt &a, const ModInt &b) {
        ModInt res(a.val1 + b.val1, a.val2 + b.val2);
        res.val1 -= (res.val1 >= ModInt::mod1) * ModInt::mod1;
        res.val2 -= (res.val2 >= ModInt::mod2) * ModInt::mod2;
        return res;
    }

    friend ModInt operator-(const ModInt &a, const ModInt &b) {
        ModInt res(a.val1 - b.val1, a.val2 - b.val2);
        res.val1 += (res.val1 < 0) * ModInt::mod1;
        res.val2 += (res.val2 < 0) * ModInt::mod2;
        return res;
    }

    friend ModInt operator*(const ModInt &a, const ModInt &b) {
        ModInt res(((ll) a.val1 * b.val1) % ModInt::mod1, ((ll) a.val2 * b.val2) % ModInt::mod2);
        return res;
    }

    friend bool operator==(const ModInt &a, const ModInt &b) {
        return a.val1 == b.val1 && a.val2 == b.val2;
    }

    friend bool operator<(const ModInt &a, const ModInt &b) {
        if (a.val1 == b.val1)
            return a.val2 < b.val2;
        return a.val1 < b.val1;
    }
};

array<ModInt, maxn> pows;

vector<ModInt> build_pref_hashes(string &s) {
    int n = (int) s.size();
    vector<ModInt> P(n);
    ModInt h;
    for (int i = 0; i < n; i++) {
        h = h * ModInt(ModInt::base1, ModInt::base2) + ModInt(s[i] - 'a' + 1);
        P[i] = h;
    }
    return P;
}

vector<ModInt> build_suf_hashes(string &s) {
    int n = (int) s.size();
    vector<ModInt> S(n);
    ModInt h;
    for (int i = n - 1; i >+ 0; i--) {
        h = h * ModInt(ModInt::base1, ModInt::base2) + ModInt(s[i] - 'a' + 1);
        S[i] = h;
    }
    return S;
}

ModInt get_hash(int l, int r, vector<ModInt> &A, int flag=0) {//flag = 0 -> straight hash, flag != 0 -> reverse hash; return hash substring[l:r]
    if (flag == 0) {
        if (l == 0)
            return A[r];
        return A[r] - A[l - 1] * pows[r - l + 1];
    }
    if (r + 1 == A.size())
        return A[l];
    return A[l] - A[r + 1] * pows[r - l + 1];
}

void precalc() {
    pows[0] = 1;
    for (int i = 1; i < pows.size(); i++)
        pows[i] = pows[i - 1] * ModInt(ModInt::base1, ModInt::base2);
}

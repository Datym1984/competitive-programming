struct ModInt {
    static constexpr int base1 = 29, base2 = 31;
    static constexpr int mod1 = 1e9 + 7, mod2 = 1e9 + 9;

    int val1 = 0, val2 = 0;

    ModInt() = default;
    ModInt(int val) : val1(val), val2(val) {}
    ModInt(int val1, int val2) : val1(val1), val2(val2) {}

    ModInt operator+(const ModInt &other) const {
        ModInt res(val1 + other.val1, val2 + other.val2);
        res.val1 -= (res.val1 >= mod1) * mod1;
        res.val2 -= (res.val2 >= mod2) * mod2;
        return res;
    }

    ModInt operator-(const ModInt &other) const {
        ModInt res(val1 - other.val1, val2 - other.val2);
        res.val1 += (res.val1 < 0) * mod1;
        res.val2 += (res.val2 < 0) * mod2;
        return res;
    }

    ModInt operator*(const ModInt &other) const {
        return ModInt((ll) val1 * other.val1 % mod1, (ll) val2 * other.val2 % mod2);
    }

    strong_ordering operator<=>(const ModInt &other) const = default;
};

const ModInt base(ModInt::base1, ModInt::base2);
const int maxn = 1e5 + 10;
vector<ModInt> pows(maxn, 1);

ModInt get_hash(int l, int r, vector<ModInt> &pref) {
    return pref[r] - (l == 0 ? 0 : (pref[l - 1] * pows[r - l + 1]));
}

void precalc() {
    for (int i = 1; i < pows.size(); i++)
        pows[i] = pows[i - 1] * base;
}

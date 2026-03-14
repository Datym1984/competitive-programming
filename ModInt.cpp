struct ModInt {
    static const int mod = 1e9 + 7;
    int val;

    ModInt(int val=0) : val(val) {}


    operator int() {
        return val;
    }

    friend istream& operator>>(istream &i, ModInt &x) {
        return i >> x.val;
    }

    friend ostream& operator<<(ostream &o, const ModInt &x) {
        return o << x.val;
    }

    friend ModInt operator+(const ModInt &lhs, const ModInt &rhs) {
        return (lhs.val + rhs.val) % mod;
    }

    friend ModInt& operator+=(ModInt &lhs, const ModInt &rhs) {
        lhs.val = (lhs.val + rhs.val) % mod;
        return lhs;
    }

    friend ModInt operator-(const ModInt &lhs, const ModInt &rhs) {
        return ((lhs.val - rhs.val) % mod + mod) % mod;
    }

    friend ModInt& operator-=(ModInt &lhs, const ModInt &rhs) {
        lhs.val = ((lhs.val - rhs.val) % mod + mod) % mod;
        return lhs;
    }

    friend ModInt operator*(const ModInt &lhs, const ModInt &rhs) {
        return ((ll) lhs.val * rhs.val) % mod;
    }

    friend ModInt& operator*=(ModInt &lhs, const ModInt &rhs) {
        lhs.val = ((ll) lhs.val * rhs.val) % mod;
        return lhs;
    }
};

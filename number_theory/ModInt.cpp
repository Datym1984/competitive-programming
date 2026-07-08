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
        return ModInt((lhs.val + rhs.val) % mod);
    }

    friend ModInt& operator+=(ModInt &lhs, const ModInt &rhs) {
        lhs.val = (lhs.val + rhs.val) % mod;
        return lhs;
    }

    friend ModInt operator-(const ModInt &lhs, const ModInt &rhs) {
        return ModInt(((lhs.val - rhs.val) % mod + mod) % mod);
    }

    friend ModInt& operator-=(ModInt &lhs, const ModInt &rhs) {
        lhs.val = ((lhs.val - rhs.val) % mod + mod) % mod;
        return lhs;
    }

    friend ModInt operator*(const ModInt &lhs, const ModInt &rhs) {
        return ModInt(((ll) lhs.val * rhs.val) % mod);
    }

    friend ModInt& operator*=(ModInt &lhs, const ModInt &rhs) {
        lhs.val = ((ll) lhs.val * rhs.val) % mod;
        return lhs;
    }

    friend ModInt operator/(const ModInt &lhs, const ModInt &rhs) {
        return lhs * rhs.power(mod - 2);
    }

    friend ModInt& operator/=(ModInt &lhs, const ModInt &rhs) {
        lhs = lhs / rhs;
        return lhs;
    }

private:
    ModInt power(int ind) const {
        if (ind == 0)
            return ModInt(1);
        else if (ind % 2 == 0) {
            ModInt res = power(ind / 2);
            return res * res;
        }
        else
            return this->power(ind - 1) * (*this);
    }
};

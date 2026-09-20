struct ModInt {
    static const int mod = 1e9 + 7;
    int val;

    ModInt(int val=0) : val(val) {}

    explicit operator int() {
        return val;
    }

    friend istream& operator>>(istream& i, ModInt &rhs) {
        return i >> rhs.val;
    }

    friend ostream& operator<<(ostream& o, const ModInt &rhs) {
        return o << rhs.val;
    }

    ModInt& operator+=(const ModInt& rhs) {
        val += rhs.val;
        val -= (val >= mod) * mod;
        return *this;
    }

    ModInt operator+(const ModInt& rhs) const {
        return ModInt(*this) += rhs;
    }

    ModInt& operator-=(const ModInt& rhs) {
        val -= rhs.val;
        val += (val < 0) * mod;
        return *this;
    }

    ModInt operator-(const ModInt& rhs) const {
        return ModInt(*this) -= rhs;
    }

    ModInt& operator*=(const ModInt& rhs) {
        val = (ll) val * rhs.val % mod;
        return *this;
    }

    ModInt operator*(const ModInt& rhs) const {
        return ModInt(*this) *= rhs;
    }

    ModInt operator/=(const ModInt& rhs) {
        *this *= rhs.power(mod - 2);
        return *this;
    }

    ModInt operator/(const ModInt& rhs) const {
        return ModInt(*this) /= rhs;
    }

private:
    ModInt power(int ind) const {
        ModInt res = 1;
        ModInt p = *this;
        while (ind) {
            if (ind & 1)
                res *= p;
            p *= p;
            ind >>= 1;
        }
        return res;
    }
};

//only +, +=, ==, <<, operations
struct BigInt {
    static const int base = 1e8;

    vector<int> ar;

    BigInt(int x = 0) {
        assert(x < base);
        ar.push_back(x);
    }

    friend BigInt operator+(const BigInt &lhs, const BigInt &rhs) {
        BigInt res; res.ar.pop_back();
        int i = 0, carry = 0;
        while (i < lhs.ar.size() || i < rhs.ar.size() || carry != 0) {
            ll sm = (ll) (i < lhs.ar.size() ? lhs.ar[i] : 0) + (i < rhs.ar.size() ? rhs.ar[i] : 0) + carry;
            res.ar.push_back(sm % base);
            carry = sm / base;
            i++;
        }
        return res;
    }

    friend BigInt& operator+=(BigInt &lhs, const BigInt &rhs) {
        return lhs = lhs + rhs;
    }

    friend bool operator==(const BigInt &, const BigInt &) = default;

    friend ostream& operator<<(ostream &o, BigInt x) {
        assert(!x.ar.empty());
        o << x.ar.back();
        for (int i = (int) x.ar.size() - 2; i >= 0; i--) {
            o << setfill('0') << setw(8) << x.ar[i];
        }
        return o;
    }
};

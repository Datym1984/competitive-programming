const ld eps = 1e-8;
const ld pi = acos(-1);

void fft(vector<complex<ld>> &A) {
    int n = A.size();
    assert((n & -n) == n);
    vector<int> rev(n);
    for (int i = 1; i < n; i++)
        rev[i] = (i & 1) * (n / 2) + rev[i / 2] / 2;
    for (int i = 0; i < n; i++) {
        if (i < rev[i])
            swap(A[i], A[rev[i]]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ld arg = (2 * pi) / len;
        complex<ld> w1{cos(arg), sin(arg)};
        for (int st = 0; st < n; st += len) {
            complex<ld> wi{1, 0};
            for (int i = st; i < st + len / 2; i++) {
                auto l = A[i], r = A[i + len / 2];
                A[i] = l + wi * r;
                A[i + len / 2] = l - wi * r;
                wi *= w1;
            }
        }
    }
}

vector<ll> mult(vector<int> A, vector<int> B) {
    int n = max(A.size(), B.size());
    while ((n & -n) != n) n += n & -n;
    n <<= 1;
    vector<complex<ld>> A2(n), B2(n);
    for (int i = 0; i < A.size(); i++)
        A2[i] = A[i];
    for (int i = 0; i < B.size(); i++)
        B2[i] = B[i];
    fft(A2);
    fft(B2);
    vector<complex<ld>> C2(n);
    for (int i = 0; i < n; i++)
        C2[i] = A2[i] * B2[i];
    fft(C2);
    vector<ll> C(n);
    for (int i = 0; i < n; i++) {
        assert(abs(C2[i].imag()) <= eps);
        C[i] = round(C2[i].real() / n);
    }
    reverse(C.begin() + 1, C.end());
    return C;
}

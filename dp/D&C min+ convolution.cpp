//A - concave vector i.e. A[i] - A[i - 1] <= A[i + 1] - A[i]
//B - arbitrary sequence
//C[i] = min<j>(B[j]+A[i-j])
//idea: C[i] - increasing
//solution in O(n*log(n))
vector<int> min_plus_convolution(int n, int m, vector<int> A, vector<int> B) {
    vector<int> C(n + m - 1);

    auto devide = [&](auto &&self, int l, int r, int opt_l, int opt_r)->void {
        if (l > r) return;
        int mid = (l + r) / 2;
        int opt_mid = max(mid - n + 1, opt_l);
        for (int i = max(mid - n + 1, opt_l); i <= min(mid, opt_r); i++) {
            if (B[i] + A[mid - i] < B[opt_mid] + A[mid - opt_mid])
                opt_mid = i;
        }

        C[mid] = opt_mid;
        self(self, l, mid - 1, opt_l, opt_mid);
        self(self, mid + 1, r, opt_mid, opt_r);
    };

    devide(devide, 0, n + m - 2, 0, m - 1);
    for (int i = 0; i < n + m - 1; i++)
        C[i] = B[C[i]] + A[i - C[i]];
    return C;
}

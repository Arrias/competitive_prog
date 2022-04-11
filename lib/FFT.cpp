ll double_to_int(long double c) {
    return (ll) (c + 0.5);
}

template<int SZ>
struct CFFT {   
    int ord[SZ];

    vector<pt> FFT(vector<pt> &a, int dg, bool isRev = false) {
        // a.size() = (1 << dg)

        for (int i = 1; i < a.size(); ++i) {
            ord[i] = (i & 1) * (1 << (dg - 1)) + (ord[i>>1] >> 1);
            if (ord[i] < i) {
                swap(a[i], a[ord[i]]);
            }
        }

        for (int lvl = 2; lvl <= (1 << dg); lvl *= 2) {
            int step = lvl / 2;

            long double angle = 2 * PI / lvl;
            if (isRev) angle *= -1;
            pt w0 = polar((long double)1.0, angle);

            for (int i = 0; i < a.size(); i += lvl) {
                pt w_1 = 1;
                pt w_2 = -1;

                for (int j = 0; j < step; ++j) {
                    auto A = a[i + j];
                    auto B = a[i + j + step];

                    a[i + j] = A + w_1 * B;
                    a[i + j + step] = A + w_2 * B;

                    w_1 *= w0;
                    w_2 *= w0;
                }
            }

            //debr(all(a));
        }

        if (isRev) {
            for (auto &i : a) i /= pt((1 << dg), 0);
        }

        return a;
    }

    vector<pt> mult(vector<pt> a, vector<pt> b) {
        int v = a.size() + b.size() - 1;
        int l = 0;
        while ((1 << l) < v) ++l;
        while (a.size() < (1 << l)) a.push_back(0);
        while (b.size() < (1 << l)) b.push_back(0);

        FFT(a, l);
        FFT(b, l);

        forn(i, a.size()) {
            a[i] *= b[i];
        }

        FFT(a, l, true);
        return a;
    }

    vector<pt> to_sqr(vector<pt> a) {
        int v = a.size() + a.size() - 1;
        int l = 0;
        while ((1 << l) < v) ++l;
        while (a.size() < (1 << l)) a.push_back(0);
        
        FFT(a, l);

        forn(i, a.size()) {
            a[i] *= a[i];
        }
        FFT(a, l, true);
        return a;
    }
};
int bpow(int n, int k, int mod) {
	if (!k) return 1;
	int c = bpow(n, k / 2, mod);
	c = (1ll * c * c) % mod;
	if (k & 1) {
		c = (1ll * c * n) % mod;
	}
	return c;
}

int testPherma(int n) {
	int a = rnd() % (n - 1) + 1;
	return bpow(a, n - 1, n) == 1;
}

int testMillerRabin(int n) {
	if (n % 2 == 0) {
		return n == 2;
	}
	if (!testPherma(n)) return 0;
	int c = n - 1;
	int k = 0;
	while (c % 2 == 0) {
		c /= 2;
		++k;
	}
	forn(cnt, 7) {
		int a = rnd() % (n - 1) + 1;
		a = bpow(a, c, n);
		forn(i, k) {
			int nxt = (1ll * a * a) % n;
			if (nxt == 1 && a != 1 && a != n - 1) return false;
			a = nxt;
		}
		if (a != 1) return false;
	}
	return true;
}

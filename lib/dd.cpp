//
// Created by arrias on 26.12.2020.
//

// sum is sum of x in subtree

struct D {
    ll x, y, sz, sum;
    D *l, *r;
    D(ll v) {
        x = sum = v;
        y = rand();
        sz = 1;
        l = r = 0;
    }
};

ll getSz(D *a) {
    if (a == 0) return 0;
    return a->sz;
}

ll getSum(D *a) {
    if (a == 0) return 0;
    return a->sum;
}

void upd(D *a) {
    if (a == 0) return;
    a->sz = 1 + getSz(a->r) + getSz(a->l);
    a->sum = a->x + getSum(a->r) + getSum(a->l);
}

D *merge(D *a, D *b) {
    if (!a) return b;
    if (!b) return a;
    if (a->y > b->y) {
        a->r = merge(a->r, b);
        upd(a);
        return a;
    }
    else {
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }
}

pair<D *, D*> split(D *a, ll k) {
    if (!a) return{ nullptr, nullptr };
    if (a->x <= k) {
        auto b = split(a->r, k);
        a->r = b.first;
        upd(a);
        return{ a, b.second };
    }
    else {
        auto b = split(a->l, k);
        a->l = b.second;
        upd(a);
        return{ b.first, a };
    }
}

pair<D *, D *> split_k(D *a, int k) {
    if (!a) return{ nullptr, nullptr };
    if (getSz(a->l) >= k) {
        auto b = split_k(a->l, k);
        a->l = b.second;
        upd(a);
        return{ b.first, a };
    }
    else {
        auto b = split_k(a->r, k - 1 - getSz(a->l));
        a->r = b.first;
        upd(a);
        return{ a, b.second };
    }
}

D *insert(D *a, ll el) {
    auto b = split(a, el);
    return merge(b.first, merge(new D(el), b.second));
}

D *erase(D *a, ll el) {
    auto b = split(a, el);
    auto c = split_k(b.first, getSz(b.first) - 1);
    return merge(c.first, b.second);
}

ll weryRight(D * a) {
    if (!a) return 0;
    if (!a->r) return a->x;
    return weryRight(a->r);
}

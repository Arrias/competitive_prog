struct AVL {
    struct Node {
        int x;
        int h;
        Node *l, *r;

        Node(int val) : x(val), h(0), l(0), r(0) {}
    };

    int h(Node *a) { return a ? a->h : 0; }
    int diff(Node * a) {return h(a->l) - h(a->r); }
    Node * left_son(Node * a) { return a ? a->l : 0; }
    Node * right_son(Node * a) { return a ? a->r : 0; }

    Node *root = nullptr;

    Node * rotateLeft(Node * v) {
        auto w = v->r;
        v->r = w->l;
        w->l = v;
        v->h = max(h(v->l), h(v->r)) + 1;
        w->h = max(h(w->l), h(w->r)) + 1;
        return w;
    }

    Node * rotateRight(Node * v) {
        auto w = v->l;
        v->l = w->r;
        w->r = v;
        v->h = max(h(v->l), h(v->r)) + 1;
        w->h = max(h(w->l), h(w->r)) + 1;
        return w;
    }

    Node * bigRotateLeft(Node * v) {
        v->r = rotateRight(v->r);
        return rotateLeft(v);
    }

    Node * bigRotateRight(Node * v) {
        v->l = rotateLeft(v->l);
        return rotateRight(v);
    }

    Node * rebalance(Node * v) {
        int df = diff(v);
        if (abs(df) <= 1) {
            v->h = max(h(v->l), h(v->r)) + 1;
            return v;
        }
        else if (df == -2) {
            if (diff(v->r) <= 0) {
                return rotateLeft(v);
            } else {
                return bigRotateLeft(v);
            }
        }
        else if (df == 2) {
            if (diff(v->l) >= 0) {
                return rotateRight(v);
            } else {
                return bigRotateRight(v);
            }
        }
        assert(false);
    }

    Node * insert(Node *a, int elem) {
        if (!a) return new Node(elem);
        if (a->x >= elem) {
            a->l = insert(a->l, elem);
        } else {
            a->r = insert(a->r, elem);
        }
        return rebalance(a);
    }

    void insert(int elem) {
        root = insert(root, elem);
    }

    template<class F> 
    void traverse(Node *a, F func) {
        if (!a) return;
        traverse(a->l, func);
        func(a->x);
        traverse(a->r, func);
    }

    void print() {
        traverse(root, [](int x) { cout << x << " "; });
    }
};

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>
#include <complex>
#include <queue>
#include <cassert>
#include <stack>
#include <random>
#include <chrono>
#include <map>
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) begin(a), end(a)
#define int long long
#define sqr(x) ((x) * (x))

#ifndef _debug
    #define debug(...) 42
    #define debr(...) 42
#else
    #define debug(x) cout << #x << " = " << x << endl
    #define debr(...) { cout << #__VA_ARGS__ << " = ";  _debr(__VA_ARGS__); }
#endif

using namespace std;

template<class Iter> 
void _debr(Iter l, Iter r) {
    cout << "[";
    for (auto it = l; it != r; ++it) {
        if (it != l) {
            cout << ", ";   
        }
        cout << *it;
    }
    cout << "]" << endl;
}

template<class C, class F> 
ostream& operator<<(ostream &out, pair<C, F> p) {
    return out << "(" << p.first << ", " << p.second << ")";
}

using ll = long long;

mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

struct RB_tree {
    int black = 0;
    int red = 1;

    struct Node {
        int x, cl;
        Node *l, *r, *parent;

        bool isTerm() const {
            return l == nullptr;
        }

        void swp() {
            cl ^= 1;
        }

        Node * other(Node * son) {
            return (son == l) ? r : l;
        }

        void setLson(Node * left) {
            left->parent = this;
            l = left;
        }

        void setRson(Node * right) {
            right->parent = this;
            r = right;
        }

        Node(int x, int cl, Node *oth, Node *par) :
             x(x), cl(cl), l(oth), r(oth), parent(par) {}
    };

    Node neutral = Node(-1, black, nullptr, nullptr);    
    Node *root = &neutral;

    Node * rotateRight(Node * p) {
        auto a = p->l;
        a->parent = p->parent;
        if (p->parent) {
            (p->parent->l == p) ? p->parent->setLson(a) 
                : p->parent->setRson(a);
        } 
        p->setLson(a->r);
        a->setRson(p);
        return a;
    }   

    Node * rotateLeft(Node * p) {
        auto a = p->r;
        a->parent = p->parent;
        if (p->parent) {
            (p->parent->l == p) ? p->parent->setLson(a) 
                : p->parent->setRson(a);
        } 
        p->setRson(a->l);
        a->setLson(p);
        return a;
    }

    Node * fixLeft(Node * a, Node * parent) {
        auto u = parent->other(a);

        if (u->cl == red) {
            u->swp();
            a->swp();
            parent->swp();
            return parent;
        }

        if (parent->r == a) {
            parent->r = rotateRight(a);
            parent = rotateLeft(parent);
            parent->swp();
            parent->l->swp();
        } 
        else {
            parent = rotateRight(parent);
            parent->swp();
            parent->r->swp();
        }

        return parent;
    }

    Node * fixRight(Node * a, Node * parent) {
        auto u = parent->other(a);

        if (u->cl == red) {
            u->swp();
            a->swp();
            parent->swp();
            return parent;
        }

        if (parent->l == a) {
            parent->l = rotateLeft(a);
            parent = rotateRight(parent);
            parent->swp();
            parent->r->swp();
        } 
        else {
            parent = rotateLeft(parent);
            parent->swp();
            parent->l->swp();
        }

        return parent;
    }

    Node * insert(Node * a, Node * parent, int key, bool &changed) {
        if (a->isTerm()) {
            return new Node(key, red, &neutral, parent);
        }

        bool chg = false;
        if (a->x >= key) {
            auto ret = insert(a->l, a, key, chg);
            if (chg) return ret;

            a->l = ret;
            if (a->cl == black || a->l->cl == black) return a;

            changed = true;
            return fixLeft(a, parent);
        } 
        else {
            auto ret = insert(a->r, a, key, chg);
            if (chg) return ret;
            
            a->r = ret;
            if (a->cl == black || a->r->cl == black) return a;

            changed = true;
            return fixRight(a, parent);
        }
    }

    Node * fixBlackHeightRightSon(Node * a, bool &isFixed) {
        isFixed = true;

        auto b = a->l;
        if (a->cl == red) {
            if (b->r->cl == red) {
                b = rotateLeft(b);
                a = rotateRight(a);
                a->cl = red;
                a->l->cl = a->r->cl = black;
                return a;
            }

            if (b->l->cl == red) {
                b = rotateRight(b);
                a = rotateRight(a);
                a->cl = red;
                a->l->cl = a->r->cl = black;
                return a;
            }

            a->cl = black;
            a->l->cl = red;
            return a;
        }

        if (b->cl == red) {
            auto c = b->r;
            if (c->l->cl == red) {
                b = rotateLeft(b);
                a = rotateRight(a);
                a->cl = a->r->cl = a->l->r->cl = black;
                a->l->cl = red;
                return a;
            }

            if (c->r->cl == red) {
                b = rotateLeft(b);
                a = rotateRight(a);
                a->cl = a->l->cl = a->r->l->cl = black;
                a->r->cl = red;
                return a;
            }

            a = rotateRight(a);
            a->cl = a->r->cl = black;
            a->r->l->cl = red;
            return a;
        }

        if (b->r->cl == red) {
            b = rotateLeft(b);
            a = rotateRight(a);
            a->cl = a->r->cl = a->l->cl = black;
            return a;
        }

        if (b->l->cl == red) {
            a = rotateRight(a);
            a->cl = a->r->cl = a->l->cl = black;
            return a;
        }

        isFixed = false;
        b->cl = red;
        return a;
    }

    Node * fixBlackHeightLeftSon(Node * a, bool &isFixed) {
        isFixed = true;

        auto b = a->r;
        if (a->cl == red) {
            if (b->r->cl == red) {
                b = rotateRight(b);
                a = rotateLeft(a);
                a->cl = red;
                a->l->cl = a->r->cl = black;
                return a;
            }

            if (b->l->cl == red) {
                b = rotateLeft(b);
                a = rotateLeft(a);
                a->cl = red;
                a->l->cl = a->r->cl = black;
                return a;
            }

            a->cl = black;
            a->r->cl = red;
            return a;
        }

        if (b->cl == red) {
            auto c = b->l;

            if (c->l->cl == red) {
                b = rotateRight(b);
                a = rotateLeft(a);
                a->cl = a->l->cl = a->r->l->cl = black;
                a->r->cl = red;
                return a;
            }

            if (c->r->cl == red) {
                b = rotateRight(b);
                a = rotateLeft(a);
                a->cl = a->r->cl = a->l->r->cl = black;
                a->l->cl = red;
                return a;
            }   

            a = rotateLeft(a);
            a->cl = a->l->cl = black;
            a->l->r->cl = red;
            return a;
        }

        if (b->l->cl == red) {
            b = rotateRight(b);
            a = rotateLeft(a);
            a->cl = a->l->cl = a->r->cl = black;
            return a;
        } 
        if (b->r->cl == red) {
            a = rotateLeft(a);
            a->cl = a->r->cl = a->l->cl = black;
            return a;
        }

        isFixed = false;
        b->cl = red;
        return a;
    }

    Node * erase(Node * a, int key, bool &isFixed) {
        if (a->x == key) {
            if (a->r->isTerm()) {
                if (a->l->isTerm()) {
                    isFixed |= (a->cl == red);
                    return &neutral;
                }
                isFixed = true;
                a->l->cl = black;
                a->l->parent = a->parent;
                return a->l;
            }

            if (!a->l->isTerm()) {
                Node * df = a->l;
                while (!df->r->isTerm()) df = df->r;
                a->x = df->x;
                a->l = erase(a->l, df->x, isFixed);
                return isFixed ? a : fixBlackHeightLeftSon(a, isFixed);
            }

            isFixed = true;
            a->r->cl = black;
            a->r->parent = a->parent;
            return a->r;
        }

        if (a->x > key) {
            a->l = erase(a->l, key, isFixed);
            return isFixed ? a : fixBlackHeightLeftSon(a, isFixed);
        } 
        else {
            a->r = erase(a->r, key, isFixed);
            return isFixed ? a : fixBlackHeightRightSon(a, isFixed);
        }
    }

    void erase(int a) {
        bool flag = false;
        root = erase(root, a, flag);
    }

    int getMin() {
        auto nd = root;
        while (!root->l->isTerm()) root = root->l;
        return root->x;
    }

    void insert(int key) {
        bool chg = false;
        root = insert(root, nullptr, key, chg);
        if (root->cl == red) root->swp();
    }

    template<class F> 
    void traverse(Node *a, F func) {
        if (a->isTerm()) return;
        traverse(a->l, func);
        func(a->x);
        //cout << a->cl << "\n";
        traverse(a->r, func);
    }

    void semafor(Node * a) {
        if (a->isTerm()) return;
        debug(a->x);
        debug(a->cl);
        debug(a->l->x);
        debug(a->r->x);
        debug("===");

        semafor(a->l);
        semafor(a->r);
    }

    void print() {
        traverse(root, [](int x) { cout << x << " "; });
        cout << "\n";
    }   

    void test_parent(Node * a) {
        if (a->isTerm()) return;
        assert(a->l->isTerm() || a->l->parent == a);
        assert(a->r->isTerm() || a->r->parent == a);
        test_parent(a->l);
        test_parent(a->r);
    }

    void test_parent() {
        test_parent(root);
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); 

    RB_tree a;
    forn(i, 100) a.insert(i);

    set<int> st;
    forn(i, 100) st.insert(i);
    forn(i, 100) {
        a.erase(i);
        st.erase(i);
        set<int> vt;
        a.traverse(a.root, [&](int y) {vt.insert(y);});
        assert(vt == st);
    }

    // RB_tree a;
    // forn(i, 1000) {
    //     a.insert(i);
    // }
    // forn(i, 1000) {
    //     a.erase(i);
    // }
    // a.erase(0); a.print();
    // a.erase(1); a.print();

    // a.semafor(a.root);
    // a.erase(2); a.print();


    // debug(a.root->cl);
    // a.semafor(a.root);
    // a.erase(0);
    // debug(a.root->cl);
    // a.erase(1);

    // a.print();
    // a.semafor(a.root);

    // a.erase(2);
    // a.print();

//    a.erase(4);

    // forn(i, 7) {
    //     a.erase(i);
    // }
    return 0;
}
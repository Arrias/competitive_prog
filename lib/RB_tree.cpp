template<typename T>
struct RB_tree {
    int black = 0, red = 1;
    
    struct Node {
        T x;
        int cl;
        Node * sons[2]{}, *parent;

        bool isTerm() const {
            return !sons[0];
        }

        void swp() {
            cl ^= 1;
        }

        Node * other(Node * son) {
            return sons[0] == son ? sons[1] : sons[0];
        }

        int sonId(Node * son) {
            return (sons[0] == son) ^ 1;
        }

        void setSon(int i, Node * son) {
            son->parent = this;
            sons[i] = son;
        }

        Node(T x, int cl, Node *oth, Node *par) : x(x), cl(cl), parent(par) {
            sons[0] = sons[1] = oth;
        }
    };

    Node neutral = Node(-1, black, nullptr, nullptr);    
    Node *root = &neutral;

    // {rotateRight, rotateLeft}
    Node * rotate(Node * p, int tp) {
        auto a = p->sons[tp];
        a->parent = p->parent;
        if (p->parent) {
            p->parent->setSon(p->parent->sonId(p), a);
        }
        p->setSon(tp, a->sons[tp ^ 1]);
        a->setSon(tp ^ 1, p);
        return a;
    }

    // {fixLeft, fixRight}
    Node * fixTwoReds(Node * a, int tp) {
        auto parent = a->parent;
        auto u = parent->other(a);

        if (u->cl == red) {
            u->swp();
            a->swp();
            parent->swp();
            return parent;
        }   

        if (parent->sonId(a) == tp ^ 1) {
            parent->sons[tp^1] = rotate(a, tp);
            parent = rotate(parent, tp ^ 1);
            parent->swp();
            parent->sons[tp]->swp();
        } 
        else {
            parent = rotate(parent, tp);
            parent->swp();
            parent->sons[1-tp]->swp();
        }

        return parent;
    }
    
    // {fixBlackHeightLeftSon, fixBlackHeightRightSon}
    Node * fixBlackHeight(Node * a, bool &isFixed, int tp) {
        isFixed = true;

        auto b = a->sons[tp ^ 1];
        if (a->cl == red) {
            if (b->sons[tp ^ 1]->cl == red) {
                b = rotate(b, tp);
                a = rotate(a, tp ^ 1);
                a->cl = red;
                a->sons[0]->cl = a->sons[1]->cl = black;
                return a;
            }

            if (b->sons[tp]->cl == red) {
                b = rotate(b, tp ^ 1);
                a = rotate(a, tp ^ 1);
                a->cl = red;
                a->sons[0]->cl = a->sons[1]->cl = black;
                return a;
            }

            a->cl = black;
            a->sons[tp ^ 1]->cl = red;
            return a;
        }

        if (b->cl == red) {
            auto c = b->sons[tp];

            if (c->sons[tp]->cl == red) {
                b = rotate(b, tp);
                a = rotate(a, tp ^ 1);
                a->cl = a->sons[tp]->cl = a->sons[tp ^ 1]->sons[tp]->cl = black;
                a->sons[tp ^ 1]->cl = red;
                return a;
            }

            if (c->sons[tp ^ 1]->cl == red) {
                b = rotate(b, tp);
                a = rotate(a, tp ^ 1);
                a->cl = a->sons[tp ^ 1]->cl = a->sons[tp]->sons[tp ^ 1]->cl = black;
                a->sons[tp]->cl = red;
                return a;
            }

            a = rotate(a, tp ^ 1);
            a->cl = a->sons[tp]->cl = black;
            a->sons[tp]->sons[tp ^ 1]->cl = red;
            return a;
        }

        if (b->sons[tp]->cl == red) {
            b = rotate(b, tp);
            a = rotate(a, tp ^ 1);
            a->cl = a->sons[tp]->cl = a->sons[tp ^ 1]->cl = black;
            return a;
        }

        if (b->sons[tp ^ 1]->cl == red) {
            a = rotate(a, tp ^ 1);
            a->cl = a->sons[tp]->cl = a->sons[tp ^ 1]->cl = black;
            return a;
        }

        isFixed &= false;
        b->cl = red;
        return a;
    }

    Node * insert(Node * a, Node * par, T key, bool &changed) {
        if (a->isTerm()) {
            return new Node(key, red, &neutral, par);
        }

        int ins_id = (a->x < key);

        bool chg = false;
        auto ret = insert(a->sons[ins_id], a, key, chg);
        
        if (chg) {
            return ret;
        }
        a->setSon(ins_id, ret);

        if (a->cl == black || a->sons[ins_id]->cl == black) {
            return a;
        }

        changed |= true;
        return fixTwoReds(a, ins_id);
    }

    Node * erase(Node * a, int key, bool &isFixed) {
        if (a->x == key) {
            if (a->sons[1]->isTerm()) {
                if (a->sons[0]->isTerm()) {
                    isFixed |= (a->cl == red);
                    return &neutral;
                }
                isFixed |= true;
                a->sons[0]->cl = black;
                a->sons[0]->parent = a->parent;
                return a->sons[0];
            }

            if (!a->sons[0]->isTerm()) {
                Node * df = a->sons[0];
                while (!df->sons[1]->isTerm()) df = df->sons[1];

                a->x = df->x;
                a->sons[0] = erase(a->sons[0], df->x, isFixed);
                return isFixed ? a : fixBlackHeight(a, isFixed, 0);
            }

            isFixed |= true;
            a->sons[1]->cl = black;
            a->sons[1]->parent = a->parent;
            return a->sons[1];
        }

        int er_id = (a->x < key);
        a->sons[er_id] = erase(a->sons[er_id], key, isFixed);
        return isFixed ? a : fixBlackHeight(a, isFixed, er_id);
    }

    void insert(T key) {
        bool tr = false;
        root = insert(root, nullptr, key, tr);
        if (root->cl == red) root->swp();
    }

    void erase(T key) {
        bool flag = false;
        root = erase(root, key, flag);
    }

    void print(Node * a) {
        if (a->isTerm()) return;
        print(a->sons[0]);
        cout << a->x << " ";
        print(a->sons[1]);
    }

    template<class F> 
    void traverse(Node *a, F func) {
        if (a->isTerm()) return;
        traverse(a->sons[0], func);
        func(a->x);
        //cout << a->cl << "\n";
        traverse(a->sons[1], func);
    }
};
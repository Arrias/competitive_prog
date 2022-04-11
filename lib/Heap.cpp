//
// Created by arrias on 26.05.2021.
//

template<int SZ, typename T>
struct Heap {
    T ar[SZ];
    int sz = 0;

    int size() const {
        return sz;
    }

    int empty() const {
        return sz == 0;
    }

    template<typename Iter>
    void build(Iter left, Iter right) {
        sz = 0;
        while (left != right) {
            ar[sz++] = (*left)++;
        }
    }

    void push(T elem) {
        ar[++sz] = elem;
        siftUp(sz);
    }

    T front() {
        return ar[1];
    }

    void pop() {
        swap(ar[1], ar[sz]);
        --sz;
        if (sz >= 1) {
            siftDown(1);
        }
    }

private:
    void siftUp(int i) {
        while (i > 1 && ar[i / 2] > ar[i]) {
            swap(ar[i], ar[i / 2]);
            i /= 2;
        }
    }

    void siftDown(int i = 1) {
        while ((i << 1) <= sz) {
            int j = (i << 1);
            if ((i << 1) + 1 <= sz && ar[(i << 1) + 1] < ar[j]) {
                ++j;
            }
            if (ar[i] <= ar[j]) break;
            swap(ar[i], ar[j]);
            i = j;
        }
    }
};
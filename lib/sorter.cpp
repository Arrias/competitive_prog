template<int N>
struct Sorter {
    int n;
    int p[N];
    int lb[N];
    int inv_p[N];
    int cnt[N];

    void init(int nn) {
        n = nn;
        iota(p, p + n, 0);
        iota(inv_p, inv_p + n, 0);
        lb[0] = 0;
        fill(cnt, cnt + n, 0);
        fill(lb + 1, lb + n, n);
    }

    void addOneTo(int x) {  
        int posTo = lb[cnt[x] + 1] - 1;
        if (p[x] != posTo) {
            int t = p[x];
            int who = inv_p[posTo];
            swap(p[x], p[who]);
            inv_p[posTo] = x;
            inv_p[t] = who;
        } 
        lb[cnt[x] + 1] = p[x];
        ++cnt[x];
    }

    void subOneTo(int x) {
        int posTo = lb[cnt[x]];
        if (p[x] != posTo) {
            int t = p[x];
            int who = inv_p[posTo];
            swap(p[x], p[who]);
            inv_p[posTo] = x;
            inv_p[t] = who;   
        }
        lb[cnt[x]]++;
        --cnt[x];
    }

    void info() {
        cout << "p is: ";
        print(p, p + n);
        cout << "inv_p is :";
        print(inv_p, inv_p + n);
        cout << "lb is: ";
        print(lb, lb + n);
        cout << "\n";
    }
};
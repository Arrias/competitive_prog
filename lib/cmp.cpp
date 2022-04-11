//
// Created by arrias on 08.02.2021.
//

vector<int> cmp(string t, string s) {
    string a = t + '#' + s;
    vector<int> pi(a.size());
    vector<int> ret;
    for (int i = 1; i < a.size(); ++i) {
        int j = pi[i - 1];
        while (true) {
            if (a[j] == a[i]) {
                j++;
                break;
            }
            if (j == 0) break;
            j = pi[j - 1];
        }
        pi[i] = j;
        if (j == t.size()) {
            ret.push_back(i - t.size());
        }
    }
    return ret;
}
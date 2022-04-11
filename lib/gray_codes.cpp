vector<int> gray_codes(int len) { // if you need changes ints to string 
    if (len == 1) {
        return vector < int > {0, 1};
    }
    auto p = gray_codes(len - 1);
    int g = p.size();
    for (int i = g - 1; i >= 0; --i) {
        p.push_back(p[i] ^ (1 << (len - 1)));
    }
    return p;
}
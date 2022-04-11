vint find_basis_z2(vint &masks, int len) {
    vint ret;
    vint temp = masks;
    for (int bit = len - 1; bit >= 0; --bit) {
        int id = -1;
        for (int i = 0; i < masks.size(); ++i) {
            if ((masks[i] >> bit) & 1) {
                id = i;
                break;
            }
        }
        if (id == -1) continue;
        for (int i = id + 1; i < masks.size(); ++i) {
            if ((masks[i] >> bit) & 1) {
                masks[i] ^= masks[id];
            }
        }
        ret.push_back(temp[id]);
        swap(temp[id], temp.back());
        swap(masks[id], masks.back());
        masks.pop_back();
        temp.pop_back();
    }
    return ret;
}

void add_vector(vlint &bazis, ll vec) {
    for (auto &i : bazis) {
        ckmin(vec, vec ^ i);
    }
    if (vec) {
        int ptr = 0;
        while (ptr < size(bazis) && bazis[ptr] > vec) { ptr++; }
        bazis.insert(bazis.begin() + ptr, vec);
    }
}
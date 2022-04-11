//
// Created by arrias on 26.12.2020.
//

struct Int {
    int top, bot, sign;
    Int(int A = 0, int B = 1, int S = 0) {
        top = A;
        bot = B;
        sign = S;
    }
    void norm() {
        if (bot * top < 0) sign = 1;
        bot = abs(bot);
        top = abs(top);
        int c = __gcd(bot, top);
        bot /= c;
        top /= c;
        if (top == 0) {
            bot = 1;
            sign = 0;
        }
    }
    void operator = (int chi) {
        top = chi;
        bot = 1;
        norm();
    }
    void inp() {
        double t;
        cin >> t;
        t *= 100;
        top = (int)t;
        bot = 100;
        sign = 0;
        norm();
    }
};

Int zero;

bool operator == (Int a, Int b) {
    a.norm();
    b.norm();
    return (a.bot == b.bot && a.top == b.top && a.sign == b.sign);
}

bool operator != (Int a, Int b) {
    return !(a == b);
}

bool operator < (Int a, Int b) {
    a.norm();
    b.norm();
    int avalue = a.top * b.bot;
    int bvalue = b.top * a.bot;
    if (a.sign) avalue *= -1;
    if (b.sign) bvalue *= -1;
    return avalue < bvalue;
}

bool operator > (Int a, Int b) {
    return !((a < b) || (a == b));
}

Int operator * (Int a, Int b) {
    Int res;
    a.norm(), b.norm();
    res.top = a.top * b.top;
    res.bot = a.bot * b.bot;
    res.sign = (a.sign ^ b.sign);
    return res;
}

Int operator + (Int a, Int b) {
    Int res;
    a.norm(), b.norm();
    int avalue = a.top * b.bot;
    if (a.sign) avalue *= -1;
    int bvalue = b.top * a.bot;
    if (b.sign) bvalue *= -1;
    res.top = avalue + bvalue;
    res.bot = a.bot * b.bot;
    res.norm();
    return res;
}

Int operator - (Int a, Int b) {
    b.sign ^= 1;
    return a + b;
}

void operator *= (Int &a, Int b) {
    a = a * b;
}

void operator += (Int &a, Int b) {
    a = a + b;
}

Int operator - (Int a) {
    a.norm();
    a.sign ^= 1;
    return a;
}
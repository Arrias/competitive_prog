//
// Created by arrias on 26.04.2021.
//

int ban[15];
ll n, k;
ll dp[50][2];

ll calc(string s) {
    for (int f = 1; f <= s[0] - '0'; ++f) {
        if (f != 8 && f != 9) continue;
        if (f < s[0] - '0')
            dp[0][1]++;
        else
            dp[0][0]++;
    }

    for (int d = 0; d < s.size() - 1; ++d) {
        rep(nxt, 0, 10) {
            if (nxt != 8 && nxt != 9) continue;
            dp[d + 1][1]++;
        }
        rep(nxt, 0, s[d + 1] -'0'+1) {
            if (nxt != 8 && nxt != 9) continue;
            int nxtw = 1;
            if (nxt == s[d+1]-'0') nxtw = 0;
            dp[d + 1][nxtw] += dp[d][0];
        }
        rep(nxt, 0, 10) {
            if (nxt != 8 && nxt != 9) continue;
            dp[d + 1][1] += dp[d][1];
        }
    }
    return dp[s.size() - 1][0] + dp[s.size() - 1][1];
}
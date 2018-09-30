#include <testlib.h>

#include <iostream>
#include <string>
#include <cassert>

const int maxans = 50000;
constexpr int maxn = 20;
int n, m;
bool board[maxn][maxn];

int func(int i, int j, const std::string &str) {
    for (char c : str) {
        switch (c) {
        case 'U':
            if (i > 0 && board[i - 1][j])
                i--;
            break;
        case 'D':
            if (i + 1 < n && board[i + 1][j])
                i++;
            break;
        case 'L':
            if (j > 0 && board[i][j - 1])
                j--;
            break;
        case 'R':
            if (j + 1 < m && board[i][j + 1])
                j++;
            break;
        }
    }
    return i * m + j;
}

int main(int argc, char **argv) {
    if (argc != 3) exit(1);
    registerValidation(argc, argv);
	
    freopen(argv[1], "r", stdin);

    n = inf.readInt(1, 20, "n");
    inf.readSpace();
    m = inf.readInt(1, 20, "m");
    inf.readEoln();
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = inf.readChar();
            assert(c == '0' || c == '1');
            board[i][j] = c != '0';            
        }
        inf.readEoln();
    }

    inf.readEof();

    fclose(stdin);

    freopen(argv[2], "r", stdin);

    std::string ans;
    ans = inf.readString();
    //  inf.readEoln();
    inf.readEof();

    int cnt = -1;
    bool flag = 1;

    if (ans.length() > maxans)
        flag = 0;
    for (int i = 0; i < (int)ans.size(); i++)
        if (ans[i] != 'U' && ans[i] != 'D' && ans[i] != 'L' && ans[i] != 'R')
            flag = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j]) {
                if (cnt == -1)
                    cnt = func(i, j, ans);
                else if (func(i, j, ans) != cnt)
                    flag = 0;
            }
    
    std::cout << (flag ? "AC\n" : "WA\n");
}


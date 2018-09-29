#include <iostream>
#include <set>
#include <string>
#include <utility>

constexpr int maxn = 20;
int n, m;
bool board[maxn][maxn];

bool visited[maxn][maxn];
char step[maxn * maxn][maxn * maxn]; /// next step from x to y

std::set<int> loc;
std::string ans;

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

void make() {
    std::string ans1;
    std::set<int>::iterator p = loc.begin();
    int x = *p;
    p++;
    int y = *p;

    while (x != y) {
        std::string a;
        a += step[x][y];
        x = func(x / m, x % m, a);
        y = func(y / m, y % m, a);
        ans1 = ans1 + a;
    }

    std::set<int> loc2;
    for (p = loc.begin(); p != loc.end(); p++) {
        x = *p;
        loc2.insert(func(x / m, x % m, ans1));
    }
    std::swap(loc, loc2);
    ans += ans1;
}

void dfs(int myi, int myj, int i, int j){
    visited[myi][myj] = 1;
    if (myi > 0 && !visited[myi - 1][myj]) {
        step[(myi - 1) * m + myj][i * m + j] = 'D';
        dfs(myi - 1, myj, i, j);
    }
    if (myi + 1 < n && !visited[myi + 1][myj]) {
        step[(myi + 1) * m + myj][i * m + j] = 'U';
        dfs(myi + 1, myj, i, j);
    }
    if (myj > 0 && !visited[myi][myj - 1]) {
        step[myi * m + myj - 1][i * m + j] = 'R';
        dfs(myi, myj - 1, i, j);
    }
    if (myj + 1 < m && !visited[myi][myj + 1]) {
        step[myi * m + myj + 1][i * m + j] = 'L';
        dfs(myi, myj + 1, i, j);
    }
}

int main() {
    std::cin >> n >> m;
    for (int i=0;i<n;i++) {
        std::string temp;
        std::cin >> temp;
        for (int j = 0; j < m; j++)
            board[i][j] = temp[j] != '0';
    }

    /// init
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j]) {
                for (int ii = 0; ii < n; ii++)
                    for (int jj = 0; jj < m; jj++)
                        visited[ii][jj] = 1 - board[ii][jj];
                dfs(i, j, i, j);
            }

    /// set
    for (int t = 0; t < n + m; t++)
        ans += "RD";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j])
                loc.insert(func(i, j, ans));

    /// main algorithm
    while (loc.size() > 1)
        make();

    std::cout << ans << "\n";
}


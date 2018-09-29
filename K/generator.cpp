#include "testlib.h"

#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int MAX_N = 20 + 7;
const int DX[4] = {-1, 1, 0, 0};
const int DY[4] = {0, 0, -1, 1};

inline int Rnd(int a, int b) {
    return rnd.next(b - a + 1) + a;
}

int par[MAX_N * MAX_N];

int find(int x) {
  if (x == par[x]) return x;
  else return par[x] = find(par[x]);
}

bool merge(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return 0;
  par[y] = x;
  return 1;
}

int n, m;
int A[MAX_N][MAX_N];
char B[MAX_N][MAX_N];
bool in_pq[MAX_N][MAX_N];

int get_id(int x, int y) {
  return x * m + y;
}

bool check(int x, int y) {
  if (A[x][y]) return 0;

  vector<int> ids;
  for (int i = 0; i < 4; i++) {
    int x2 = x + DX[i];
    int y2 = y + DY[i];
    if (x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) continue;
    ids.push_back(find(get_id(x2, y2)));
  }
  sort(ids.begin(), ids.end());
  for (int i = 1; i < (int)ids.size(); i++) {
    if (ids[i] == ids[i - 1]) return 0;
  }
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 4) exit(1);
  registerGen(argc, argv, 1);

  n = stoi(string(argv[1]));
  m = stoi(string(argv[2]));
  int k = stoi(string(argv[3]));

  for (int i = 0; i < n * m; i++) par[i] = i;

  priority_queue<tuple<int, int, int, int> > pq;
  int x = Rnd(0, n - 1);
  int y = Rnd(0, n - 1);
  pq.emplace(Rnd(1, 1000000000), x, y, 0);
  in_pq[x][y] = 1;
  while (!pq.empty() && k) {
    int state;
    tie(x, y, state) = tie(get<1>(pq.top()), get<2>(pq.top()), get<3>(pq.top()));

    in_pq[x][y] = 0;
    pq.pop();

    if (state == 0) {
      if (check(x, y)) A[x][y] = 1, k--;
      else continue;
    }

    vector<pair<int, int> > odr;
    for (int i = 0; i < 4; i++) {
      int x2 = x + DX[i];
      int y2 = y + DY[i];
      if (x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) continue;
      if (A[x2][y2]) merge(get_id(x, y), get_id(x2, y2));
      else if (check(x2, y2)) odr.emplace_back(x2, y2);
    }
    shuffle(odr.begin(), odr.end());
    if ((int)odr.size() == 0) continue;
    pair<int, int> p = odr[0];
    if (!in_pq[p.first][p.second]) {
        pq.emplace(Rnd(1, 1000000000), p.first, p.second, 0);
        in_pq[p.first][p.second] = 1;
    }
    if ((int)odr.size() > 1) {
        pq.emplace(Rnd(1, 1000000000), x, y, 1);
        in_pq[x][y] = 1;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        B[i][j] = A[i][j] + '0';
    }
    B[i][m] = 0;
  }

  println(n, m);
  for (int i = 0; i < n; i++)
    println(B[i]);

  return 0;
}


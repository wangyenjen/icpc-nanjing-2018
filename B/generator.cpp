#include "testlib.h"

#include <vector>
#include <algorithm>

using Data = long long;

inline Data Rnd(Data a, Data b) {
  return rnd.next(b - a + 1) + a;
}

void Reduce(Data& N, Data& K, std::vector<Data>& R) {
  R[0] = 0;
  std::sort(R.begin(),R.end());
  R.resize(N = std::unique(R.begin(), R.end()) - R.begin());
  if (K < 1) K = 1;
  if (K >= N) K = N - 1;
}

std::vector<Data> Produce1(Data& N, Data& K, int mode) {
  switch (mode) {
    case 0: K = Rnd(N * 5 / 31, N * 6 / 31); break;
    case 1: K = Rnd(N * 7 / 31, N * 8 / 31); break;
    case 2: K = Rnd(N * 15 / 31, N * 16 / 31); break;
    case 3: K = Rnd(N * 22 / 31, N * 26 / 31); break;
    case 4: K = Rnd(N * 29 / 31, N * 30 / 31); break;
    case 5: K = 1; break;
    case 6: K = std::sqrt(N); break;
    default: throw;
  }
  std::vector<Data> R;
  for (int i = 0; i < N; i++) R.push_back(Rnd(0, N * 3000));
  Reduce(N, K, R); return R;
}

std::vector<Data> Produce2(Data& N, Data& K, int mode) {
  K = 1;
  std::vector<Data> R;
  for (int i = 0; i < N / 2; i++) R.push_back(Rnd(0, N * 100));
  for (int i = 0; i < N / 2; i++) R.push_back(Rnd(N * 2900, N * 3000));
  Reduce(N, K, R); return R;
}

std::vector<Data> Produce3(Data& N, Data& K, int mode) {
  std::vector<Data> R;
  Data B = std::min(N, (Data)(sqrt(N) * 2 + 1));
  Data totB = (N - 1) / B + 1, span = N * 1500 / totB / 13;
  for (int i = 0; i < N; i++) {
    Data pos = (i / B * N * 3000 + 1500 * N) / totB;
    R.push_back(Rnd(pos - span, pos + span));
  }
  switch (mode) {
    case 0: K = totB * 3 / 4;
    case 1: K = totB * 5 / 4;
    case 2: K = totB * 7 / 4;
  }
  Reduce(N, K, R); return R;
}

template <class T> std::vector<T> Range(T a, T b) {
  std::vector<T> ret; ret.reserve(b - a);
  for (T i = a; i < b; i++) ret.emplace_back(i);
  return ret;
}

int main(int argc, char** argv) {
  if (argc != 4) exit(1);
  registerGen(argc, argv, 1);

  Data N = std::stol(std::string(argv[1])), K;
  int kind = std::stol(std::string(argv[2]));
  int mode = std::stol(std::string(argv[3]));

  std::vector<Data> lst;
  switch (kind) {
    case 0: lst = Produce1(N, K, mode); break;
    case 1: lst = Produce2(N, K, mode); break;
    case 2: lst = Produce3(N, K, mode); break;
    default: throw;
  }
  println(N, K);
  Data* begin = lst.data();
  println(begin, begin + lst.size());
}

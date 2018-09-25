#include <testlib.h>

#include <vector>
#include <algorithm>
#include <stdexcept>

template <class T> std::vector<T> Range(T a, T b) {
  std::vector<T> ret; ret.reserve(b - a);
  for (T i = a; i < b; i++) ret.emplace_back(i);
  return ret;
}

struct Edge {
  size_t u, v;
  Edge() : u(0), v(0) {}
  Edge(size_t u, size_t v) : u(u), v(v) {}
  bool operator==(const Edge& x) const { return u == x.u && v == x.v; }
  bool operator<(const Edge& x) const {
    return u < x.u || (u == x.u && v == x.v);
  }
};

class DirectedGraphGenerator {
  std::vector<Edge> edges_;
  size_t N_;

  void ThrowRange_() const {
    throw std::out_of_range("Vertex id out of range");
  }
  void AddEdge_(size_t u, size_t v) {
    edges_.emplace_back(u, v);
  }
  template <class T> void AddEdge_(size_t u, size_t v, const T& lst) {
    edges_.emplace_back(lst[u], lst[v]);
  }
  size_t CheckLst_() const { return N_; }
  template <class T> size_t CheckLst_(const T& lst) const {
    for (size_t i : lst) {
      if (i >= N_) ThrowRange_();
    }
    return lst.size();
  }
 public:
  DirectedGraphGenerator(size_t N = 1) : N_(N) {}
  size_t Edges() const { return edges_.size(); }
  size_t Vertices() const { return N_; }
  void Clear() { edges_.clear(); }
  void RemoveMultipleEdges() {
    std::sort(edges_.begin(), edges_.end());
    edges_.resize(std::unique(edges_.begin(), edges_.end()) - edges_.begin());
  }
  template <class... T> void AddRandomTree(bool toward_root, T&&... q) {
    size_t c = CheckLst_(q...);
    if (toward_root) { // root = 0
      for (size_t i = 1; i < c; i++) AddEdge_(i, rnd.next(i), q...);
    } else {
      for (size_t i = 1; i < c; i++) AddEdge_(rnd.next(i), i, q...);
    }
  }
  template <class... T> void AddCycle(T&&... q) {
    size_t c = CheckLst_(q...);
    for (size_t i = 1; i < c; i++) AddEdge_(i - 1, i, q...);
    AddEdge_(c - 1, 0, q...);
  }
  template <class... T>
  void AddRandomEdges(size_t num, bool loop = false, T&&... q) {
    size_t c = CheckLst_(q...);
    if (loop) {
      for (size_t i = 0; i < num; i++) {
        size_t u = rnd.next(c);
        size_t v = rnd.next(c);
        AddEdge_(u, v, q...);
      }
    } else {
      for (size_t i = 0; i < num; i++) {
        size_t u = rnd.next(c);
        size_t v = rnd.next(c - 1);
        if (u <= v) v++;
        AddEdge_(u, v, q...);
      }
    }
  }
  void AddEdge(size_t u, size_t v) {
    if (u >= N_ || v >= N_) ThrowRange_();
    AddEdge_(u, v);
  }
  void ResizeVertex(size_t N) {
    if (N < N_) {
      edges_.resize(std::remove_if(edges_.begin(), edges_.end(),
              [&](const Edge& ed){ return ed.u >= N || ed.v >= N; })
          - edges_.begin());
    }
    N_ = N;
  }
  void ShuffleEdges() { shuffle(edges_.begin(), edges_.end()); }
  const std::vector<Edge>& GetEdges() const { return edges_; }
  template <class T> void PrintEdges(const T& perm) {
    for (const Edge& i : edges_) println(perm[i.u], perm[i.v]);
  }
  void PrintEdges(bool shuffle_vertices = false) {
    if (shuffle_vertices) {
      PrintEdges(rnd.perm(N_, (size_t)0));
    } else {
      for (const Edge& i : edges_) println(i.u, i.v);
    }
  }
};

template <class T> void PrintVec(const std::vector<T>& v) {
  println(v.size());
  println(v.data(), v.data() + v.size());
}

void Gen(int argc, char** argv) {
  auto ArgStr = [&](size_t i){ return std::string(argv[i]); };
  auto ArgNum = [&](size_t i){ return std::stol(ArgStr(i)); };
  size_t N = ArgNum(0), cycsize = ArgNum(1), fac = ArgNum(2), Q = ArgNum(3);
  if (Q < 2) throw;
  DirectedGraphGenerator gen(N);

  for (size_t i = 0; i < N; i += cycsize) { // make graph strongly-connected
    std::vector<size_t> lst = Range(i, std::min(N, i + cycsize));
    if (i) {
      lst.insert(lst.begin() + rnd.next(lst.size()), rnd.next(i));
      lst.insert(lst.begin() + rnd.next(lst.size()), rnd.next(i));
    }
    gen.AddCycle(lst);
  }
  for (int i = 4; i < argc;) {
    auto str = ArgStr(i);
    size_t num = ArgNum(i + 1);
    if (str == "tree") {
      gen.AddRandomTree(true, rnd.perm(num, 0));
      i += 2;
    } else if (str == "rtree") {
      gen.AddRandomTree(false, rnd.perm(num, 0));
      i += 2;
    } else if (str == "random") {
      gen.AddRandomEdges(num, false, Range(0l, ArgNum(i + 2)));
      i += 3;
    } else if (str == "loop") {
      for (size_t i = 0; i < num; i++) {
        size_t u = rnd.next(N);
        gen.AddEdge(u, u);
      }
      i += 2;
    } else {
      throw;
    }
  }
  std::vector<std::vector<int>> adj(N, std::vector<int>(N));
  for (const Edge& i : gen.GetEdges()) adj[i.u][i.v]++;
  gen.Clear();
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      if (!adj[i][j]) continue;
      size_t g = rnd.next(fac) + 1;
      if (i == j && !rnd.next(5)) g *= 10;
      for (size_t k = 0; k < g; k++) gen.AddEdge(i, j);
    }
  }

  auto perm = rnd.perm(N, 0);
  println(N, gen.Edges(), Q);
  gen.ShuffleEdges();
  gen.PrintEdges(perm);
  {
    auto Z = Range(0, (int)N);
    Z[rnd.next(N - 2) + 2] = 0;
    for (int& i : Z) i = perm[i];
    PrintVec(Z);
    std::reverse(Z.begin(), Z.end());
    PrintVec(Z);
  }
  for (size_t i = 2; i < Q; i++) {
    size_t len = rnd.next(N / 2) + N / 2 + 1;
    std::vector<int> Z;
    for (size_t i = 0; i < len; i++) {
      Z.push_back(rnd.next(N));
      while (Z[Z.size() - 2] == Z.back()) Z.back() = rnd.next(N);
    }
    PrintVec(Z);
  }
}

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);
  Gen(argc - 1, argv + 1);
}

/// Author: Wang, Yen-Jen
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 100 + 7;

const double MIN_X = -100000.0;
const double MAX_X = 100000.0;

int N;
double X[MAX_N], Y[MAX_N], Z[MAX_N];

double calc(double x, double y, double z) {
	double res = 0;
	for (int i = 0; i < N; i++) {
		double dx = X[i] - x;
		double dy = Y[i] - y;
		double dz = Z[i] - z;
		double dis = sqrt(dx * dx + dy * dy + dz * dz);
		res = max(res, dis);
	}

	return res;
}

double calc_z(double x, double y) {
  double lb = MIN_X, rb = MAX_X;
  for (int times = 0; times < 50; times++) {
    double m1 = lb + (rb - lb) / 3;
    double m2 = rb - (rb - lb) / 3;

    if (calc(x, y, m1) > calc(x, y, m2)) lb = m1;
    else rb = m2;
  }

  return calc(x, y, (lb + rb) / 2);
}

double calc_y(double x) {
  double lb = MIN_X, rb = MAX_X;
  for (int times = 0; times < 50; times++) {
    double m1 = lb + (rb - lb) / 3;
    double m2 = rb - (rb - lb) / 3;

    if (calc_z(x, m1) > calc_z(x, m2)) lb = m1;
    else rb = m2;
  }

  return calc_z(x, (lb + rb) / 2);
}

double calc_x() {
  double lb = MIN_X, rb = MAX_X;
  for (int times = 0; times < 50; times++) {
    double m1 = lb + (rb - lb) / 3;
    double m2 = rb - (rb - lb) / 3;

    if (calc_y(m1) > calc_y(m2)) lb = m1;
    else rb = m2;
  }

  return calc_y((lb + rb) / 2);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%lf%lf%lf", &X[i], &Y[i], &Z[i]);

	printf("%.10f\n", calc_x());

	return 0;
}


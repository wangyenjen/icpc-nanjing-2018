/// Author: Wang, Yen-Jen
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const double EPS = 1e-4;
const int MAX_N = 100 + 7;

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

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%lf%lf%lf", &X[i], &Y[i], &Z[i]);

	double x = 0, y = 0, z = 0, step = 1;
	while (step > EPS) {
		double now_ans = calc(x, y, z);
		
		double tmp_ans = calc(x - step, y, z);
		if (tmp_ans < now_ans) {
			x -= step;
			continue;
		}

		tmp_ans = calc(x + step, y, z);
		if (tmp_ans < now_ans) {
			x += step;
			continue;
		}

		tmp_ans = calc(x, y - step, z);
		if (tmp_ans < now_ans) {
			y -= step;
			continue;
		}
		tmp_ans = calc(x, y + step, z);
		if (tmp_ans < now_ans) {
			y += step;
			continue;
		}

		tmp_ans = calc(x, y, z - step);
		if (tmp_ans < now_ans) {
			z -= step;
			continue;
		}

		tmp_ans = calc(x, y, z + step);
		if (tmp_ans < now_ans) {
			z += step;
			continue;
		}

		step *= 0.99;
	}

	printf("%.10f\n", calc(x, y, z));

	return 0;
}

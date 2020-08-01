#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

const int MAX = 100;

int maze[MAX][MAX];

int mark[MAX][MAX];

int distance(int x, int y) {
	int w = 30 - x;
	int v = 40 - y;
	return sqrt(w * w + v * v);
}

int main() {
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < 30; i++) {
		string tmp;
		cin >> tmp;
		for (int j = 0; j < 40; j++)
			maze[i][j] = tmp[j] - '0';
	}

	int path[1000][2];

	int p[2] = { 1, 1 };
	mark[1][1] = 1;
	int n = MAX;
	int pq[MAX][2];
	for (int i = 0; i < n; i++) {
		pq[i][0] = 0; pq[i][1] = 0;
	}
	int pqdis[MAX] = { 0, };

	int dir[9][2] = { {-1,-1},{-1,0},{1,-1},
						{-1,0}, {0,0}, {1,0},
						{-1,1}, {0,1}, {1,1} };

	path[0][0] = 1; path[0][1] = 1;
	int t = 0;

	int g = 0;

	while (!(pq[0][0] == N - 2 && pq[0][1] == M - 2)) {
		g++;
		if (!(pq[0][0] == 0 && pq[0][1] == 0)) {

			p[0] = pq[0][0];
			p[1] = pq[0][1];

			t++;
			path[t][0] = p[0]; path[t][1] = p[1];

			for (int i = 0; i < n - 1; i++) {
				pq[i][0] = pq[i + 1][0];
				pq[i][1] = pq[i + 1][1];
				pqdis[i] = pqdis[i + 1];
			}
		}
		for (int i = 0; i < 9; i++) {
			if (i != 4) {
				int temp[2] = { p[0] + dir[i][0] , p[1] + dir[i][1] };
				if (maze[temp[0]][temp[1]] == 0 && mark[temp[0]][temp[1]] == 0) {
					mark[temp[0]][temp[1]] = 1;
					int dis = distance(temp[0], temp[1]) + g;
					for (int j = 0; j < n; j++) {
						if (temp[0] == pq[j][0] && temp[1] == pq[j][1])	break;
						if (pqdis[j] == 0) {
							pqdis[j] = dis;
							pq[j][0] = temp[0];
							pq[j][1] = temp[1];
							break;
						}
						else if (pqdis[j] >= dis) {
							for (int k = n - 1; k > j; k--) {
								pq[k][0] = pq[k - 1][0];
								pq[k][1] = pq[k - 1][1];
								pqdis[k] = pqdis[k - 1];
							}
							pq[j][0] = temp[0];
							pq[j][1] = temp[1];
							pqdis[j] = dis;
							break;
						}
					}
				}
			}
		}
	}
	int c, d;
	int tf = t;
	int tp = t;
	int z = 0;
	for (int j = t; j > 1; j--) {
		int a = path[tf][0] - path[j - 1][0];
		int b = path[tf][1] - path[j - 1][1];

		if (a * a + b * b <= 2) {
			if (z == 1) {
				c = path[tf][0] - path[j - 2][0];
				d = path[tf][1] - path[j - 2][1];

				if (c * c + d * d <= 2)	j--;

				tp = j;
				z = 0;
				for (int i = tp; i < tf; i++) {
					path[i][0] = -1; path[i][1] = -1;
				}
				tf = j - 1;
				tp = j - 1;
			}
			else {
				tp = j - 1;
				tf = j - 1;
			}
		}
		else {
			z = 1;
		}
	}

	for (int i = 0; i <= t; i++) {
		if (!(path[i][0] == -1)) {
			maze[path[i][0]][path[i][1]] = -1;
		}
	}

	printf("\n");
	p[0] = pq[0][0]; p[1] = pq[0][1];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if ((p[0] == i && p[1] == j) || (maze[i][j] == -1))	printf("* ");
			else	printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}
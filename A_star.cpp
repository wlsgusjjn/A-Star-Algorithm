#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

const int MAX = 100;

int maze[MAX][MAX];

int mark[MAX][MAX];

int path[1000][2];
int t_path[1000][2];

int N, M, t;

int sx, sy, dx, dy;

void Astar(int sx, int sy, int dx, int dy);

int distance(int a, int b, int x, int y) {
	int w = a - x;
	int v = b - y;
	return sqrt(w * w + v * v);
}

int main() {
	N, M;
	cin >> N >> M;

	cout << "Source: ";
	cin >> sx >> sy;

	cout << "Destination: ";
	cin >> dx >> dy;


	// 1 = wall
	for (int i = 0; i < N; i++) {
		string tmp;
		cin >> tmp;
		for (int j = 0; j < M; j++) {
			maze[i][j] = tmp[j] - '0';
		}
	}

	Astar(sx, sy, dx, dy);

	int j = 0;
	for (int i = t; i > -1; i--) {
		t_path[j][0] = path[i][0];
		t_path[j][1] = path[i][1];

		int a, b;
		int z = -1;
		for (int k = i - 1; k > -1; k--) {
			a = t_path[j][0] - path[k][0];
			b = t_path[j][1] - path[k][1];
			if (a * a + b * b <= 2)
				z = k;
		}
		i = z + 1;
		j++;
	}

	for (int i = 0; i < j; i++)
		maze[t_path[i][0]][t_path[i][1]] = -1;

	printf("\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if ((sx == i && sy == j) || (maze[i][j] == -1))	printf("* ");
			else	printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

void Astar(int sx, int sy, int dx, int dy){
	int p[2] = { sx, sy };
	mark[sx][sy] = 1;
	int n = MAX;
	int pq[MAX][2];
	for (int i = 0; i < n; i++) {
		pq[i][0] = 0; pq[i][1] = 0;
	}
	for (int i = 0; i < 1000; i++) {
		path[i][0] = 0; path[i][1] = 0;
	}

	int pqdis[MAX] = { 0, };

	int dir[9][2] = { {-1,-1},{-1,0},{-1,1},
						{0,-1}, {0,0}, {0,1},
						{1,-1}, {1,0}, {1,1} };

	path[0][0] = sx; path[0][1] = sy;
	t = 0;
	int g = 0;

	while (!(pq[0][0] == dx && pq[0][1] == dy)) {
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
					int dis = distance(dx, dy, temp[0], temp[1]) + g;
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
	path[++t][0] = pq[0][0]; path[t][1] = pq[0][1];
}
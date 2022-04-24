#include<iostream>
#include<vector>
using namespace std;
int main() {
	setlocale(LC_ALL, "");
	unsigned int n;
	cout << "Введите кол-во вершин:";
	cin >> n;


	vector<vector<int>> graph(n, vector<int>(n));
	vector<bool> visited(n,{false});
	vector<pair<unsigned int,unsigned int>> path(n-1);
	unsigned int mincost=0;
	int min_;
	unsigned int path_index = 0;
	unsigned int posfirst=0, possec=0;


	cout << "Введите матрицу смежности:(в качестве значения вводится вес ребра, соединяющего i и j вершины)" << endl;
	for (unsigned int i = 0; i < n; ++i) {
		for (unsigned int j = 0; j < n; ++j) {
			cin >> graph[i][j];
			if (graph[i][j] == 0) {
				graph[i][j] = INT16_MAX;
			}
		}
	}


	cout << endl;
	vector<int> minimums;
	unsigned int ind_of_min = 0;
	for (unsigned int i = 0; i < n; ++i) {
		minimums.push_back(*min(graph[i].begin(), graph[i].end()));
	}
	int minimum = *min(minimums.begin(), minimums.end());
	ind_of_min = unsigned int(distance(minimums.begin(),find(minimums.begin(), minimums.end(), minimum)));
	visited[ind_of_min] = true;
	path[0].first = ind_of_min+1;


	while (path_index < n-1) {
		min_ = INT16_MAX;
		for (unsigned int i = 0; i < n; ++i) {
			for (unsigned int j = 0; j < n; ++j) {
				if (graph[i][j] < min_) {
						if (visited[i]) {
							min_ = graph[i][j];
							posfirst = i;
							possec = j;
					}
				}
			}
		}
		if (path_index == 0) {
			path[0].second = possec + 1;
			path_index++;
			mincost += min_;
			visited[possec] = true;
		}
		else {
			if (!visited[posfirst] or !visited[possec]) {
				path[path_index].first = posfirst + 1;
				path[path_index].second = possec + 1;
				path_index++;
				mincost += min_;
				visited[possec] = true;
			}
		}
		graph[posfirst][possec] = graph[possec][posfirst] = INT16_MAX;
	}
	cout << "Минимальное остовое дерево:(в виде ребер(вершина-вершина))"<<endl;
	for (unsigned int i = 0; i < n-1; ++i) {
		cout << path[i].first << "-" << path[i].second << endl;
	}
	cout <<endl<<"Минимальный вес:"<<mincost;

	return 0;
}
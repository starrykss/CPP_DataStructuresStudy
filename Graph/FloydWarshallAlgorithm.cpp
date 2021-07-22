/* ======================================================================================================
 * Title : 동적 계획법(Dynamic Programming)을 이용한 플로이드-워셜 알고리즘(Floyd-Warshall Algorithm) 구현
 * Author : starrykss
 * Date : 2021.07.22
 * Reference : 코딩 테스트를 위한 자료 구조와 알고리즘 with C++ (길벗)
 * =====================================================================================================*/

#include <iostream>
#include <vector>
using namespace std;

const int UNKNOWN = 1e9;

vector<vector<int>> FloydWarshall(int V, vector<vector<int>> weight) {
    vector<vector<int>> distance(V, vector<int>(V, UNKNOWN));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            distance[i][j] = weight[i][j];
        }
        distance[i][i] = 0;
    }

    for (int mid = 0; mid < V; mid++) {
        for (int start = 0; start < V; start++) {
            for (int end = 0; end < V; end++) {
                if (distance[start][mid] + distance[mid][end] < distance[start][end]) {
                    distance[start][end] = distance[start][mid] + distance[mid][end];
                }
            }
        }
    }

    for (int i = 0; i < V; i++) {
        // 자기 자신으로의 거리가 0보다 작으면 음수 가중치 사이클이 있는 것으로 판단.
        if (distance[i][i] < 0) {
            return {};
        }
    }

    return distance;
}

int main() {
    int V, E;

    cin >> V >> E;

    vector<vector<int>> weight(V, vector<int>(V, UNKNOWN));

    for (int i = 0; i < E; i++) {
        int u, v, w;
        
        cin >> u >> v >> w;

        weight[u][v] = w;
    }

    vector<vector<int>> distance = FloydWarshall(V, weight);

    if (distance.empty()) {
        cout << "음수 가중치 사이클이 있습니다." << endl;
        return 0;
    }

    for (int i = 0; i < V; i++) {
        cout << i << endl;

        for (int j = 0; j < V; j++) {
            cout << "\t" << j << ": ";

            (distance[i][j] == UNKNOWN) ? cout << "_" << endl : cout << distance[i][j] << endl;
        }
    }

    return 0;
}
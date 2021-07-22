/* =====================================================================================================
 * Title : 동적 계획법(Dynamic Programming)을 이용한 무한 개수 배낭 문제(Unbounded Knapsack Problem) 구현
 * Author : starrykss
 * Date : 2021.07.22
 * Reference : 코딩 테스트를 위한 자료 구조와 알고리즘 with C++ (길벗)
 * =====================================================================================================*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int UnboundedKnapsack(int items, int capacity, vector<int> values, vector<int> weight) {
    vector<int> DP(capacity + 1, 0);

    for (int w = 0; w <= capacity; w++) {
        for (int i = 0; i < items; i++) {
            if (weight[i] <= w) {
                DP[w] = max(DP[w], DP[w - weight[i]] + values[i]);
            }
        }
    }
    return DP[capacity];
}

int main() {
    int items, capacity;
    
    cin >> items >> capacity;

    vector<int> values(items), weight(items);

    for (auto& v : values) cin >> v;
    for (auto& w : weight) cin >> w;

    int result = UnboundedKnapsack(items, capacity, values, weight);

    cout << "배낭에 채울 수 있는 물건들의 최고 가격: " << result << endl;

    return 0;
}
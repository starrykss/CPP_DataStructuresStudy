/* =================================================================================================
 * Title : 동적 계획법(Dynamic Programming)을 이용한 0-1 배낭 문제(0-1 Knapsack Problem) 구현
 * Author : starrykss
 * Date : 2021.07.22
 * Reference : 코딩 테스트를 위한 자료 구조와 알고리즘 with C++ (길벗)
 * =================================================================================================*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Knapsack_01(int items, int capacity, vector<int> values, vector<int> weight) {
    vector<vector<int>> DP(items + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= items; i++) {
        int currentWeight = weight[i - 1];
        int currentValue = values[i - 1];

        for (int totalWeight = 1; totalWeight <= capacity; totalWeight++) {
            if (totalWeight < currentWeight) {
                DP[i][totalWeight] = DP[i - 1][totalWeight];
            }
            else {
                DP[i][totalWeight] = max(DP[i - 1][totalWeight], DP[i - 1][totalWeight - currentWeight] + currentValue);
            }
        }
    }

    return DP[items][capacity];
}

int main() {
    int items, capacity;
    
    cin >> items >> capacity;

    vector<int> values(items), weight(items);
    for (auto& v : values) cin >> v;
    for (auto& w : weight) cin >> w;

    int result = Knapsack_01(items, capacity, values, weight);

    cout << "배낭에 채울 수 있는 물건들의 최고 가격: " << result << endl;

    return 0;
}
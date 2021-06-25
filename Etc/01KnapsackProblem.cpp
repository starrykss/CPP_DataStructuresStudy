/* ==========================================================================
 * Title : 0-1 배낭 문제(0-1 Knapsack Problem) 구현
 * Author : starrykss
 * Date : 2021.06.25
 * Reference : https://www.tutorialspoint.com/cplusplus-program-to-solve-the-0-1-knapsack-problem
 * ==========================================================================*/

#include <iostream>
#include <climits>

#define max(A, B) (A > B) ? A : B

int KnapSack01(int Value[], int Weights[], int n, int T) {
    if (T < 0) {
        return INT_MIN;
    }
    if (n < 0 || T == 0) {
        return 0;
    }

    int in = Value[n] + KnapSack01(Value, Weights, n - 1, T - Weights[n]);
    int ex = KnapSack01(Value, Weights, n - 1, T);
    return max(in, ex);
}

int main() {
    // Knapsack #1
    int v[] = {10, 7, 15, 10, 12, 11, 5};       // Values of Items
    int w[] = {1, 2, 5, 9, 2, 3, 4};            // Weights of Items
    int T = 8;                                  // Capacity of Knapsack
    int n = sizeof(v) / sizeof(v[0]);           // Size of Value Set
    std::cout << "Knapsack Value is " << KnapSack01(v, w, n - 1, T);

    return 0;
}
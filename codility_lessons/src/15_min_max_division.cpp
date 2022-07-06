#include <vector>
#include <iostream>

using namespace std;

bool checkSolution(int mid, int k, const vector<int>& a) {
    int sum = 0;

    for(int i = 0; i < a.size(); i++){
        sum += a[i];

        if(sum > mid) {
            sum = a[i];
            k--;
        }
        if(k < 0){
            return false;
        }
    }
    return true;
}

int solution(int K, int M, vector<int> &A) {
    int maxSum = 0;
    int minSum = 0;

    // maxSum - sum of all elements
    // minSum - the max element
    for(const auto a: A) {
        maxSum += a;
        minSum = std::max(minSum, a);
    }

    int result = maxSum;
    while(minSum <= maxSum) {
        int mid = minSum + (maxSum - minSum) / 2;

        if(checkSolution(mid, K-1, A)) {
            maxSum = mid -1;
            result = mid;
        } else {
            minSum = mid + 1;
        }
    }

    return result;
}

void main() {
    vector<int> A {2, 1, 5, 1, 2, 2, 2};
    int K = 3;
    int M = 5;
    cout << "Solution: " << solution(K, M, A);
}
// you can use includes, for example:
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <random>

using namespace std;

class RandomNumber {
private:
    int from;
    int to;
    std::random_device                  rand_dev;
    std::mt19937                        generator;
    std::uniform_int_distribution<int>  distr;

public:
    RandomNumber(int _from, int _to)
        : from(_from), to(_to), generator(rand_dev()), distr(from, to)
    { }

    int get() {
        return distr(generator);
    }
};


int getIndex(int start, int end, vector<vector<int>> nails, int index) {
    int left = 0;
    int right = nails.size() - 1;
    int minIndex = -1;

    // binary search to get the min index of the sorted array of nails
    while(left <= right) {
        // avoid nasty overflows in getting the mid
        int mid = left + (right - left) / 2;

        if(nails[mid][0] < start)
            left = mid + 1;
        else if(nails[mid][0] > end)
            right = mid - 1;
        else {
            right = mid - 1;
            minIndex = mid;
        }
    }

    // nothing found
    if(minIndex == -1)
        return -1;

    int originalIndex = nails[minIndex][1];

    for(unsigned int i = minIndex; i < nails.size(); i++){
        if(nails[i][0] > end)
            break;

        originalIndex = min(originalIndex, nails[i][1]);

        if(originalIndex <= index)
            return index;
    }

    return originalIndex;
}

int solution(vector<int> &A, vector<int> &B, vector<int> &C) {
    // write your code in C++14 (g++ 6.2.0)
    int planks = A.size();
    int nails  = C.size();
    int result = 0;
    int visitedPlanks = 0;

    for (int i = 0; i < nails; i++) {

        int start = 0;
        int end = planks;
        int foundIndex = -1;

        while (start <= end) {
            int mid = start + (end - start) / 2;
            
            if (C[i] < abs(A[mid])) {
                end = mid - 1;
            } 
            else if (C[i] > B[mid]) {
                start = mid + 1;
            } 
            else {
                if (A[mid] > 0) {
                    A[mid] *= (-1);
                    ++visitedPlanks;
                }
                foundIndex = mid;

                // special case where C[i] = B[i] = A[i+1]
                if (mid < planks - 1 && C[i] == B[mid] && C[i] == abs(A[mid + 1])) {
                    if (A[mid + 1] > 0) {
                        A[mid + 1] *= (-1);
                        ++visitedPlanks;
                    }
                    foundIndex = mid + 1;
                }

                result++;
                end = mid - 1;
                
            }
        }

        // we have a nail with no plank to nail
        if (foundIndex == -1) {
            return -1;
        }

        // check if we finished
        // all planks were visited
        if (visitedPlanks == planks)
            break;
    }

    // could not nail all the planks with all the nails
    if (visitedPlanks < planks)
        return -1;

    return result;

}


void simple_test_1() {
    vector<int> A = { 1, 4, 5, 8 };
    vector<int> B = { 4, 5, 9, 10 };
    vector<int> C = { 4, 6, 7, 10, 2 };

    cout << "   >>> RESULT = " << solution(A, B, C);

   
}

void simple_test_2() {
    vector<int> A = { 1, 4, 5, 8 };
    vector<int> B = { 4, 5, 9, 10 };
    vector<int> C = { 4, 6, 7, 2, 10 };

    cout << "   >>> RESULT = " << solution(A, B, C);
}

void simple_test_3() {
    vector<int> A = { 1, 4, 5, 8 };
    vector<int> B = { 4, 5, 9, 10 };
    vector<int> C = { 4, 4, 6, 7, 7, 7, 7, 10, 2 };

    cout << "   >>> RESULT = " << solution(A, B, C);
}

void large_test_1() {
    vector<int> A;
    vector<int> B;
    vector<int> C;

    constexpr int SIZE = 10;

    A.reserve(SIZE * sizeof(int));
    B.reserve(SIZE * sizeof(int));
    C.reserve(SIZE * sizeof(int));

    RandomNumber rndPlank(1, SIZE);
    RandomNumber rndSmall(1, 10);

    for (unsigned int i = 0; i < SIZE; i++) {
        auto tmp = rndPlank.get();
        A.push_back(tmp);
        B.push_back(tmp);
        C.push_back(tmp);
    }

    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    std::sort(C.begin(), C.end());
    cout << "   >>> RESULT = " << solution(A, B, C);
}

void main() {
    large_test_1();


    //simple_test_1();
    //simple_test_2();
    //simple_test_3();
}
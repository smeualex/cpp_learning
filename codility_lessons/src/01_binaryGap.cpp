#include<iostream>

using namespace std;

int solution(int N) {
    int result = 0;
    bool addToResult = false;

    int tmpResult = 0;
    while (N) {
        int bit = N % 2;

        if (!bit && addToResult) {
            tmpResult++;
        }

        if (bit) {
            addToResult = true;
            if (tmpResult >= result) {
                result = tmpResult;
            }
            tmpResult = 0;
        }

        cout << "bit: " << bit << "; N: " << N
            << "; tmpResult: " << tmpResult
            << "; result: " << result << endl;
        N /= 2;
    }

    return result;
}


void main() {
    cout << "--------------------------------" << endl;
    cout << "Result = " << solution(1);

    cout << "--------------------------------" << endl;
    cout << "Result = " << solution(5);

    cout << "--------------------------------" << endl;
    cout << "Result = " << solution(561892);

    cout << "--------------------------------" << endl;
    cout << "Result = " << solution(74901729);

    cout << "--------------------------------" << endl;
    cout << "Result = " << solution(1376796946);
}
#include<iostream>
#include<vector>

using namespace std;

vector<int> solution(vector<int> &A, int K) {
    
    if (A.size() == 0)
        return A;

    int size = A.size();
    int rotations = K % size;

    if (rotations == 0)
        return A;


    vector<int> tmp(rotations);

    cout << "size:             " << size << endl;
    cout << "rotations:        " << rotations << endl;
    cout << "size - rotations: " << size - rotations << endl;

    int j = 0;
    for(int i = size - rotations; i < size; i++)
        tmp[j++] = A[i];

    cout << "tmp: ";
    for(const auto i: tmp)
        cout << i << " ";
    cout << endl;

    for(int i = size - 1; i >= rotations; i--) {
        cout << "A[" << i << "] = " << A[i]
            << " <-> A[" << i - rotations << "] = " << A[i - rotations] << endl;
        A[i] = A[i - rotations];
    }
        

    for(unsigned int i = 0; i < tmp.size(); i++){
        cout << "A[" << i << "] = " << tmp[i]
            << " <-> tmp[" << i << "] = " << tmp[i] << endl;
        A[i] = tmp[i];
    }

    return A;
}

void main() {
    cout << "-----------------------------------------------" << endl;
    std::vector<int> data1{ 1,2,3,4,5,6,7 };
    std::vector<int> s1 = solution(data1, 2);
    cout << "solution: ";
    for(int i = 0; i < s1.size(); i++)
        cout << s1[i] << " ";
    cout << endl;

    cout << "-----------------------------------------------" << endl;
    std::vector<int> data2{ 1,2,3,4,5,6,7 };
    std::vector<int> s2 = solution(data2, 0);
    cout << "solution: ";
    for (int i = 0; i < s2.size(); i++)
        cout << s2[i] << " ";
    cout << endl;

    cout << "-----------------------------------------------" << endl;
    std::vector<int> data3{ 1,2,3,4,5,6,7 };
    std::vector<int> s3 = solution(data3, 6);
    cout << "solution: ";
    for (int i = 0; i < s3.size(); i++)
        cout << s3[i] << " ";
    cout << endl;

    cout << "-----------------------------------------------" << endl;
    std::vector<int> data4{ };
    std::vector<int> s4 = solution(data4, 2);
    cout << "solution: ";
    for (int i = 0; i < s4.size(); i++)
        cout << s4[i] << " ";
    cout << endl;


    cout << endl;
}
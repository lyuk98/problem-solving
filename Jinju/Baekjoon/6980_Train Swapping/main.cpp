#include <iostream>
#include <vector>

using namespace std;


vector<int> train;
int length;

int bubbleSortSwaps() {
    int count = 0;
    for (int i = 0; i < length; i++) {
        for (int ii = 0; ii < length - i - 1; ii++) {
            if (train[ii] > train[ii + 1]) {
                swap(train[ii], train[ii + 1]);
                count++;
            }
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testCases;
    cin >> testCases;

    while (testCases--) {
        cin >> length;

        // Since the elements are being overwritten anyway,
        // it seems more efficient to resize the existing vector
        // instead of assigning a new container
        train.resize(length);
        
        for (int i = 0; i < length; ++i) {
            cin >> train[i];
        }

        // Using endl causes stream to flush,
        // which may take a long time if you have a lot to print
        cout << "Optimal train swapping takes " << bubbleSortSwaps() << " swaps.\n";
    }
}

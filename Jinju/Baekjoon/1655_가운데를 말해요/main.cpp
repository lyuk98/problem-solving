#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

vector<int> number;
vector<int> answer;

// 과거에 잠긴 나의 죽은 코드
//void findMid() {
//    sort(number.begin(), number.end());
//    
//    // cout << endl;
//    // cout << number.size() << endl;
//    // cout << ">>>> : ";
//    // for (int i : number) {
//    //     cout << i << ' ';
//    // }
//    
//    int size = number.size();
//    if(size % 2 == 0) {
//        answer.push_back(number[size / 2 - 1]);
//    }
//    else {
//        answer.push_back(number[size / 2]);
//    }
//}

//int main() {
//
//    int n;
//    cin >> n;
//    
//    int temp;
//    for(int i = 0; i < n; i++) {
//        cin >> temp;
//        number.push_back(temp);
//        findMid();
//    }
//    
//    for (int i : answer) {
//        cout << i << '\n';
//    }
//}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;
    
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    vector<int> answer;
    
    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        
        if(maxHeap.empty() || num <= maxHeap.top()){
            maxHeap.push(num);
        }
        else{
            minHeap.push(num);
        }
        
        if(minHeap.size() + 1 < maxHeap.size()){
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if(maxHeap.size() < minHeap.size()){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        answer.push_back(maxHeap.top());
    }
    
    for(int i : answer){
        cout << i << '\n';
    }
}

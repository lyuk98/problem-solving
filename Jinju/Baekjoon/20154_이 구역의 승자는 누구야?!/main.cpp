#include <iostream>
#include <deque>

using namespace std;

int numbers[] = { 3, 2, 1, 2, 3, 3, 3, 3, 1, 1, 3, 1, 3, 3, 1, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 1 };
string str;

deque<int> q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> str;
    
    for (char c : str) {
        q.push_back(numbers[c - 'A']);
    }
    
    int cnt = 0;
    while (true) {
        if(q.size() == 1) {
            cnt = q.at(0);
            break;
        }
        if(q.size() == 2) {
            cnt = q.at(0);
            q.pop_front();
            cnt += q.at(0);
            cnt %= 10;
            break;
        }
        int hing = q.size() / 2;
        int mem = 0;
        if(hing % 2 == 1) {
            mem = q.at(q.size()-1);
            q.pop_back();
        }
        for (int i = 0; i < hing; i++) {
            int a = q.at(0);
            q.pop_front();
            int b =q.at(0);
            q.pop_front();
            q.push_back((a+b)%10);
        }
        if (hing % 2 == 1) {
            q.push_back(mem);
        }
    }
    
    if(cnt == 0) {
        cout << "You're the winner?\n";
    }
    else if((cnt % 2) == 0) {
        cout << "You're the winner?\n";
    }
    else {
        cout << "I'm a winner!\n";
    }
}

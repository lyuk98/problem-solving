#include <iostream>
using namespace std;

void star(int i, int j, int num) {
    if((i / num)%3 == 1 && (j / num)%3 == 1) cout << ' ';
    else {
        if(num / 3 == 0) cout <<'*';
        else star(i,j,num/3);
    }
}

bool isBlank(int i, int j) {
    while(i > 0 || j > 0) {
        if (i % 3 == 1 && j % 3 == 1) return true;
        i /= 3;
        j /= 3;
    }
    return false;
}

int main() {
    int num;
    cin >> num;

    // 방법 1 : 재귀적 구조를 활용
    for(int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++)
            star(i,j,num);
        cout << '\n';
    }

    // 방법2  : 프랙탈 구조를 활용
    for(int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++) {
            if(isBlank(i, j)) cout << ' ';
            else cout << '*';
        }
        cout << '\n';
    }
}

#include <iostream>
#include <queue>

using namespace std;

int n;
int a, b;
int family[102][102];

struct hing {
    int y, x;
    int cnt;
};

int find() {
    queue<hing> q;
    q.push({a, 0, 0});
    
    while (!q.empty()) {
        hing top = q.front();
        q.pop();
        
        if((top.x == b) || (top.y == b)) {
            return top.cnt;
        }
        for (int i = 0; i <= n; i++) {
            if(family[top.y][i] == 1) {
                q.push({top.y, i, top.cnt+1});
                family[top.y][i] = 0;
            }
            if(family[i][top.x] == 1) {
                q.push({i, top.x, top.cnt+1});
                family[i][top.x] = 0;
            }
        }
    }
    
    return -1;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    cin >> a >> b;
    
    int m;
    cin >> m;
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        family[y][x] = 1;
        family[x][y] = 1;
    }
    
    cout << find();
    
}

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<string> map;
vector<vector<bool>> visit;

int h, w;
int findY[] = {0, -1, 0, 1};
int findX[] = {-1, 0, 1, 0};

struct Point {
    int y, x, cnt;
};

int BFS(int y, int x) {
    queue<Point> q;
    q.push({y, x, 1});
    visit[y][x] = true;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        if (current.y == h - 1 && current.x == w - 1) {
            return current.cnt;
        }

        for (int i = 0; i < 4; i++) {
            int newY = current.y + findY[i];
            int newX = current.x + findX[i];
            
            if (newY >= 0 && newY < h && newX >= 0 && newX < w) {
                if (map[newY][newX] == '1' && !visit[newY][newX]) {
                    visit[newY][newX] = true;
                    q.push({newY, newX, current.cnt + 1});
                }
            }
        }
    }

    return -1;
}

int main() {
    cin >> h >> w;
    visit = vector<vector<bool>>(h, vector<bool>(w, false));

    // Using .reserve(), in case you know the size in advance,
    // can prevent repeated allocations with .push_back()s
    map.reserve(h);

    for (int i = 0; i < h; i++) {
        string line;
        cin >> line;

        // Avoid expensive allocations
        // by std::move()ing variables with values no longer needed
        map.push_back(std::move(line));
    }
    
    cout << BFS(0, 0);
}

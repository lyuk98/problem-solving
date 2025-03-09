#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct tomato {
    int dy, dx, date;
};

int w, h;
vector<vector<int>> arr;
queue<tomato> q;

int dirY[] = { -1, 0, 1, 0 };
int dirX[] = { 0, -1, 0, 1 };

bool checkRipe() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (arr[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    cin >> w >> h;

    arr.resize(h, vector<int>(w));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) {
                q.push({ i, j, 0 });
            }
        }
    }

    if (checkRipe()) {
        cout << 0 << "\n";
        return 0;
    }

    int maxDate = 0;
    while (!q.empty()) {
        int y = q.front().dy;
        int x = q.front().dx;
        int date = q.front().date + 1;

        maxDate = max(maxDate, date);
        q.pop();

        for (int i = 0; i < 4; i++) {
            int dy = y + dirY[i];
            int dx = x + dirX[i];
            cout << '(' << dy << ", " << dx << ")\n";
            if (0 <= dy && dy < h && 0 <= dx && dx < w) {
                if (arr[dy][dx] == 0) {
                    arr[dy][dx] = 1;
                    q.push({ dy, dx, date });
                }
            }
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (arr[i][j] == 0) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }

    cout << maxDate - 1 << '\n';

}

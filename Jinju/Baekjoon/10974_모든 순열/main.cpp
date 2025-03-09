#include <iostream>
#include <vector>

using namespace std;

int n;
vector<bool> visited;
vector<vector<int>> result;

void solve(int idx, vector<int> v) {
    if (idx == n) {
        result.push_back(v); // 각 순열을 result에 저장
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            v.push_back(i);
            solve(idx + 1, v);
            visited[i] = false;
            v.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    visited.resize(n + 1, false); // 크기 조정 및 초기화

    solve(0, vector<int>());

    // 2차원 벡터에 저장된 모든 순열 출력
    for (const auto& permutation : result) {
        for (int num : permutation) cout << num << ' ';
        cout << '\n';
    }

    return 0;
}

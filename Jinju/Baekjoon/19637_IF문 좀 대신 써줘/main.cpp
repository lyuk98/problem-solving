#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <ranges>
#include <print>

using namespace std;

struct CombatPower {
    string name;
    int power;
    CombatPower(string n, int p) : name(n), power(p) {}
};

int N, M;
vector<CombatPower> cp;

string findCombatPower(int userPower) {
    auto it = lower_bound(cp.begin(), cp.end(), userPower, [](const CombatPower& c, int p) {
        return c.power < p;
        });
    return it->name;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    cp.reserve(N);

    for (int i : views::iota(0, N)) {
        string name;
        int power;
        cin >> name >> power;
        cp.emplace_back(name, power);
    }

    for (int i : views::iota(0, M)) {
        int userPower;
        cin >> userPower;
        println("{}", findCombatPower(userPower));
    }

    return 0;
}

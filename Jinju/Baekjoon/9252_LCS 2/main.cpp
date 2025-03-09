#include <iostream>
#include <vector>
using namespace std;

//string findLCS(string s1, string s2) {
//    int s1Length = (int)s1.length();
//    int s2Length = (int)s2.length();
//    
//    string longest = "";
//    for(int i = 0; i < s1Length; i++) {
//        string temp = "";
//        for(int j = i; j < s1Length; j++ ) {
//            for (int k = i; k < s2Length; k++) {
//                if(s1[j] == s2[k]) {
//                    temp+=s2[k];
//                    j++;
//                }
//            }
//        }
//        if(longest.length() < temp.length()) {
//            longest = temp;
//        }
//        
//    }
//    return longest;
//}

string findLCS(string s1, string s2) {
    // By using "auto,"
    // type of the variable is inferred from the right-hand side
    auto s1Length = s1.length();
    auto s2Length = s2.length();
    
    // DP 테이블을 선언 및 초기화
    // dp[i][j]는 s1의 처음 i개 문자와 s2의 처음 j개 문자 간의 LCS 길이를 저장합니다.
    vector<vector<int>> dp(s1Length + 1, vector<int>(s2Length + 1, 0));

    // DP 테이블을 채우기
    // s1[i-1]과 s2[j-1]이 같으면 dp[i][j] = dp[i-1][j-1] + 1,
    // 다르면 dp[i][j] = max(dp[i-1][j], dp[i][j-1])로 계산

    // Using "decltype(var)" eliminates the need
    // to specify the type of a variable
    for (decltype(s1Length) i = 1; i <= s1Length; i++) {
        for (decltype(s2Length) j = 1; j <= s2Length; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // dp 테이블의 마지막 값이 두 문자열 간의 LCS 길이
    int lcsLength = dp[s1Length][s2Length];

    // LCS 문자열을 추출하기 위한 역추적 단계
    // dp 테이블을 역방향으로 탐색하여 LCS 탐색
    // std::string is initialized without assignment
    string lcs;
    auto i = s1Length, j = s2Length;
    while (i > 0 && j > 0) {
        // s1[i-1]과 s2[j-1]이 같으면 해당 문자를 LCS에 추가
        if (s1[i - 1] == s2[j - 1]) {
            lcs = s1[i - 1] + lcs;
            i--;
            j--;
        }
        // dp[i-1][j]가 더 크면 위쪽에서 왔다는 의미로 i를 감소
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        // dp[i][j-1]이 더 크면 왼쪽에서 왔다는 의미로 j를 감소
        else {
            j--;
        }
    }

    // 최종적으로 구한 LCS 문자열을 반환합니다.
    return lcs;
}

int main() {
    string s1, s2;
    
    cin >> s1 >> s2;
//    if(s1.length() > s2.length()) {
//        s1.swap(s2);
//    }
//    string result = findLCS(s1, s2);
//    
//    cout << result.length() << '\n';
//    if(result.length()) {
//        cout << result << '\n';
//    }
    
    // LCS 계산 및 출력
    string result = findLCS(s1, s2);
    cout << result.length() << '\n';

    // std::string has built-in function to check if it is empty
    // checking against length() does its trick too,
    // but better to be verbose, right?
    if(!result.empty()) {
        cout << result << '\n';
    }
    
    return 0;
}

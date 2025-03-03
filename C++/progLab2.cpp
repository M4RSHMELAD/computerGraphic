#include <iostream>
#include <vector>
using namespace std;

vector<int> SavePatternValue(const string& pattern){
    int m = pattern.size();
    vector<int> pi(m, 0);
    int j = 0;

    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

int main(){
    string text, pattern;

    cout << "Введите строку" << endl;
    cin >> text;

    cout << "Введите строку-образец" << endl;
    cin >> pattern;

    SavePatternValue(pattern);

    return 0;
}
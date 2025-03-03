#include <iostream>
#include <vector>
using namespace std;

// Функция для вычисления префикс-функции
vector<int> computePrefixFunction(const string& pattern) {
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

// Функция для поиска подстроки в строке с использованием алгоритма
void KMPSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> pi = computePrefixFunction(pattern);
    int j = 0;

    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            cout << "Образец найден на индексе " << (i - m + 1) << endl;
            j = pi[j - 1];
        }
    }
}

int main() {
    string text, pattern;
    cout << "Введите строку: ";
    cin >> text;
    cout << "Введите образец: ";
    cin >> pattern;

    KMPSearch(text, pattern);

    return 0;
}

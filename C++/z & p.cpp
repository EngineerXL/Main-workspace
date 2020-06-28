#include <iostream>
#include <vector>

using namespace std;

vector<int> z_function(const string &s) {
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) {
			z[i] = min(z[i - l], r - i + 1);
		}
		while (z[i] + i < n and s[z[i] + i] == s[z[i]]) {
			z[i]++;
		}
		if (z[i] + i - 1 > r) {
			l = i, r = z[i] + i - 1;
		}
	}
	return z;
}

vector<int> prefix_function(string s) {
	int n = s.size();
	vector<int> p(n);
	for (int i = 1; i < n; i++) {
		int cur = p[i - 1];
		while (0 < cur and s[i] != s[cur]) {
			cur = p[cur - 1];
		}
		if (s[i] == s[cur]) {
			cur++;
		}
		p[i] = cur;
	}
	return p;
}

signed main() {
	string s, t;
	cin >> s >> t;
	s = t + "#" + s;
	/* Поиск подстроки с помощью префикс-функции */
	vector<int> p = prefix_function(s);
	for (int i = t.size(); i < s.size(); i++) {
		if (p[i] == t.size()) {
			cout << i - 2 * t.size() << ' ';
		}
	}
	/* Поиск подстроки с помощью Z-функции */
	vector<int> z = z_function(s);
	for (int i = t.size(); i < s.size(); i++) {
		if (z[i] == t.size()) {
			cout << i - t.size() - 1 << ' ';
		}
	}
}

#include <iostream>
#include <vector>

using namespace std;

vector<int> prefix(string s) {
	int n = s.size();
	vector<int> pref(n);
	for (int i = 1; i < n; i++) {
		int j = pref[i - 1];
		while (j > 0 and s[j] != s[i]) {
			j = pref[j - 1];
		}
		if (s[j] == s[i]) {
			j = j + 1;
		}
		pref[i] = j;
	}
	return pref;
}

signed main() {
	string s, t;
	cin >> s >> t;
	int m = t.size();
	s = t + "#" + s;
	vector<int> pref = prefix(s);
	for (int i = 0; i < s.size(); i++) {
		if (pref[i] == m) {
			cout << i - 2 * m << " ";
		}
	}
}

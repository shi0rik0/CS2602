#include <iostream>
#include <climits>

using namespace std;

int main() {
	int N;
	cin >> N;
	int m = INT_MAX;
	int b = 0;
	for (int _ = 0; _ < N; ++_) {
		int n;
		cin >> n;
		if (n < m) {
			m = n;
			continue;
		}
		if (n - m > b) {
			b = n - m;
		}
	}
	cout << b;
	return 0;
}
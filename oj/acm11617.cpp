#include <iostream>

using namespace std;

const int SIZE = 605;

char* add_two_string(char* p, char* q);

int main() {
	char s1[SIZE];
	char s2[SIZE];
	int n1;
	int n2;
	cin >> n1 >> n2;
	while (cin.get() != '\n') {

	}
	int i = 0;
	for (i = 0; i < n1 - 1; ++i) {
		s1[i] = cin.get();
	}
	s1[i] = '\0';
	while (cin.get() != '\n') {

	}
	for (i = 0; i < n2 - 1; ++i) {
		s2[i] = cin.get();
	}
	s2[i] = '\0';
	char* s3 = add_two_string(s1, s2);
	cout << s3;
	return 0;
}

char* add_two_string(char* p, char* q) {
	static char ans[SIZE];

	int n1 = 0;
	int n2 = 0;
	while (p[n1]) {
		++n1;
	}
	while (q[n2]) {
		++n2;
	}

	int carry = 0;
	int i = 0;
	for (i = 0; i < n1 || i < n2; ++i) {
		int d1 = i < n1 ? p[i] - '0' : 0;
		int d2 = i < n2 ? q[i] - '0' : 0;
		int sum = d1 + d2 + carry;
		ans[i] = sum % 10 + '0';
		carry = sum / 10;
	}
	if (carry) {
		ans[i++] = '1';
	}
	ans[i] = '\0';
	return ans;
}

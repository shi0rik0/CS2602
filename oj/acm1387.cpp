#include <iostream>
#include <climits>

using namespace std;

const int MAX_SIZE = 20000;

struct TreeNode {
	int weight;
	int parent;
	int left;
	int right;
};

TreeNode tree[MAX_SIZE];
int N;

int get_weight(int i) {
	if (tree[i].parent == 0) {
		return tree[i].weight;
	} else {
		return INT_MAX;
	}
}

void find_min(int start, int* out1, int* out2) {
	int min1 = INT_MAX;
	int min2 = INT_MAX;
	for (int i = start; i < 2 * N; ++i) {
		int w = get_weight(i);
		if (w < min1) {
			min2 = min1;
			*out2 = *out1;
			min1 = w;
			*out1 = i;
		} else if (w < min2) {
			min2 = w;
			*out2 = i;
		}
	}
}

unsigned long long sum = 0;

void get_sum(int i, int length) {
	if (tree[i].left == 0) {
		sum += tree[i].weight * length;
		return;
	}
	get_sum(tree[i].left, length + 1);
	get_sum(tree[i].right, length + 1);
}

int main() {
	cin >> N;
	for (int i = 0; i < 2 * N; ++i) {
		tree[i].parent = 0;
		tree[i].left = 0;
		tree[i].right = 0;
	}
	for (int i = 0; i < N; ++i) {
		int m;
		cin >> m;
		tree[N + i].weight = m;
	}
	for (int i = N - 1; i > 0; --i) {
		int min1, min2;
		find_min(i + 1, &min1, &min2);
		tree[i].weight = tree[min1].weight + tree[min2].weight;
		tree[i].left = min1;
		tree[i].right = min2;
		tree[min1].parent = i;
		tree[min2].parent = i;
	}
	get_sum(1, 0);
	cout << sum;
	return 0;
}
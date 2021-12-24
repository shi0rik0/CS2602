#include <iostream>

using namespace std;

const int MAX_LEN = 100005;

// 存储父节点，0表示没有父节点
int tree[MAX_LEN];
// 根节点的深度为1
int depth[MAX_LEN] = {0, 1};
// 要查找的节点
int node[MAX_LEN];

bool all_same(int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (node[i] != node[i+1]) {
            return false;
        }
    }
    return true;
}

void lca(int n) {
    int min = depth[node[0]];
    for (int i = 1; i < n; ++i) {
        if (depth[node[i]] < min) {
            min = depth[node[i]];
        }
    }
    for (int i = 0; i < n; ++i) {
        int d = depth[node[i]];
        for (int j = 0; j < d - min; ++j) {
            node[i] = tree[node[i]];
        }
    }
    while (!all_same(n)) {
        for (int i = 0; i < n; ++i) {
            node[i] = tree[node[i]];
        }
    }
    cout << node[0] << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 2; i <= n; ++i) {
        int parent;
        cin >> parent;
        tree[i] = parent;
        depth[i] = depth[parent] + 1;
    }
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int a;
            cin >> a;
            node[j] = a;
        }
        lca(k);
    }
    return 0;
}
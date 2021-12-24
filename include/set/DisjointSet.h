#pragma once

class DisjointSet final {
private:
    int size;
    int *parent;
public:
    DisjointSet(int size_) {
        size = size_;
        parent = new int[size];
        for (int i = 0; i < size; ++i) {
            parent[i] = -1;
        }
    }
    ~DisjointSet() {
        delete[] parent;
    }
    void merge(int x1, int x2) {
        auto r1 = find(x1);
        auto r2 = find(x2);
        if (r1 == r2) {
            return;
        }
        if (parent[r1] > parent[r2]) {
            parent[r2] += parent[r1];
            parent[r1] = r2;
        } else {
            parent[r1] += parent[r2];
            parent[r2] = r1;
        }
    }
    int find(int x) {
        if (parent[x] < 0) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }
};
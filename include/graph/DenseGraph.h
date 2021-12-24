#pragma once

#include "utils/Allocator.h"
#include <functional>

struct NullEdge {

};

template <typename Edge>
class DenseGraph final {
public:
    // [0, n)
    DenseGraph(int n) {
        size = n;
        conn = new bool*[n];
        for (int i = 0; i < n; ++i) {
            conn[i] = new bool[n];
            for (int j = 0; j < n; ++j) {
                conn[i][j] = false;
            }
        }
        visited = new bool[n];
        edges = new Edge*[n];
        for (int i = 0; i < n; ++i) {
            edges[i] = alloc::allocate<Edge>(n);
        }
    }
    ~DenseGraph() {
        delete[] visited;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (conn[i][j]) {
                    alloc::destruct(&edges[i][j]);
                }
            }
            delete[] conn[i];
        }
        delete[] conn;
        for (int i = 0; i < size; ++i) {
            alloc::deallocate(edges[i], size);
        }
        delete[] edges;
    }
    void add_edge(int from, int to, const Edge& edge) {
        if (conn[from][to]) {
            throw "Error!!!";
        }
        alloc::construct(&edges[from][to], edge);
        conn[from][to] = true;
    }
    void remove_edge(int from, int to) {
        if (!conn[from][to]) {
            throw "Error!!!";
        }
        alloc::destruct(&edges[from][to]);
        conn[from][to] = false;
    }
    Edge& edge(int from, int to) {
        if (!conn[from][to]) {
            throw "Error!!";
        }
        return edges[from][to];
    }
    // 注意：这个算法不是线程安全的
    void dfs(int start, const std::function<void(int)>& callback) {
        for (int i = 0; i < size; ++i) {
            visited[i] = false;
        }
        dfs_(start, 0, callback);
    }
private:
    void dfs_(int v, int layer, const std::function<void(int)>& callback) {
        callback(v);
        visited[v] = true;
        for (int i = 0; i < size; ++i) {
            if (!visited[i] && conn[v][i]) {
                dfs_(i, layer + 1, callback);
            }
        }
    }
    int size;
    bool** conn;
    Edge** edges;
    bool* visited;
};
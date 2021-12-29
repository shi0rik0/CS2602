#pragma once

#include "list/SeqList.h"
#include <tuple>
#include <climits>

template<typename Edge>
class SparseGraph final {
public:
    struct OutEdge {
        int to;
        Edge edge;
    };

    using OutEdgeIterator = typename SeqList<OutEdge>::iterator;
    // [0, n)
    explicit SparseGraph(int n) {
        n_vertices = n;
        for (int i = 0; i < n; ++i) {
            data.push(SeqList<OutEdge>());
            visited.push(false);
            distance.push(0);
            prev.push(0);
            known.push(false);
        }
    }

    int get_num_vertices() const {
        return n_vertices;
    }

    void add_edge(int from, int to, const Edge &edge) {
        OutEdge e;
        e.to = to;
        e.edge = edge;
        data[from].push(e);
    }

    OutEdgeIterator get_out_edge_begin_iterator(int v) {
        return data[v].begin();
    }
    OutEdgeIterator get_out_edge_end_iterator(int v) {
        return data[v].end();
    }
//    void remove_edge(int from, int to) {
//
//    }
//    Edge& edge(int from, int to) {
//        if (!conn[from][to]) {
//            throw "Error!!";
//        }
//        return edges[from][to];
//    }


    // 注意：这个算法不是线程安全的
    void dfs(int start, const std::function<void(int)> &callback) {
        for (int i = 0; i < data.get_length(); ++i) {
            visited[i] = false;
        }
        dfs_(start, callback);
    }

    void dijkstra(int start) {
        for (int i = 0; i < data.get_length(); ++i) {
            distance[i] = INT_MAX;
            known[i] = false;
            prev[i] = -1;
        }
        distance[start] = 0;
        for (int i = 1; i < data.get_length(); ++i) {
            int v = find_min();
            known[v] = true;
            auto &arr = data[v];
            for (int j = 0; j < arr.get_length(); ++j) {
                int u = arr[j].to;
                int weight = arr[j].edge;
                if (!known[u] && distance[v] + weight < distance[u]) {
                    distance[u] = distance[v] + weight;
                    prev[u] = v;
                }
            }
        }
    }

private:
    int find_min() {
        int m = INT_MAX;
        int v = -1;
        for (int i = 0; i < data.get_length(); ++i) {
            if (!known[i] && distance[i] <= m) {
                v = i;
                m = distance[i];
            }
        }
        return v;
    }

    void dfs_(int v, const std::function<void(int)> &callback) {
        callback(v);
        visited[v] = true;
        auto &arr = data[v];
        for (int j = 0; j < arr.get_length(); ++j) {
            auto next_v = std::get<0>(arr[j]);
            if (!visited[next_v]) {
                dfs_(next_v, callback);
            }
        }

    }

    SeqList<SeqList<OutEdge>> data;
    SeqList<bool> visited;

    SeqList<int> distance;
    SeqList<int> prev;
    SeqList<bool> known;

    int n_vertices;
};
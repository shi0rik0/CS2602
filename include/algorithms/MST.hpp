#include "set/DisjointSet.h"
#include "priority/BinaryHeap.h"
#include "graph/SparseGraph.h"
#include <cstdio>

namespace impl {
    template <typename T>
    struct Edge {
        int from;
        int to;
        T weight;
    };

    template <typename T>
    struct EdgeLess {
        bool operator()(const Edge<T>& lhs, const Edge<T>& rhs) const {
            return lhs.weight < rhs.weight;
        }
    };
}

template <typename T>
void kruskal(SparseGraph<T>& graph) {
    int n_vertices = graph.get_num_vertices();
    DisjointSet set(n_vertices);
    MinBinaryHeap<impl::Edge<T>, impl::EdgeLess<T>> heap;

    for (int i =0;i < n_vertices; ++i) {
        for (auto it=graph.get_out_edge_begin_iterator(i);it!=graph.get_out_edge_end_iterator(i); ++it) {
            if (i < it->to) {
                impl::Edge<T> e;
                e.from = i;
                e.to = it->to;
                e.weight = it->edge;
                heap.enqueue(e);
            }
        }
    }
    int edges_accepted =0;
    while (edges_accepted < n_vertices - 1) {
        auto edge = heap.front();
        heap.dequeue();
        if (set.find(edge.from) != set.find(edge.to)) {
            ++edges_accepted;
            set.merge(edge.from, edge.to);
            std::printf("(%d, %d)\n", edge.from + 1, edge.to + 1);
        }
    }
}
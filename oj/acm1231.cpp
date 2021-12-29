
#include <memory>
#include <tuple>
#include <functional>
#include <string>
#include <sstream>

template <typename T>
class SeqList final {
private:
    class Iterator {
    public:
        explicit Iterator(T* p_) : p(p_) {}
        Iterator& operator++() {
            ++p;
            return *this;
        }
        T& operator*() {
            return *p;
        }
        const T& operator*() const {
            return *p;
        }
        T* operator->() {
            return p;
        }
        const T* operator->() const {
            return p;
        }
        bool operator!=(Iterator rhs) const {
            return p != rhs.p;
        }
    private:
        T* p;
    };
public:
    using iterator = Iterator;
    SeqList() : max_len(64) {
        data = alloc.allocate(max_len);
    }
    ~SeqList() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, max_len);
    }
    SeqList(const SeqList& other) {
        data = alloc.allocate(other.max_len);
        for (int i = 0; i < other.len; ++i) {
            alloc.construct(data + i, other.data[i]);
        }
        len = other.len;
        max_len = other.max_len;
    }
    SeqList& operator=(const SeqList<T>& other) {
        if (this == &other) {
            return *this;
        }
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, max_len);
        data = alloc.allocate(other.max_len);
        for (int i = 0; i < other.len; ++i) {
            alloc.construct(data + i, other.data[i]);
        }
        len = other.len;
        max_len = other.max_len;
        return *this;
    }
    void reserve(int capacity) {
        while (max_len < capacity) {
            double_space();
        }
    }
    int get_length() const {
        return len;
    }
    T& operator[](int i) {
        return data[i];
    }
    const T& operator[](int i) const {
        auto& r = *const_cast<SeqList*>(this);
        return r[i];
    }
    SeqList operator+(const SeqList& rhs) const {
        int new_len = len + rhs.len;
        SeqList r(new_len * 2);
        int i;
        for (i = 0; i < len; ++i) {
            r.alloc.construct(r.data + i, data[i]);
        }
        for (int j = 0; j < rhs.len; ++j) {
            r.alloc.construct(r.data + i + j, rhs.data[j]);
        }
        return r;
    }
    template <typename U>
    void splice(int i, int dn, const U& start, const U& end) {
        int in = end - start;
        int new_len = len - dn + in;
        while (max_len < new_len) {
            double_space();
        }
        if (dn < in) {
            for (int j = len - 1; j >= len - in + dn; --j) {
                alloc.construct(data + j + in - dn, data[j]);
            }
            for (int j = len - in + dn - 1; j >= i + dn; --j) {
                data[j + in - dn] = data[j];
            }
        } else {
            for (int j = i + dn; j < len; ++j) {
                data[j + in - dn] = data[j];
            }
            for (int j = new_len; j < len; ++j) {
                alloc.destroy(data + j);
            }
        }
        for (int j = 0; j < in; ++j) {
            data[i + j] = start[j];
        }
        len = new_len;
    }
    void insert(int i, const T& e) {
        if (len == max_len) {
            double_space();
        }
        alloc.construct(data + len, data[len - 1]);
        for (int j = len - 2; j >= i; --j) {
            data[j + 1] = data[j];
        }
        data[i] = e;
        ++len;
    }
    void remove(int i) {
        for (int j = i + 1; j < len; ++j) {
            data[j - 1] = data[j];
        }
        alloc.destroy(data + len - 1);
        --len;
    }
    T &end_ref() {
        return data[len - 1];
    }
    const T&end_ref() const {
        auto& r = *const_cast<SeqList*>(this);
        return r.end_ref();
    }
    void push(const T& e) {
        if (len == max_len) {
            double_space();
        }
        alloc.construct(data + len, e);
        ++len;
    }
    void pop() {
        alloc.destroy(data + len - 1);
        --len;
    }
    void clear() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        len = 0;
    }
    std::tuple<T*, int> find(const std::function<bool(const T&)>& func, int start=0) {
        for (int i = start; i < len; ++i) {
            if (func(data[i])) {
                return std::make_tuple(data + i, i);
            }
        }
        return std::make_tuple(nullptr, -1);
    }
    std::tuple<const T*, int> find(const std::function<bool(const T&)>& func, int start=0) const {
        auto& r = *const_cast<SeqList*>(this);
        return r.find(func, start);
    }
    std::string to_string() const {
        std::ostringstream oss;
        auto sep = "{";
        for (int i = 0; i < len; ++i) {
            oss << sep << data[i];
            sep = ", ";
        }
        oss << "}";
        return oss.str();
    }
    Iterator begin() {
        return Iterator(data);
    }
    Iterator end() {
        return Iterator(data + len);
    }
private:


    T* data = nullptr;
    int len = 0;
    int max_len = 0;
    std::allocator<T> alloc;

    void double_space() {
        max_len *= 2;
        T* new_data = alloc.allocate(max_len);
        for (int i = 0; i < len; ++i) {
            alloc.construct(new_data + i, data[i]);
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, len);
        data = new_data;
    }
};

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


#include <functional>

template <typename T, typename Less=std::less<T>>
class MinBinaryHeap {
public:
    MinBinaryHeap() {
        data.push(T());
    }
    template <typename It>
    void build_heap(const It& start, const It& end) {
        data.clear();
        data.push(T());
        data.splice(1, 0, start, end);
        length = end - start;
        for (int i = length / 2; i > 0; --i) {
            percolate_down(i);
        }
    }
    bool is_empty() const {
        return length == 0;
    }
    void enqueue(const T& x) {
        int i;
        data.push(T());
        for (i = length + 1; i > 1 && Less()(x, data[i / 2]); i /= 2) {
            data[i] = data[i / 2];
        }
        data[i] = x;
        ++length;
    }
    void dequeue() {
        data[1] = data[length];
        data.pop();
        percolate_down(1);
        --length;
    }
    const T& front() {
        return data[1];
    }
private:
    int length = 0;
    SeqList<T> data;

    void percolate_down(int hole) {
        int child;
        T tmp = data[hole];

        for (; hole * 2 <= length; hole = child) {
            child = hole * 2;
            if (child != length && Less()(data[child + 1], data[child])) {
                ++child;
            }
            if (Less()(data[child], tmp)) {
                data[hole] = data[child];
            } else {
                break;
            }
        }
        data[hole] = tmp;
    }
};

template <typename Less, typename T>
struct reverse {
    constexpr bool operator()(const T& x1, const T& x2) const {
        return Less()(x2, x1);
    }
};

template <typename T, typename Less=std::less<T>>
using MaxBinaryHeap = MinBinaryHeap<T, reverse<Less, T>>;


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

long long s = 0;

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
            s += edge.weight;
        }
    }
}
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    SparseGraph<int> g(n);
    for (int i =0;i <m;++i) {
        int x,y,z;
        cin>>x>>y>>z;
        g.add_edge(x-1,y-1,z);
        g.add_edge(y-1,x-1,z);
    }
    kruskal(g);
    cout << s;
    return 0;
}
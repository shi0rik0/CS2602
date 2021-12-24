#include <functional>
#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

namespace alloc {
    template<typename T>
    T *allocate(int size) {
        std::allocator<T> alloc;
        using traits_t = std::allocator_traits<decltype(alloc)>;
        T *p = traits_t::allocate(alloc, size);
        return p;
    }

    template<typename T>
    void deallocate(T *p, int size) {
        std::allocator<T> alloc;
        using traits_t = std::allocator_traits<decltype(alloc)>;
        traits_t::deallocate(alloc, p, 1);
    }

    template<typename T, typename... Args>
    void construct(T *p, Args... args) {
        std::allocator<T> alloc;
        using traits_t = std::allocator_traits<decltype(alloc)>;
        traits_t::construct(alloc, p, args...);
    }

    template<typename T>
    void destruct(T *p) {
        std::allocator<T> alloc;
        using traits_t = std::allocator_traits<decltype(alloc)>;
        traits_t::destroy(alloc, p);
    }
}

struct NullEdge {

};

template <typename Edge>
class DenseGraph final {
public:
    // [0, n)
    explicit DenseGraph(int n) {
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
    int dfs(int start) {
        for (int i = 0; i < size; ++i) {
            visited[i] = false;
        }
        dfs_(start, 0);
        int c = 0;
        for (int i = 0; i < size; ++i) {
            if (visited[i]) {
                ++c;
            }
        }
        return c;
    }
private:
    void dfs_(int v, int layer) {
        if (layer == 7) {
            return;
        }
        visited[v] = true;
        for (int i = 0; i < size; ++i) {
            if (conn[v][i]) {
                dfs_(i, layer + 1);
            }
        }
    }
    int size;
    bool** conn;
    Edge** edges;
    bool* visited;
};

int main() {
    int N, M;
    cin >> N >> M;
    DenseGraph<NullEdge> g(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g.add_edge(a, b, NullEdge());
        g.add_edge(b, a, NullEdge());
    }
    for (int i = 0; i < N; ++i) {
        int n = g.dfs(i);
        auto ans = (double)n / N * 100;
        cout << i+1 << ": " << setiosflags(ios::fixed) << setprecision(2) << ans << '%' <<endl;
    }
    return 0;
}
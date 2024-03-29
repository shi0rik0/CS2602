
#include <memory>
#include <tuple>
#include <functional>
#include <string>
#include <sstream>

template<typename T>
class SeqList final {
public:
    SeqList() : max_len(64) {
        data = alloc.allocate(max_len);
    }

    ~SeqList() {
        for (int i = 0; i < len; ++i) {
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, max_len);
    }

    SeqList(const SeqList &other) {
        data = alloc.allocate(other.max_len);
        for (int i = 0; i < other.len; ++i) {
            alloc.construct(data + i, other.data[i]);
        }
        len = other.len;
        max_len = other.max_len;
    }

    SeqList &operator=(const SeqList<T> &other) {
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

    T &operator[](int i) {
        return data[i];
    }

    const T &operator[](int i) const {
        auto &r = *const_cast<SeqList *>(this);
        return r[i];
    }

    SeqList operator+(const SeqList &rhs) const {
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

    template<typename U>
    void splice(int i, int dn, const U &start, const U &end) {
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

    void insert(int i, const T &e) {
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

    const T &end_ref() const {
        auto &r = *const_cast<SeqList *>(this);
        return r.end_ref();
    }

    void push(const T &e) {
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

    std::tuple<T *, int> find(const std::function<bool(const T &)> &func, int start = 0) {
        for (int i = start; i < len; ++i) {
            if (func(data[i])) {
                return std::make_tuple(data + i, i);
            }
        }
        return std::make_tuple(nullptr, -1);
    }

    std::tuple<const T *, int> find(const std::function<bool(const T &)> &func, int start = 0) const {
        auto &r = *const_cast<SeqList *>(this);
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

private:
    T *data = nullptr;
    int len = 0;
    int max_len = 0;
    std::allocator<T> alloc;

    void double_space() {
        max_len *= 2;
        T *new_data = alloc.allocate(max_len);
        for (int i = 0; i < len; ++i) {
            alloc.construct(new_data + i, data[i]);
            alloc.destroy(data + i);
        }
        alloc.deallocate(data, len);
        data = new_data;
    }
};

#include <tuple>
#include <climits>

int v_end;
int min_dis = INT32_MAX;

template<typename Edge>
class SparseGraph final {
public:
    // [0, n)
    explicit SparseGraph(int n) {
        for (int i = 0; i < n; ++i) {
            data.push(SeqList<std::tuple<int, Edge>>());
            visited.push(false);
            distance.push(0);
            prev.push(0);
            known.push(false);
        }
    }

    void add_edge(int from, int to, const Edge &edge) {
        data[from].push(std::make_tuple(to, edge));
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
    void dfs(int start) {
        for (int i = 0; i < data.get_length(); ++i) {
            visited[i] = false;
        }
        dfs_(start, 0);
    }

private:
    void dfs_(int v, int dis) {
        if (v == v_end) {
            if (dis < min_dis) {
                min_dis = dis;
            }
            return;
        }
        visited[v] = true;
        auto &arr = data[v];
        for (int j = 0; j < arr.get_length(); ++j) {
            auto next_v = std::get<0>(arr[j]);
            auto w = std::get<1>(arr[j]);
            if (!visited[next_v]) {
                dfs_(next_v, dis + w);
            }
        }
        visited[v] = false;
    }

    SeqList<SeqList<std::tuple<int, Edge>>> data;
    SeqList<bool> visited;

    SeqList<int> distance;
    SeqList<int> prev;
    SeqList<bool> known;
};

#include <iostream>

using namespace std;

int main() {
    int n, m, v_start;
    cin >> n >> m >> v_start >> v_end;
    --v_end;
    SparseGraph<int> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, p;
        cin >> a >> b >> p;
        g.add_edge(a - 1, b - 1, p);
    }
    g.dfs(v_start - 1);
    cout << min_dis;
    return 0;
}
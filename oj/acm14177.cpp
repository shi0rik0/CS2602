// 这段代码不是我写的


#include <iostream>
#include <cmath>
#include <climits>

template<class elemType>
class List {
public:
    virtual inline int len() const = 0;

    virtual int find(const elemType &x) const = 0;

    virtual inline elemType get(int i) const = 0;

    virtual void insert(int, const elemType &x) = 0;

    virtual void remove(int i) = 0;

    virtual inline void clear() = 0;

    virtual void traverse(int start = 0, int end = -1) const = 0;

    virtual ~List() = default;
};

template<class elemType>
class linkedList : public List<elemType> {
private:
    int length;

    class node {
    public:
        elemType data;
        node *next;

        explicit node() : next(nullptr) {}

        node(elemType D, node *N) : data(D), next(N) {}

        //~node(){ delete next; }
        node(const node &another) : data(another.data), next(another.next) {}
    };

    node *head;
public:
    linkedList();

    ~linkedList();

    inline int len() const;

    int find(const elemType &x) const;

    inline elemType get(int) const;

    void insert(int, const elemType &x);

    void remove(int);

    inline void clear();

    void traverse(int st = -1, int ed = -1) const; // st and ed does nothing

};


template<class elemType>
linkedList<elemType>::linkedList() {
    head = new node();
    length = 0;
}

template<class elemType>
linkedList<elemType>::~linkedList() {
    this->clear();
    delete head;
}

template<class elemType>
inline void linkedList<elemType>::clear() {
    node *tmp;
    length = 0;
    while (head->next != nullptr) {
        tmp = head->next;
        head->next = tmp->next;
        delete tmp;
    }

}

template<class elemType>
inline int linkedList<elemType>::len() const {
    return length;

}

template<class elemType>
int linkedList<elemType>::find(const elemType &x) const {
    int cnt = 0;
    node *p = head;
    while (p->next) {
        p = p->next;
        if (p->data == x) {
            return cnt;
        }
        cnt++;
    }
    return -1;
}

template<class elemType>
inline elemType linkedList<elemType>::get(int pos) const {

    node *p = head->next;
    while (pos--) {
        p = p->next;
    }
    return p->data;

}

template<class elemType>
void linkedList<elemType>::insert(int pos, const elemType &x) {
    node *p = head;
    while (pos--) {
        p = p->next;
    }
    p->next = new node(x, p->next);
    length++;

}

template<class elemType>
void linkedList<elemType>::remove(int pos) {
    node *p = head;
    while (pos--) {
        p = p->next;
    }
    node *tmp = p->next;
    p->next = tmp->next;
    delete tmp;
    length--;

}


template<class elemType>
void linkedList<elemType>::traverse(int st, int ed) const {

    node *p = head->next;

    while (p) {
        std::cout << (p->data) << ' ';
        p = p->next;
    }
    std::cout << std::endl;
}


template<class T>
struct Edge {
    int v;
    T weight;
    Edge *next;

    Edge() : v(-1), next(nullptr) {}

    Edge(int v_, T weight_, Edge *next_ = nullptr) : v(v_), weight(weight_), next(next_) {}

};

template<class T>
class AdjGraph {
public:
    int V, E;
    Edge<T> **edges;

    explicit AdjGraph(int MaxN) : V(0), E(0) {
        edges = new Edge<T> *[MaxN];
        for (int i = 0; i < MaxN; ++i) {
            edges[i] = nullptr;
        }
    }

    void addEdge(int from, int to, T weight);

    T getWeight(int from, int to);
};

template<class T>
void AdjGraph<T>::addEdge(int from, int to, T weight) {
    auto *newEdge = new Edge<T>(to, weight, edges[from]);

    edges[from] = newEdge;
    E++;
}

template<class T>
T AdjGraph<T>::getWeight(int from, int to) {
    auto cur = edges[from];
    while (cur) {
        if (cur->v == to) {
            return cur->weight;
        }
        cur = cur->next;
    }
    return T(-1);
}


template<class T>
void dijkstra(int st, int n, T *dis, const AdjGraph<T> &g) {

    bool *vis = new bool[n + 1];
    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
        dis[i] = INT64_MAX;
    }

    dis[st] = 0;
    for (int k = 1; k <= n; ++k) {
        int closest = 1;
        T minDis = INT64_MAX;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && dis[i] < minDis) {
                minDis = dis[i];
                closest = i;
            }
        }
        vis[closest] = true;
        for (Edge<T> *e = g.edges[closest]; e; e = e->next) {
            if (minDis < INT64_MAX && e->weight < INT64_MAX && !vis[e->v] && minDis + e->weight < dis[e->v]) {
                dis[e->v] = minDis + e->weight;
            }
        }
    }
}

typedef long long int LL;
const LL MOD = 998244353;

void dijkstra_mod(int st, int n, LL *dis, const AdjGraph<LL> &G) {

    auto *logdis = new double[n + 10];
    bool *vis = new bool[n + 1];
    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
        dis[i] = INT64_MAX;
        logdis[i] = INT64_MAX;
    }


    dis[st] = 1;
    logdis[st] = 0;

    for (int k = 1; k <= n; ++k) {
        int closest = 1;
        double logMinDis = INT64_MAX;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && logdis[i] < logMinDis) {
                logMinDis = logdis[i];
                closest = i;
            }
        }
        vis[closest] = true;
        // update all edges going out of 'closest'
        for (Edge<LL> *e = G.edges[closest]; e; e = e->next) {
            if (logMinDis < INT64_MAX && e->weight < INT64_MAX && !vis[e->v] && logMinDis + log(e->weight) < logdis[e->v]) {
                logdis[e->v] = logMinDis + log(e->weight);
                dis[e->v] = (dis[closest] * e->weight) % MOD;
            }
        }
    }
    delete[] logdis;
}

using namespace std;
const int MAXN = 5e4 + 10;

int main() {
    int n, m;
    cin >> n >> m;

    int from, to;
    LL weight;
    AdjGraph<LL> G(MAXN);
    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> weight;
        G.addEdge(from, to, weight);
        G.addEdge(to, from, weight);
    }


    LL *dis = new LL[n + 10];
    dijkstra_mod(1, n, dis, G);
    cout << dis[n] << endl;
    delete[] dis;
}


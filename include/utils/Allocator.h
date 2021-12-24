#include <memory>

// 不知道为什么标准库的allocator这么难用，所以我封装了一下

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
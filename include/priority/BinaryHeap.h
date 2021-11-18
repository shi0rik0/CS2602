#pragma once

#include "list/SeqList.h"

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
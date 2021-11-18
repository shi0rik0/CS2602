#include "priority/BinaryHeap.h"

#include <iostream>

using namespace std;

int main() {
    MaxBinaryHeap<int> heap;
    int arr[] = {1,2,3,4,8,7,6,5};
    for (int i = 0; i < 0; ++i) {
        heap.enqueue(i);
    }
    heap.build_heap(arr+0, arr+8);
    while (!heap.is_empty()) {
        cout << heap.front() << endl;
        heap.dequeue();
    }
	return 0;
}
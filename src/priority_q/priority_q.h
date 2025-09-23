#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H
#include <stdexcept>

template<typename E>
class Node {
    public:
    E data;
    int priority{};

    // ==Constructor==
    Node() = default;
    Node(const E& d, const int p) : data(d), priority(p) {}
    // ==Destructor==
    ~Node() = default;
};

template<typename E>
class PriorityQueue {
    private:
    size_t capacity;
    size_t size;
    Node<E>* heap;

    // == Utils methods ==
    /*
     * We use binary heap there
     * to optimize push algorithm
     */
    void up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) >> 2;
            if (heap[index].priority > heap[parent].priority) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void down(size_t index) {
        while (true) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t largest = index;

            if (left < size && heap[left].priority > heap[largest].priority) {
                largest = left;
            }
            if (right < size && heap[right].priority > heap[largest].priority) {
                largest = right;
            }
            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

    void resize(const size_t newCap) {
        auto* newHeap = new Node<E>[newCap];
        for (size_t i = 0; i < size; i++) {
            newHeap[i].data = std::move(heap[i].data);
            newHeap[i].priority = std::move(heap[i].priority);
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCap;

    }

    public:
    // ==Constructor==
    explicit PriorityQueue(const size_t cap)
        : capacity(cap),
        size(0),
        heap(new Node<E>[cap]) {}
    // ==Destructor==
    ~PriorityQueue() {
        delete[] heap;
    }

    // ==Prohibit assignment==
    PriorityQueue& operator=(const PriorityQueue&) = delete;
    PriorityQueue(const PriorityQueue&) = delete;

    // ==Prohibit movement==
    PriorityQueue(PriorityQueue&&) = delete;
    PriorityQueue& operator=(PriorityQueue&&) = delete;

    // ==Basic operations==
    [[nodiscard]] bool is_empty() const { return size == 0; }

    [[nodiscard]] bool is_full() const { return size == capacity; }

    [[nodiscard]] size_t get_size() const { return size; }

    [[nodiscard]] size_t get_capacity() const { return capacity; }

    [[maybe_unused]] const E& top() const {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");
        return heap[0].data;
    }

    [[nodiscard]] int top_priority() const {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");
        return heap[0].priority;
    }

    void push(E&& value, int priority) {
        if (is_full()) resize(2 * capacity);
        heap[size] = Node<E>(std::move(value), priority);
        up(size);
        ++size;
    }

    E pop() {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");

        E res = std::move(heap[0].data);

        if (size > 1) {
            heap[0] = std::move(heap[size - 1]);
            --size;
            down(0);
        } else {
            size = 0;
        }

        if (size < capacity / 4 && capacity > 10) resize(std::max(static_cast<size_t>(10), capacity / 2));

        return res;
    }
};

#endif
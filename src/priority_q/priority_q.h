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
    const size_t capacity;
    size_t size;
    Node<E>** heap;

    // == Utils methods ==
    void up(size_t index) {
        while (index > 0) {
            if (heap[index]->priority > heap[index - 1]->priority) {
                std::swap(heap[index], heap[index - 1]);
                --index;
            } else break;
        }
    }

    void down(size_t index) {
        while (index < size) {
            if (heap[index]->priority < heap[index + 1]->priority) {
                std::swap(heap[index], heap[index + 1]);
                index = index + 1;
            } else break;
        }
    }

    public:
    // ==Constructor==
    explicit PriorityQueue(const size_t cap)
        : capacity(cap),
        size(0),
        heap(new Node<E> *[cap]) {
            for (size_t i = 0; i < cap; i++) {
                heap[i] = nullptr;
            }
    }
    // ==Destructor==
    ~PriorityQueue() {
        for (size_t i = 0; i < size; i++) {
            delete heap[i];
        }
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

    [[nodiscard]] const E& top() const {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");
        return heap[0]->data;
    }

    [[nodiscard]] int top_priority() const {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");
        return heap[0]->priority;
    }

    void push(const E& value, int priority) {
        if (is_full()) throw std::out_of_range("Priority queue is full");

        heap[size] = new Node<E>(value, priority);
        up(size);
        ++size;
    }

    E pop() {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");

        E res = std::move(heap[0]->data);
        delete heap[0];

        if (size > 1) {
            heap[0] = std::move(heap[size - 1]);
            --size;
            down(0);
        } else {
            heap[0] = nullptr;
            size = 0;
        }

        return res;
    }
};

#endif
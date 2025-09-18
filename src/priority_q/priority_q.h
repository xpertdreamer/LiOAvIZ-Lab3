#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H
#include <memory>

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
    std::unique_ptr<std::unique_ptr<Node<E>>[]> heap;

    public:
    // ==Constructor==
    explicit PriorityQueue(const size_t cap)
        : capacity(cap),
        size(0),
        heap(std::make_unique<std::unique_ptr<Node<E>>[]>(cap)) {}
    // ==Destructor==
    ~PriorityQueue() = default;

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

    // note: add heapify
    void push(const E& value, int priority) {
        if (is_full()) throw std::out_of_range("Priority queue is full");
        heap[size] = std::make_unique<Node<E>>(value, priority);
        size++;
    }
};

#endif
//
// Created by IWOFLEUR on 20.09.2025.
//

#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

template<typename E>
class Queue {
    private:
    size_t capacity;
    size_t size;
    /*
     * Save rear and front elements
     * of queue array to properly
     * push and pop
     */
    size_t rear;
    size_t front;

    E* heap;

    void resize(const size_t newCapacity) {
        auto* newHeap = new E[newCapacity];
        for (size_t i = 0; i < rear; i++) {
            newHeap[i] = std::move(heap[i]);
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    public:
    // Constructor
    explicit Queue(const size_t cap)
        : capacity(cap),
        size(0),
        rear(0),
        front(0),
        heap(new E[capacity]) {}
    // Destructor
    ~Queue() {
        delete[] heap;
    }
    // Prohibit assignment and movement
    Queue& operator=(const Queue&) = delete;
    Queue(const Queue&) = delete;
    Queue& operator=(Queue&&) = delete;
    Queue(Queue&&) = delete;

    // == Basic operations ==
    [[nodiscard]] bool is_empty() const { return size == 0; }

    [[nodiscard]] bool is_full() const { return size == capacity; }

    [[nodiscard]] size_t get_size() const { return size; }

    [[nodiscard]] size_t get_capacity() const { return capacity; }

    [[maybe_unused]] const E& peek_back() const {
        if (is_empty()) throw std::out_of_range("Queue is empty");
        return heap[rear - 1];
    }

    [[maybe_unused]] const E& peek_front() const {
        if (is_empty()) throw std::out_of_range("Queue is empty");
        return heap[front];
    }

    void push(E&& e) {
        if (is_full()) resize(2 * capacity);
        heap[rear] = std::move(e);
        rear = (rear + 1) % capacity;
        ++size;
    }

    void push(const E& e) {
        if (is_full()) resize(2 * capacity);
        heap[rear] = e;
        rear = (rear + 1) % capacity;
        ++size;
    }

    [[maybe_unused]] E pop() {
        if (is_empty()) throw std::out_of_range("Queue is empty");

        E res = std::move(heap[front]);
        front = (front + 1) % capacity;
        --size;

        if (size < capacity / 4 && capacity > 10) resize(std::max(static_cast<size_t>(10), capacity / 2));

        return res;
    }
};

#endif //QUEUE_H

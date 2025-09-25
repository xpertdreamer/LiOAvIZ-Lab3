//
// Created by IWOFLEUR on 20.09.2025.
//

#ifndef STACK_H
#define STACK_H
#include <stdexcept>

/*
 * Without STL objects may
 * remain in memory when we copy them
 */

template<typename E>
class Stack {
    private:
    size_t capacity;  // Max size of our stack
    size_t size;
    E* heap;

    void resize(const size_t newCapacity) {
        auto newHeap = new E[newCapacity];
        for (size_t i = 0; i < size; i++) {
            newHeap[i] = heap[i];
            heap[i] = E();
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    public:
    // Constructor
    explicit Stack(const size_t cap) : capacity(cap), size(0), heap(new E[cap]) {}
    // Destructor
    ~Stack() {
        delete[] heap;
    }
    // Prohibit assignment and movement
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack& operator=(Stack&&) = delete;

    // === Basic operations ===
    // True if stack is empty
    [[nodiscard]] bool is_empty() const { return size == 0; }
    // True if stack is full
    [[nodiscard]] bool is_full() const { return size == capacity; }

    [[nodiscard]] size_t get_size() const { return size; }

    [[nodiscard]] size_t get_capacity() const { return capacity; }
    // Copy existing object
    void push(const E& e) {
        if (is_full()) resize(2 * capacity);
        heap[size++] = e;
    }
    // Move object or move temporary
    void push(E&& e) {
        if (is_full()) resize(2 * capacity);
        heap[size++] = e;
        e = E();
    }

    [[maybe_unused]] E pop() {
        if (is_empty()) throw std::out_of_range("Stack is empty");
        E result = heap[size - 1];
        heap[size - 1] = E();
        size--;

        if (size < capacity / 4 && capacity > 10) resize(std::max(static_cast<size_t>(10), capacity / 2));

        return result;
    }

    [[maybe_unused]] const E& peek() const {
        if (is_empty()) throw std::out_of_range("Stack is empty");
        return heap[size - 1];
    }
};

#endif //STACK_H

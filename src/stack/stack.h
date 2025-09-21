//
// Created by IWOFLEUR on 20.09.2025.
//

#ifndef STACK_H
#define STACK_H
#include <stdexcept>

template<typename E>
class Stack {
    private:
    size_t capacity;  // Max size of our stack
    size_t size;
    size_t top;     // Top of the stack
    E* heap;

    void resize(size_t newCapacity) {
        E* newHeap = new E[newCapacity];
        for (size_t i = 0; i < top; i++) {
            newHeap[i] = std::move(heap[i]);
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    public:
    // Constructor
    explicit Stack(const size_t cap) : capacity(cap), size(0), top(-1), heap(new E[cap]) {}
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
    [[nodiscard]] bool is_empty() const { return top == -1; }
    // True if stack is full
    [[nodiscard]] bool is_full() const { return top == capacity - 1; }

    [[nodiscard]] size_t get_size() const { return size; }

    [[nodiscard]] size_t get_capacity() const { return capacity; }
    // Copy existing object
    void push(const E& e) {
        if (is_full()) resize(2 * capacity);
        heap[++top] = e;
        ++size;
    }
    // Move object or move temporary
    void push(E&& e) {
        if (is_full()) resize(2 * capacity);
        heap[++top] = std::move(e);
        ++size;
    }

    [[maybe_unused]] E pop() {
        if (is_empty()) throw std::out_of_range("Stack is empty");

        if (size < capacity / 4 && capacity > 10) resize(capacity / 2);

        --size;
        return std::move(heap[top--]);
    }

    [[maybe_unused]] E peek() const {
        if (is_empty()) throw std::out_of_range("Stack is empty");
        return heap[top];
    }
};

#endif //STACK_H

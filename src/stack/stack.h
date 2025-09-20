//
// Created by IWOFLEUR on 20.09.2025.
//

#ifndef STACK_H
#define STACK_H

template<typename E>
class Stack {
    private:
    const size_t capacity;
    size_t size;
    size_t top;
    E* heap;

    public:
    // Constructor
    explicit Stack(const size_t cap) : capacity(cap), size(0), top(0), heap(new E[cap]) {}
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

};

#endif //STACK_H

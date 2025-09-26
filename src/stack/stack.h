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
    struct Node {
        E data;
        Node* next;

        explicit Node(const E& d) : data(d), next(nullptr) {}
        explicit Node(E&& d) : data(static_cast<E&&>(d)), next(nullptr) {}
        ~Node() = default;
    };

    size_t size;
    Node* head;

    public:
    // Constructor
    explicit Stack() : size(0), head(nullptr) {}
    // Destructor
    ~Stack() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }
    // Prohibit assignment and movement
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack& operator=(Stack&&) = delete;

    // === Basic operations ===
    // True if stack is empty
    [[nodiscard]] bool is_empty() const { return size == 0; }

    [[nodiscard]] size_t get_size() const { return size; }

    // Copy existing object
    void push(const E& e) {
        Node* newNode = new Node(e);
        newNode->next = head;
        head = newNode;
        size++;
    }
    // Move object or move temporary
    void push(E&& e) {
        Node* newNode = new Node(static_cast<E&&>(e));
        newNode->next = head;
        head = newNode;
        size++;
    }

    [[maybe_unused]] E pop() {
        if (is_empty()) throw std::out_of_range("Stack is empty");
        Node* temp = head;
        E result = static_cast<E&&>(temp->data);
        head = head->next;
        delete temp;
        size--;

        return result;
    }

    [[maybe_unused]] const E& peek() const {
        if (is_empty()) throw std::out_of_range("Stack is empty");
        return head->data;
    }
};

#endif //STACK_H

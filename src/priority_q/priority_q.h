#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H
#include <stdexcept>

template<typename E>
class Node {
    public:
    E data;
    int priority{};
    Node* next;

    // ==Constructor==
    Node() = default;
    Node(const E& d, const int p) : data(d), priority(p), next(nullptr) {}
    Node(E&& d, const int p) : data(static_cast<E&&>(d)), priority(p), next(nullptr) {}
    // ==Destructor==
    ~Node() = default;
};

template<typename E>
class PriorityQueue {
    private:
    size_t size;
    Node<E>* head;

    // == Utils methods ==
    void insert_sorted(Node<E>* newNode) {
        if (!head || newNode->priority > head->priority) {
            newNode->next = head;
            head = newNode;
        } else {
            auto curr = head;
            while (curr->next && curr->next->priority >= newNode->priority)
                curr = curr->next;
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }

    void clear() {
        while (head) {
            auto temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    public:
    // ==Constructor==
    explicit PriorityQueue() : size(0), head(nullptr) {}
    // ==Destructor==
    ~PriorityQueue() {
        clear();
    }

    // ==Prohibit assignment==
    PriorityQueue& operator=(const PriorityQueue&) = delete;
    PriorityQueue(const PriorityQueue&) = delete;
    // ==Prohibit movement==
    PriorityQueue(PriorityQueue&&) = delete;
    PriorityQueue& operator=(PriorityQueue&&) = delete;

    // ==Basic operations==
    [[nodiscard]] bool is_empty() const { return size == 0; }

    [[nodiscard]] size_t get_size() const { return size; }


    [[maybe_unused]] const E& top() const {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");
        return head->data;
    }

    [[nodiscard]] int top_priority() const {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");
        return head->priority;
    }

    void push(E&& value, int priority) {
        auto newNode = new Node<E>(static_cast<E&&>(value), priority);
        insert_sorted(newNode);
        ++size;
    }

    void push(const E& value, int priority) {
        auto newNode = new Node<E>(value, priority);
        insert_sorted(newNode);
        ++size;
    }

    E pop() {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");

        auto temp = head;
        E res = static_cast<E&&>(temp->data);

        head = head->next;
        delete temp;
        --size;

        return res;
    }

    E find_by_priority(const int& prior) const {
        auto curr = head;
        while (curr) {
            if (curr->priority == prior) return curr->data;
            curr = curr->next;
        }
        throw std::out_of_range("Element with specified priority not found");
    }

    [[nodiscard]] bool contains_by_priority(const int prior) const {
        auto curr = head;
        while (curr) {
            if (curr->priority == prior) return true;
            curr = curr->next;
        }
        return false;
    }

    int find_by_value(const E& value) const {
        auto curr = head;
        while (curr) {
            if (curr->data == value) return curr->priority;
            curr = curr->next;
        }
        return -1;
    }

    void peek_pq() const {
        if (is_empty()) throw std::out_of_range("Priority queue is empty");
        for (auto curr = head; curr != nullptr; curr = curr->next) {
            std::cout << curr->data << "(" << curr->priority << ") ";
        }
    }
};

#endif
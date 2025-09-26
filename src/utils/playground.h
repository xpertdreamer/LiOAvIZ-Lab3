//
// Created by oblepixa on 9/25/25.
//

#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include <iostream>
#include <sstream>
#include <memory>

#include "priority_q/priority_q.h"
#include "queue/queue.h"
#include "stack/stack.h"

using namespace std;

namespace Playground {
    enum class ContainerType {
        STACK,
        QUEUE,
        PRIORITY_QUEUE
    };

    template<typename E>
    class ContainerWrapper {
    private:
        unique_ptr<Stack<E>> stack_;
        unique_ptr<Queue<E>> queue_;
        unique_ptr<PriorityQueue<E>> priority_queue_;
        ContainerType type_{};

    public:
        explicit ContainerWrapper(const ContainerType type, const size_t capacity=10) : type_(type) {
            switch (type) {
                case ContainerType::STACK:
                    stack_ = make_unique<Stack<E>>();
                    break;
                case ContainerType::QUEUE:
                    queue_ = make_unique<Queue<E>>(capacity);
                    break;
                case ContainerType::PRIORITY_QUEUE:
                    priority_queue_ = make_unique<PriorityQueue<E>>();
                    break;
            }
        }

        [[nodiscard]] ContainerType get_type() const { return type_; }

        [[nodiscard]] const char* get_type_name() const{
            switch (type_) {
                case ContainerType::STACK: return "stack";
                case ContainerType::QUEUE: return "queue";
                case ContainerType::PRIORITY_QUEUE: return "priority_queue";
                default: return "unknown";
            }
        }

        void push(const E& e, int prior=1) {
            switch (type_) {
                case ContainerType::STACK: stack_->push(e); break;
                case ContainerType::QUEUE: queue_->push(e); break;
                case ContainerType::PRIORITY_QUEUE: priority_queue_->push(e, prior); break;
            }
        }

        E pop() {
            switch (type_) {
                case ContainerType::STACK: return stack_->pop();
                case ContainerType::QUEUE: return queue_->pop();
                case ContainerType::PRIORITY_QUEUE: return priority_queue_->pop();
            }
            throw runtime_error("Invalid container type");
        }

        E& head() {
            switch (type_) {
                case ContainerType::STACK: return stack_->peek();
                case ContainerType::QUEUE: return queue_->peek_head();
                case ContainerType::PRIORITY_QUEUE: return priority_queue_->peek_head();
            }
            throw runtime_error("Invalid container type");
        }

        E& tail() {
            if (type_ != ContainerType::QUEUE) throw runtime_error("Invalid container type");
            return queue_->peek_tail();
        }

        [[nodiscard]] size_t size() const {
            switch (type_) {
                case ContainerType::STACK: return stack_->get_size();
                case ContainerType::QUEUE: return queue_->get_size();
                case ContainerType::PRIORITY_QUEUE: return priority_queue_->get_size();
            }
            return 0;
        }

        [[nodiscard]] bool empty() const {
            switch (type_) {
                case ContainerType::STACK: return stack_->is_empty();
                case ContainerType::QUEUE: return queue_->is_empty();
                case ContainerType::PRIORITY_QUEUE: return priority_queue_->is_empty();
            }
            return true;
        }

        [[nodiscard]] E find_by_priority(const int& prior) const{
            if (type_ != ContainerType::PRIORITY_QUEUE) throw runtime_error("Invalid container type");
            return priority_queue_->find_by_priority(prior);
        }

        [[nodiscard]] int find_by_value(const int& value) const {
            if (type_ != ContainerType::PRIORITY_QUEUE) throw runtime_error("Invalid container type");
            return priority_queue_->find_by_value(value);
        }
    };

    template<typename E>
    class PlaygroundManager {
    private:
        unique_ptr<ContainerWrapper<E>> container_;

        static constexpr string CONTAINER_TYPES[] {"stack", "queue", "priority_queue"};
        static constexpr size_t CONTAINER_TYPES_COUNT = 3;

        // === Util methods for handling containers ===
        ContainerType string_to_type(const string& str_type) {
            if (str_type == "stack") return ContainerType::STACK;
            if (str_type == "queue") return ContainerType::QUEUE;
            if (str_type == "priority_queue") return ContainerType::PRIORITY_QUEUE;
            throw runtime_error("Invalid container type");
        }

        void check_container_exist() const {
            if (!container_) throw runtime_error("No container created! Use 'create <type> [capacity]' first.");
        }

        // === Util methods to handle commands ===
        void handle_create(const string& str_type, size_t capacity) {
            try {
                ContainerType type = string_to_type(str_type);
                container_ = make_unique<ContainerWrapper<E>>(type, capacity);
                cout << str_type << " created with capacity " << capacity << endl;
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
                cout << "Available types: stack, queue, priority_queue" << endl;
            }
        }

        void handle_push(const E& e, int priority) {
            check_container_exist();
            container_->push(e, priority);
            cout << "Pushed: " << e;
            if (container_->get_type() == ContainerType::PRIORITY_QUEUE) cout << " with priority " << priority;
            cout << endl;
        }

        void handle_pop() {
            check_container_exist();
            E value = container_->pop();
            cout << "Popped: " << value << endl;
        }

        // void handle_head() {
        //     check_container_exist();
        //     E value = container_->head();
        //     cout << "Head: " << value;
        //     if (container_->get_type() == ContainerType::PRIORITY_QUEUE) cout << " (Priority: " <<  << ")";
        // }

        // void handle_tail() {}

        void handle_size() {
            check_container_exist();
            cout << "Size: " << container_->size() << endl;
        }

        void handle_empty() {
            check_container_exist();
            cout << (container_->empty() ? "empty" : "not empty") << endl;
        }

        void handle_help() {
            std::cout << "\n=== Available Commands ===\n";
            std::cout << "create <type> [capacity] - Create container\n";
            std::cout << "push <value> [priority]  - Push value\n";
            std::cout << "pop                      - Pop element\n";
            // std::cout << "head                      - View top element\n";
            // std::cout << "tail                     - View back element (queue only)\n";
            std::cout << "size                     - Get size\n";
            std::cout << "empty                    - Check if empty\n";;
            std::cout << "help                     - Show help\n";
            std::cout << "exit                     - Exit playground\n";
            std::cout << "==========================\n";
        }

    public:
        void run() {
            cout << "\n=== Playground Mode ===\n";
            cout << "Type 'help' for commands\n";

            string command;
            while (true) {
                cout << "playground> ";
                getline(cin, command);

                if (command.empty()) continue;

                istringstream iss(command);
                string action;
                iss >> action;

                try {
                    if (action == "create") {
                        string type;
                        size_t capacity = 10;
                        iss >> type;
                        iss >> capacity;
                        handle_create(type, capacity);
                    } else if (action == "push") {
                        E value;
                        if (iss >> value) {
                            int priority = 1;
                            iss >> priority;
                            handle_push(value, priority);
                        } else cout << "Error: Invalid value" << endl;
                    } else if (action == "pop") handle_pop();
                    else if (action == "size") handle_size();
                    else if (action == "empty") handle_empty();
                    else if (action == "help") handle_help();
                    else if (action == "exit") {
                        cout << "Exiting Playground..." << endl;
                        break;
                    } else cout << "Unknown command: " << action << " Type 'help' for available commands." << endl;
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                } catch (...) {
                    cout << "Unknown error occurred" << endl;
                }
            }
        }
    };
}

#endif //PLAYGROUND_H

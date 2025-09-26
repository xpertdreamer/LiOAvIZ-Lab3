//
// Created by oblepixa on 9/25/25.
//

#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include <functional>
#include <iostream>
#include <sstream>
#include <memory>
#include <unordered_map>
#include <utility>

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
        unique_ptr<Stack<E> > stack_;
        unique_ptr<Queue<E> > queue_;
        unique_ptr<PriorityQueue<E> > priority_queue_;
        ContainerType type_{};
        string name_;

    public:
        explicit ContainerWrapper(const ContainerType type, string name) : type_(type),
            name_(std::move(name)) {
            switch (type) {
                case ContainerType::STACK:
                    stack_ = make_unique<Stack<E>>();
                    break;
                case ContainerType::QUEUE:
                    queue_ = make_unique<Queue<E>>();
                    break;
                case ContainerType::PRIORITY_QUEUE:
                    priority_queue_ = make_unique<PriorityQueue<E>>();
                    break;
            }
        }

        [[nodiscard]] ContainerType get_type() const { return type_; }
        [[nodiscard]] const string &get_name() const { return name_; }

        [[nodiscard]] const char *get_type_name() const {
            switch (type_) {
                case ContainerType::STACK: return "stack";
                case ContainerType::QUEUE: return "queue";
                case ContainerType::PRIORITY_QUEUE: return "priority_queue";
                default: return "unknown";
            }
        }

        void push(const E &e, int prior = 1) {
            switch (type_) {
                case ContainerType::STACK: stack_->push(e);
                    break;
                case ContainerType::QUEUE: queue_->push(e);
                    break;
                case ContainerType::PRIORITY_QUEUE: priority_queue_->push(e, prior);
                    break;
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

        E &head() {
            switch (type_) {
                case ContainerType::STACK: return stack_->peek();
                case ContainerType::QUEUE: return queue_->peek_head();
                case ContainerType::PRIORITY_QUEUE: return priority_queue_->peek_head();
            }
            throw runtime_error("Invalid container type");
        }

        E &tail() {
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

        [[nodiscard]] E find_by_priority(const int &prior) const {
            if (type_ != ContainerType::PRIORITY_QUEUE) throw runtime_error("Invalid container type");
            return priority_queue_->find_by_priority(prior);
        }

        [[nodiscard]] int find_by_value(const int &value) const {
            if (type_ != ContainerType::PRIORITY_QUEUE) throw runtime_error("Invalid container type");
            return priority_queue_->find_by_value(value);
        }
    };

    template<typename E>
    class PlaygroundManager {
    private:
        unordered_map<string, unique_ptr<ContainerWrapper<E> > > containers_;
        unordered_map<string, function<void(istringstream &)> > commands_ = {
            {
                "create", [this](auto &iss) {
                    string type;
                    if (!(iss >> type)) throw runtime_error("Invalid container type");
                    handle_create(type);
                }
            },
            {
                "use", [this](auto &iss) {
                    string name;
                    if (!(iss >> name)) throw runtime_error("Invalid container name");
                    handle_use(name);
                }
            },
            {"list", [this](auto &iss) { handle_list(); }},
            {
                "remove", [this](auto &iss) {
                    string name;
                    if (!(iss >> name)) throw runtime_error("Invalid container name");
                    handle_remove(name);
                }
            },
            {
                "push", [this](auto &iss) {
                    E value;
                    int prior = 1;
                    if (!(iss >> value)) throw runtime_error("Invalid value");
                    iss >> prior;
                    handle_push(value, prior);
                }
            },
            {"pop", [this](auto &iss) { handle_pop(); }},
            {"size", [this](auto &iss) { handle_size(); }},
            {"empty", [this](auto &iss) { handle_empty(); }},
            {"help", [this](auto &iss) { handle_help(); }}
        };
        string currentContainer_;
        int containerCounter_ = 0;

        // === Util methods for handling containers ===
        ContainerType string_to_type(const string &str_type) {
            if (str_type == "stack") return ContainerType::STACK;
            if (str_type == "queue") return ContainerType::QUEUE;
            if (str_type == "priority_queue") return ContainerType::PRIORITY_QUEUE;
            throw runtime_error("Invalid container type");
        }

        string generate_container_name(const string &type) {
            return type + "_" + to_string(++containerCounter_);
        }

        ContainerWrapper<E> *get_current_container() const {
            auto it = containers_.find(currentContainer_);
            if (it == containers_.end()) throw runtime_error("No container selected! Use 'use <name>' first.");
            return it->second.get();
        }

        // === Util methods to handle commands ===
        void handle_create(const string &str_type) {
            try {
                ContainerType type = string_to_type(str_type);
                string name = generate_container_name(str_type);
                containers_[name] = make_unique<ContainerWrapper<E> >(type, name);
                currentContainer_ = name;
                cout << "Created " << str_type << " '" << name << endl;
                cout << "Now using: " << name << endl;
            } catch (const exception &e) {
                cout << "Error: " << e.what() << endl;
                cout << "Available types: stack, queue, priority_queue" << endl;
            }
        }

        void handle_use(const string &name) {
            if (containers_.contains(name)) {
                currentContainer_ = name;
                auto container = get_current_container();
                cout << "Now using: " << name << " (" << container->get_type_name() << ")" << endl;
            } else {
                cout << "Error: Container '" << name << "' not found!" << endl;
            }
        }

        void handle_list() {
            if (containers_.empty()) {
                cout << "No container created!" << endl;
                return;
            }

            cout << "Available containers:" << endl;
            for (const auto &[name, container]: containers_) {
                cout << " " << name << " (" << container->get_type_name() << ")" << endl;
                if (name == currentContainer_) cout << " [CURRENT]";
                cout << " - size: " << container->size();
                cout << " - empty: " << (container->empty() ? "yes" : "no");
                cout << endl;
            }
        }

        void handle_push(const E &e, int priority) {
            auto container = get_current_container();
            container->push(e, priority);
            cout << "Pushed: " << e;
            if (container->get_type() == ContainerType::PRIORITY_QUEUE) cout << " with priority " << priority;
            cout << endl;
        }

        void handle_pop() {
            auto container = get_current_container();
            E value = container->pop();
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
            auto container = get_current_container();
            cout << "Size: " << container->size() << endl;
        }

        void handle_empty() {
            auto container = get_current_container();
            cout << (container->empty() ? "empty" : "not empty") << endl;
        }

        void handle_remove(const string &name) {
            if (containers_.contains(name)) {
                if (currentContainer_ == name) currentContainer_.clear();
                containers_.erase(name);
                cout << "Removed: " << name << endl;
            } else cout << "Error: Container '" << name << "' not found!" << endl;
        }

        void handle_help() {
            cout << "\n=== Available Commands ===\n";
            cout << "create <type>            - Create container\n";
            cout << "use <name>               - Switch to container\n";
            cout << "push <value> [priority]  - Push value\n";
            cout << "pop                      - Pop element\n";
            // cout << "head                      - View top element\n";
            // cout << "tail                     - View back element (queue only)\n";
            cout << "size                     - Get size\n";
            cout << "empty                    - Check if empty\n";
            cout << "remove <name>            - Remove container\n";
            cout << "help                     - Show help\n";
            cout << "exit                     - Exit playground\n";
            cout << "==========================\n";
        }

    public:
        void run() {
            cout << "\n=== Playground Mode ===\n";
            cout << "Type 'help' for commands\n";

            string command;
            while (true) {
                cout << "playground> ";
                if (!getline(cin, command)) break;

                if (command.empty()) continue;

                istringstream iss(command);
                string action;
                iss >> action;

                if (action == "exit") {
                    cout << "Exiting Playground..." << endl;
                    break;
                }

                try {
                    if (auto it = commands_.find(action); it != commands_.end()) {
                        it->second(iss);
                    } else {
                        cout << "Unknown command: '" << action << "'. Type 'help' for available commands." << endl;
                    }
                } catch (const exception &e) {
                    cout << "Error: " << e.what() << endl;
                } catch (...) {
                    cout << "Unknown error occurred" << endl;
                }
            }
        }
    };
}

#endif //PLAYGROUND_H

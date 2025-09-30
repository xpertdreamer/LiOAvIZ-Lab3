#include <iostream>
#include <string>

#include "priority_q/priority_q.h"
#include "priority_q_tests/test_priority_q.h"
#include "queue/queue.h"
#include "queue_tests/test_queue.h"
#include "stack/stack.h"
#include "stack_tests/test_stack.h"
#include "utils/utils.h"

// перебор всех типов
// удаление части очереди

int main() {
    /*
     * There`s four modes:
     * 1. demo - automatically push and pop elements
     * 2. test - do every sort of tests
     * 3. free - write your own code and have fun
     * 4. playground - interactive mode
     */
    while (true) {
        std::string mode = Utils::get_valid_mode();

        try {
            if (mode == "test") {
                std::cout << "=== Running Tests ===" << std::endl;
                run_tests_priority_q();
                run_tests_queue();
                run_tests_stack();
                std::cout << "\n=== All Tests Completed ===" << std::endl;
            }
            if (mode == "demo") {
                std::cout << "\n=== Running Demos ===" << std::endl;
                run_demo_priority_q();
                run_demo_queue();
                run_demo_stack();
            }
            if (mode == "free") {
                std::cout << "\n=== Running Free Mode ===" << std::endl;
                Utils::run_free_mode(); // <- write your code here
                std::cout << "\n=== Free mode is completed ===" << std::endl;
            }
            if (mode == "playground") {
                Utils::run_playground_mode();
            }
            if (mode == "exit") {
                if (Utils::get_confirm("Are you sure?")) {
                    std::cout << "Exiting program. Goodbye!" << std::endl;
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}

void Utils::run_free_mode() {
    /* */
    // std::cout << "Empty!" << std::endl;
    std::cout << "Queue peek" << std::endl;
    Queue<int> q;
    for (int i = 1; i <= 10; i++) {
        q.push(i);
    }
    q.remove_from(5);
    q.peek_q();
    std::cout << std::endl;
    std::cout << q.pop() << std::endl;
    std::cout << std::endl;

    std::cout << "Stack peek" << std::endl;
    Stack<int> s;
    for (int i = 1; i <= 10; i++) {
        s.push(i);
    }
    s.peek_stack();
    std::cout << std::endl;

    std::cout << "Priority Q peek" << std::endl;
    PriorityQueue<int> pq;
    for (int i = 1; i <= 10; i++) {
        pq.push(i, i / (-2));
    }
    pq.peek_pq();
}

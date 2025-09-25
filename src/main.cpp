#include <iostream>
#include <string>

#include "priority_q/priority_q.h"
#include "priority_q_tests/test_priority_q.h"
#include "queue_tests/test_queue.h"
#include "stack_tests/test_stack.h"
#include "utils/utils.h"

int main() {
    /*
     * There`s three modes:
     * 1. demo - automatically push and pop elements
     * 2. test - do every sort of tests
     * 3. free - write your own code and have fun
     */
    while (true) {
        std::string mode = Utils::get_valid_mode();

        try {
            if (mode == "test") {
                std::cout << "=== Running Tests ===" << std::endl;
                // run_tests_priority_q();
                run_tests_queue();
                run_tests_stack();
                std::cout << "\n=== All Tests Completed ===" << std::endl;
            }
            if (mode == "demo") {
                std::cout << "\n=== Running Demos ===" << std::endl;
                // run_demo_priority_q();
                run_demo_queue();
                run_demo_stack();
            }
            if (mode == "free") {
                std::cout << "\n=== Running Free Mode ===" << std::endl;
                Utils::run_free_mode(); // <- write your code here
                std::cout << "\n=== Free mode is completed ===" << std::endl;
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
    PriorityQueue<int> pq;
    pq.push(1, 1);
    pq.push(2, 2);
    pq.push(3,3);
    pq.push(4,0);
    std::cout  << pq.top() << std::endl;
    std::cout << pq.top_priority() << std::endl;
    std::cout << pq.contains_by_priority(2) << std::endl;
    std::cout << pq.find_by_priority(3) << std::endl;
    std::cout << pq.find_by_value(2) << std::endl;
    std::cout << pq.pop() << std::endl;
}

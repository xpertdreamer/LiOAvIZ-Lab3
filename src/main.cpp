#include <iostream>
#include <string>

#include "priority_q_tests/test_priority_q.h"
#include "queue_tests/test_queue.h"
#include "stack_tests/test_stack.h"

int main() {
    /*
     * There`s two test modes:
     * 1. demo - automatically push and pop elements
     * 2. test - do every sort of tests
     */
    while (true) {
        std::string mode;
        std::cout << "\nSelect mode:" << std::endl;
        std::cout << "1. demo - automatic push and pop elements" << std::endl;
        std::cout << "2. test - run all tests" << std::endl;
        std::cout << "3. exit - stop the program" << std::endl;
        std::cout << "Enter 'demo', 'test' or 'exit': ";

        std::cin >> mode;

        try {
            if (mode == "test") {
                run_tests_priority_q();
                run_tests_queue();
                run_tests_stack();
            } else if (mode == "demo") {
                run_demo_priority_q();
                run_demo_queue();
                run_demo_stack();
            } else if (mode == "exit") {
                std::cout << "Exiting..." << std::endl;
                break;
            } else {
                std::cout << "Invalid mode! Using demo mode by default." << std::endl;
                run_demo_priority_q();
                run_demo_queue();
                run_demo_stack();
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}
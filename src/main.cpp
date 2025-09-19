#include <iostream>
#include <string>

#include "priority_q_tests/test_priority_q.h"

int main() {
    /*
     * There`s two test modes:
     * 1. demo - automatically push and pop elements
     * 2. test - do every sort of tests
     */

    std::string mode;
    std::cout << "Select mode:" << std::endl;
    std::cout << "1. demo - automatic push and pop elements" << std::endl;
    std::cout << "2. test - run all tests" << std::endl;
    std::cout << "Enter 'demo' or 'test': ";

    std::cin >> mode;

    try {
        if (mode == "test") {
            run_tests_priority_q();
        } else if (mode == "demo") {
            run_demo_priority_q();
        } else {
            std::cout << "Invalid mode! Using demo mode by default." << std::endl;
            run_demo_priority_q();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
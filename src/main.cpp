#include <iostream>
#include <string>

#include "tests/test_priority_q.h"

int main() {
    /*
     * There`s two test modes:
     * 1. demo - automaticly push and pop alements
     * 2. test - do every sort of tests
     */

    const std::string mode = "test";
    try {
        if (mode == "test_priority_q") {
            run_tests_priority_q();
        } else {
            run_demo_priority_q();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
//
// Created by IWOFLEUR on 20.09.2025.
//
#include "test_queue.h"
#include <cassert>
#include <iostream>
#include <string>
#include "queue/queue.h"

void run_demo_queue() {
    std::cout << "\n=== Queue Demo ====" << std::endl;

    Queue<int> q(10);

    // Add elements
    for (int i = 10; i / 10 < q.get_capacity(); i += 10) {
        q.push(i);
    }

    std::cout << "Queue size: " << q.get_size() << std::endl;
    std::cout << "Capacity: " << q.get_capacity() << std::endl;
    std::cout << "Back element: " << q.peek_back() << std::endl;
    std::cout << "Front element: " << q.peek_front() << std::endl;

    std::cout << "\nExtracting all elements:" << std::endl;
    while (!q.is_empty()) {
        std::cout << "Popped: " << q.pop() << std::endl;
    }


}

void run_tests_queue() {
     std::cout << "=== Running Queue Tests ===" << std::endl;

    // Test 1: Constructor
    std::cout << "Test 1: Constructor... ";
    Queue<int> q(5);
    assert(q.is_empty());
    assert(!q.is_full());
    assert(q.get_size() == 0);
    assert(q.get_capacity() == 5);
    std::cout << "PASSED" << std::endl;

    // Test 2: Push and Front
    std::cout << "Test 2: Push and Front... ";
    q.push(10);
    assert(!q.is_empty());
    assert(q.get_size() == 1);
    assert(q.peek_front() == 10);

    q.push(20);
    assert(q.peek_front() == 10);
    assert(q.get_size() == 2);
    std::cout << "PASSED" << std::endl;

    // Test 3: Pop
    std::cout << "Test 3: Pop... ";
    assert(q.pop() == 10);
    assert(q.get_size() == 1);
    assert(q.pop() == 20);
    assert(q.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 5: Edge cases
    std::cout << "Test 5: Edge cases... ";
    Queue<int> q3(3);

    // Test empty queue exceptions
    try {
        q3.peek_front();
        assert(false);
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Queue is empty");
    }

    // Test full queue exception
    q3.push(1);
    q3.push(2);
    q3.push(3);

    try {
        q3.push(4);
        assert(false);
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Queue is full");
    }
    std::cout << "PASSED" << std::endl;

    // Test 6: Specific example
    std::cout << "Test 6: Specific example... ";
    Queue<int> q4(10);

    for (int i = 1; i <= 10; i++) {
        q4.push(std::move(i));
    }

    assert(q4.get_capacity() == 10);
    assert(q4.get_size() == 10);
    assert(q4.peek_front() == 1);

    for (int i = 1; i <= 10; i++) {
        assert(q4.pop() == i);
    }

    assert(q4.is_empty());
    assert(q4.get_size() == 0);
    std::cout << "PASSED" << std::endl;

    std::cout << "\n=== All tests PASSED! ===" << std::endl;
}
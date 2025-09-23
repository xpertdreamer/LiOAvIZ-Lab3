//
// Created by IWOFLEUR on 19.09.2025.
//
#include <cassert>
#include <iostream>
#include <string>
#include "priority_q/priority_q.h"
#include "test_priority_q.h"

void run_demo_priority_q() {
    std::cout << "=== Priority Queue Demo ===" << std::endl;

    PriorityQueue<int> pq(10);

    // Add elements
    pq.push(5, 2);
    pq.push(10, 5);
    pq.push(3, 1);
    pq.push(7, 3);
    pq.push(15, 8);

    std::cout << "Queue size: " << pq.get_size() << std::endl;
    std::cout << "Queue capacity: " << pq.get_capacity() << std::endl;
    std::cout << "Top element: " << pq.top() << " (priority: " << pq.top_priority() << ")" << std::endl;

    std::cout << "\nExtracting all elements:" << std::endl;
    // Pop elements
    while (!pq.is_empty()) {
        std::cout << "Popped: " << pq.pop() << std::endl;
    }
}

void run_tests_priority_q() {
    std::cout << "=== Running Priority Queue Tests ===" << std::endl;

    // Test 1: Constructor
    std::cout << "Test 1: Constructor... ";
    PriorityQueue<int> pq(5);
    assert(pq.is_empty());
    assert(!pq.is_full());
    assert(pq.get_size() == 0);
    assert(pq.get_capacity() == 5);
    std::cout << "PASSED" << std::endl;

    // Test 2: Push and Top
    std::cout << "Test 2: Push and Top... ";
    pq.push(10, 2);
    assert(!pq.is_empty());
    assert(pq.get_size() == 1);
    assert(pq.top() == 10);
    assert(pq.top_priority() == 2);

    pq.push(20, 5);
    assert(pq.top() == 20);
    assert(pq.top_priority() == 5);
    assert(pq.get_size() == 2);
    std::cout << "PASSED" << std::endl;

    // Test 3: Pop
    std::cout << "Test 3: Pop... ";
    assert(pq.pop() == 20);
    assert(pq.get_size() == 1);
    assert(pq.pop() == 10);
    assert(pq.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 4: Priority ordering
    std::cout << "Test 4: Priority ordering... ";
    PriorityQueue<int> pq2(10);

    pq2.push(1, 1);
    pq2.push(9, 9);
    pq2.push(5, 5);
    pq2.push(3, 3);
    pq2.push(7, 7);

    assert(pq2.pop() == 9);
    assert(pq2.pop() == 7);
    assert(pq2.pop() == 5);
    assert(pq2.pop() == 3);
    assert(pq2.pop() == 1);
    assert(pq2.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 5: Edge cases
    std::cout << "Test 5: Edge cases... ";
    PriorityQueue<int> pq3(3);

    // Test empty queue exceptions
    try {
        pq3.top();
        assert(false);
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Priority queue is empty");
    }

    // Test full queue exception
    pq3.push(1, 1);
    pq3.push(2, 2);
    pq3.push(3, 3);

    // try {
    //     pq3.push(4, 4);
    //     assert(false);
    // } catch (const std::out_of_range& e) {
    //     assert(std::string(e.what()) == "Priority queue is full");
    // }
    std::cout << "PASSED" << std::endl;

    // Test 6: Specific example
    std::cout << "Test 6: Specific example... ";
    PriorityQueue<int> pq4(10);

    for (int i = 1; i <= 10; i++) {
        pq4.push(std::move(i), i);
    }

    assert(pq4.get_capacity() == 10);
    assert(pq4.get_size() == 10);
    assert(pq4.top() == 10);
    assert(pq4.top_priority() == 10);

    for (int i = 10; i >= 1; i--) {
        assert(pq4.pop() == i);
    }

    assert(pq4.is_empty());
    assert(pq4.get_size() == 0);
    std::cout << "PASSED" << std::endl;

    std::cout << "\n=== All tests PASSED! ===" << std::endl;
}

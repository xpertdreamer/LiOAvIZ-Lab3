//
// Created by IWOFLEUR on 19.09.2025.
//
#include <cassert>
#include <iostream>
#include <string>
#include "priority_q/priority_q.h"
#include "test_priority_q.h"

void run_demo_priority_q() {
    std::cout << "\n=== Priority Queue Demo ====" << std::endl;

    PriorityQueue<int> pq(10);

    // Add elements with different priorities
    pq.push(5, 2);
    pq.push(10, 5);
    pq.push(3, 1);
    pq.push(7, 3);
    pq.push(15, 8);

    std::cout << "Queue size: " << pq.get_size() << std::endl;
    std::cout << "Queue capacity: " << pq.get_capacity() << std::endl;
    std::cout << "Top element: " << pq.top() << " (priority: " << pq.top_priority() << ")" << std::endl;

    std::cout << "\nExtracting all elements (highest priority first):" << std::endl;
    while (!pq.is_empty()) {
        std::cout << "Popped: " << pq.pop() << std::endl;
    }
}

void run_tests_priority_q() {
    std::cout << "=== Running Priority Queue Tests ===" << std::endl;

    // Test 1: Constructor and basic properties
    std::cout << "Test 1: Constructor and basic properties... ";
    PriorityQueue<int> pq(5);
    assert(pq.is_empty());
    assert(!pq.is_full());
    assert(pq.get_size() == 0);
    assert(pq.get_capacity() == 5);
    std::cout << "PASSED" << std::endl;

    // Test 2: Push and check top element
    std::cout << "Test 2: Push and Top... ";
    pq.push(10, 2);
    assert(!pq.is_empty());
    assert(pq.get_size() == 1);
    assert(pq.top() == 10);
    assert(pq.top_priority() == 2);

    pq.push(20, 5);  // Higher priority
    assert(pq.top() == 20);  // Should be new top
    assert(pq.top_priority() == 5);
    assert(pq.get_size() == 2);
    std::cout << "PASSED" << std::endl;

    // Test 3: Pop elements
    std::cout << "Test 3: Pop... ";
    assert(pq.pop() == 20);  // Highest priority first
    assert(pq.get_size() == 1);
    assert(pq.top() == 10);  // Now 10 should be top
    assert(pq.top_priority() == 2);

    assert(pq.pop() == 10);
    assert(pq.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 4: Priority ordering (max-heap behavior)
    std::cout << "Test 4: Priority ordering... ";
    PriorityQueue<int> pq2(10);

    // Insert in random order
    pq2.push(1, 1);
    pq2.push(9, 9);
    pq2.push(5, 5);
    pq2.push(3, 3);
    pq2.push(7, 7);

    // Should extract in descending priority order
    assert(pq2.pop() == 9);
    assert(pq2.pop() == 7);
    assert(pq2.pop() == 5);
    assert(pq2.pop() == 3);
    assert(pq2.pop() == 1);
    assert(pq2.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 5: Edge cases and exceptions
    std::cout << "Test 5: Edge cases and exceptions... ";
    PriorityQueue<int> pq3(3);

    // Test empty queue exceptions
    try {
        pq3.top();
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Priority queue is empty");
    }

    try {
        pq3.pop();
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Priority queue is empty");
    }

    // Test with full queue (should resize automatically)
    pq3.push(1, 1);
    pq3.push(2, 2);
    pq3.push(3, 3);
    pq3.push(4, 4);  // This should trigger resize

    assert(pq3.get_size() == 4);
    assert(pq3.get_capacity() > 3);
    std::cout << "PASSED" << std::endl;

    // Test 6: Move semantics
    std::cout << "Test 6: Move semantics... ";
    PriorityQueue<std::string> pq4(5);

    std::string str = "Hello";
    pq4.push(str, 1);           // Copy
    pq4.push(std::move(str), 2); // Move
    pq4.push("World", 3);       // Temporary

    assert(pq4.pop() == "World");  // Highest priority first
    assert(pq4.pop() == "Hello");  // Moved version
    assert(pq4.pop() == "Hello");  // Copied version
    std::cout << "PASSED" << std::endl;

    // Test 7: Complex priority scenario
    std::cout << "Test 7: Complex priority scenario... ";
    PriorityQueue<int> pq5(10);

    // Add elements with same priority (should maintain order for same priority)
    for (int i = 1; i <= 5; i++) {
        pq5.push(i * 10, i);  // Priorities 1-5
    }

    // Add elements with duplicate priorities
    pq5.push(100, 5);
    pq5.push(200, 3);

    // Should pop in priority order (5, 5, 4, 3, 3, 2, 1)
    // For same priority, order is not guaranteed but both 5s should come first
    int last_priority = 10;
    while (!pq5.is_empty()) {
        int current_priority = pq5.top_priority();
        assert(current_priority <= last_priority);  // Priority should not increase
        last_priority = current_priority;
        pq5.pop();
    }
    std::cout << "PASSED" << std::endl;

    // Test 8: Dynamic resizing
    std::cout << "Test 8: Dynamic resizing... ";
    PriorityQueue<int> pq6(2);

    pq6.push(1, 1);
    pq6.push(2, 2);
    assert(pq6.get_capacity() == 2);

    pq6.push(3, 3);  // Trigger resize
    assert(pq6.get_capacity() > 2);
    assert(pq6.get_size() == 3);

    // Verify data integrity after resize
    assert(pq6.pop() == 3);
    assert(pq6.pop() == 2);
    assert(pq6.pop() == 1);
    assert(pq6.is_empty());
    std::cout << "PASSED" << std::endl;

    std::cout << "\n=== All Priority Queue tests PASSED! ===" << std::endl;
}
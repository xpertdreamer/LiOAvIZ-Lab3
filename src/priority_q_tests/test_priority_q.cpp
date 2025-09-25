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

    PriorityQueue<int> pq;

    // Add elements with different priorities
    pq.push(5, 2);
    pq.push(10, 5);
    pq.push(3, 1);
    pq.push(7, 3);
    pq.push(15, 8);

    std::cout << "Queue size: " << pq.get_size() << std::endl;
    std::cout << "Top element: " << pq.top() << " (priority: " << pq.top_priority() << ")" << std::endl;

    // Test find methods
    std::cout << "\n=== Testing Find Methods ===" << std::endl;

    // Find by priority
    try {
        const int result = pq.find_by_priority(5);
        std::cout << "Element with priority 5: " << result << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Element with priority 5 not found" << std::endl;
    }

    // Check if priority exists
    if (pq.contains_by_priority(3)) {
        std::cout << "Priority 3 exists in queue" << std::endl;
    }

    // Find priority by value
    int priority = pq.find_by_value(7);
    if (priority != -1) {
        std::cout << "Value 7 has priority: " << priority << std::endl;
    }

    std::cout << "\nExtracting all elements (highest priority first):" << std::endl;
    while (!pq.is_empty()) {
        std::cout << "Popped: " << pq.pop() << std::endl;
    }
}

void run_tests_priority_q() {
    std::cout << "=== Running Priority Queue Tests ===" << std::endl;

    // Test 1: Constructor and basic properties
    std::cout << "Test 1: Constructor and basic properties... ";
    PriorityQueue<int> pq;
    assert(pq.is_empty());
    assert(pq.get_size() == 0);
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
    PriorityQueue<int> pq2;

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
    PriorityQueue<int> pq3;

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
    std::cout << "PASSED" << std::endl;

    // Test 6: Move semantics
    std::cout << "Test 6: Move semantics... ";
    PriorityQueue<std::string> pq4;

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
    PriorityQueue<int> pq5;

    // Add elements with same priority
    pq5.push(10, 5);
    pq5.push(20, 3);
    pq5.push(30, 5);  // Same priority as first
    pq5.push(40, 1);
    pq5.push(50, 3);  // Same priority as second

    // Should pop in priority order (5, 5, 3, 3, 1)
    assert(pq5.pop() == 10);  // priority 5
    assert(pq5.pop() == 30);  // priority 5
    assert(pq5.pop() == 20);  // priority 3
    assert(pq5.pop() == 50);  // priority 3
    assert(pq5.pop() == 40);  // priority 1
    assert(pq5.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 8: Find by priority
    std::cout << "Test 8: Find by priority... ";
    PriorityQueue<int> pq6;

    pq6.push(100, 10);
    pq6.push(200, 20);
    pq6.push(300, 30);
    pq6.push(400, 20);  // Duplicate priority

    // Test find_by_priority
    assert(pq6.find_by_priority(20) == 200);  // Returns first found
    assert(pq6.find_by_priority(30) == 300);

    // Test exception when not found
    try {
        pq6.find_by_priority(50);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Element with specified priority not found");
    }

    // Test contains_by_priority
    assert(pq6.contains_by_priority(10) == true);
    assert(pq6.contains_by_priority(20) == true);
    assert(pq6.contains_by_priority(99) == false);
    std::cout << "PASSED" << std::endl;

    // Test 9: Find by value
    std::cout << "Test 9: Find by value... ";
    PriorityQueue<std::string> pq7;

    pq7.push("apple", 5);
    pq7.push("banana", 3);
    pq7.push("orange", 7);

    assert(pq7.find_by_value("banana") == 3);
    assert(pq7.find_by_value("orange") == 7);
    assert(pq7.find_by_value("grape") == -1);  // Not found

    // Test with integers
    PriorityQueue<int> pq8;
    pq8.push(42, 10);
    pq8.push(123, 5);
    assert(pq8.find_by_value(42) == 10);
    assert(pq8.find_by_value(999) == -1);
    std::cout << "PASSED" << std::endl;

    // Test 10: Large number of elements (simpler version)
    std::cout << "Test 10: Large number of elements... ";
    PriorityQueue<int> pq9;

    constexpr int NUM_ELEMENTS = 1000;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        pq9.push(i, i);  // Priority equals value for simplicity
    }

    assert(pq9.get_size() == NUM_ELEMENTS);

    // Should pop in descending order (highest priority/value first)
    for (int i = NUM_ELEMENTS - 1; i >= 0; --i) {
        assert(pq9.top_priority() == i);
        assert(pq9.pop() == i);
    }
    assert(pq9.is_empty());
    std::cout << "PASSED" << std::endl;

    std::cout << "\n=== All Priority Queue tests PASSED! ===" << std::endl;
}
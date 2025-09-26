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

    // Create queue with initial capacity of 10
    Queue<int> q;

    // Add elements to the queue
    for (int i = 10; i <= 100; i += 10) {
        q.push(i);
    }

    std::cout << "Queue size: " << q.get_size() << std::endl;
    std::cout << "head element: " << q.peek_head() << std::endl;

    std::cout << "\nExtracting all elements (FIFO order):" << std::endl;
    while (!q.is_empty()) {
        std::cout << "Popped: " << q.pop() << std::endl;
    }
}

void run_tests_queue() {
    std::cout << "=== Running Queue Tests ===" << std::endl;

    // Test 1: Constructor and basic properties
    std::cout << "Test 1: Constructor and basic properties... ";
    Queue<int> q;
    assert(q.is_empty());
    assert(q.get_size() == 0);
    std::cout << "PASSED" << std::endl;

    // Test 2: Push elements and peek at head and tail
    std::cout << "Test 2: Push and Peek... ";
    q.push(10);
    assert(!q.is_empty());
    assert(q.get_size() == 1);
    assert(q.peek_head() == 10);

    q.push(20);
    assert(q.peek_head() == 10);  // Queue is FIFO, so head should be first pushed element
    assert(q.get_size() == 2);
    std::cout << "PASSED" << std::endl;

    // Test 3: Pop elements from the queue
    std::cout << "Test 3: Pop... ";
    assert(q.pop() == 10);
    assert(q.get_size() == 1);
    assert(q.peek_head() == 20);  // After pop, head should be next element

    assert(q.pop() == 20);
    assert(q.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 4: Move semantics with string objects
    std::cout << "Test 4: Move semantics... ";
    Queue<std::string> q2;
    std::string str = "Hello";
    q2.push(str);           // Copy constructor
    q2.push(std::move(str)); // Move constructor
    q2.push("World");       // Temporary object (move)

    assert(q2.pop() == "Hello");  // FIFO: first in, first out
    assert(q2.pop() == "Hello");  // Moved version (original string was moved)
    assert(q2.pop() == "World");
    std::cout << "PASSED" << std::endl;

    // Test 5: Edge cases and exception handling
    std::cout << "Test 5: Edge cases and exceptions... ";
    Queue<int> q3;

    // Test empty queue exceptions
    try {
        q3.peek_head();
        assert(false); // Should not reach this point
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Queue is empty");
    }

    try {
        q3.pop();
        assert(false); // Should not reach this point
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Queue is empty");
    }
    std::cout << "PASSED" << std::endl;

    // Test 6: Specific FIFO behavior example
    std::cout << "Test 6: Specific FIFO example... ";
    Queue<int> q4;

    // Fill queue with numbers 1 to 10
    for (int i = 1; i <= 10; i++) {
        q4.push(i);
    }

    assert(q4.get_size() == 10);
    assert(q4.peek_head() == 1);  // First pushed element should be at head

    // Verify FIFO order (First In, First Out)
    for (int i = 1; i <= 10; i++) {
        assert(q4.pop() == i);
    }

    assert(q4.is_empty());
    assert(q4.get_size() == 0);
    std::cout << "PASSED" << std::endl;

    // Test 7: Queue with different data types
    std::cout << "Test 7: Different data types... ";
    Queue<double> doubleQueue;
    doubleQueue.push(3.14);
    doubleQueue.push(2.71);
    assert(doubleQueue.pop() == 3.14);
    assert(doubleQueue.pop() == 2.71);

    Queue<char> charQueue;
    charQueue.push('A');
    charQueue.push('B');
    assert(charQueue.pop() == 'A');
    assert(charQueue.pop() == 'B');
    std::cout << "PASSED" << std::endl;

    std::cout << "\n=== All Queue tests PASSED! ===" << std::endl;
}
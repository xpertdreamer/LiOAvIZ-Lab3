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
    Queue<int> q(10);

    // Add elements to the queue
    for (int i = 10; i <= 100; i += 10) {
        q.push(i);
    }

    std::cout << "Queue size: " << q.get_size() << std::endl;
    std::cout << "Capacity: " << q.get_capacity() << std::endl;
    std::cout << "Front element: " << q.peek_front() << std::endl;
    std::cout << "Back element: " << q.peek_back() << std::endl;

    std::cout << "\nExtracting all elements (FIFO order):" << std::endl;
    while (!q.is_empty()) {
        std::cout << "Popped: " << q.pop() << std::endl;
    }
}

void run_tests_queue() {
    std::cout << "=== Running Queue Tests ===" << std::endl;

    // Test 1: Constructor and basic properties
    std::cout << "Test 1: Constructor and basic properties... ";
    Queue<int> q(5);
    assert(q.is_empty());
    assert(!q.is_full());
    assert(q.get_size() == 0);
    assert(q.get_capacity() == 5);
    std::cout << "PASSED" << std::endl;

    // Test 2: Push elements and peek at front and back
    std::cout << "Test 2: Push and Peek... ";
    q.push(10);
    assert(!q.is_empty());
    assert(q.get_size() == 1);
    assert(q.peek_front() == 10);
    assert(q.peek_back() == 10);  // Only one element, so front and back are same

    q.push(20);
    assert(q.peek_front() == 10);  // Queue is FIFO, so front should be first pushed element
    assert(q.peek_back() == 20);   // Back should be last pushed element
    assert(q.get_size() == 2);
    std::cout << "PASSED" << std::endl;

    // Test 3: Pop elements from the queue
    std::cout << "Test 3: Pop... ";
    assert(q.pop() == 10);
    assert(q.get_size() == 1);
    assert(q.peek_front() == 20);  // After pop, front should be next element
    assert(q.peek_back() == 20);   // Only one element left

    assert(q.pop() == 20);
    assert(q.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 4: Move semantics with string objects
    std::cout << "Test 4: Move semantics... ";
    Queue<std::string> q2(3);
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
    Queue<int> q3(3);

    // Test empty queue exceptions
    try {
        q3.peek_front();
        assert(false); // Should not reach this point
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Queue is empty");
    }

    try {
        q3.peek_back();
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
    Queue<int> q4(10);

    // Fill queue with numbers 1 to 10
    for (int i = 1; i <= 10; i++) {
        q4.push(i);
    }

    assert(q4.get_capacity() == 10);
    assert(q4.get_size() == 10);
    assert(q4.peek_front() == 1);  // First pushed element should be at front
    assert(q4.peek_back() == 10);  // Last pushed element should be at back

    // Verify FIFO order (First In, First Out)
    for (int i = 1; i <= 10; i++) {
        assert(q4.pop() == i);
    }

    assert(q4.is_empty());
    assert(q4.get_size() == 0);
    std::cout << "PASSED" << std::endl;

    // Test 7: Dynamic resizing functionality
    std::cout << "Test 7: Dynamic resizing... ";
    Queue<int> q5(2); // Small initial capacity to trigger resizing

    q5.push(1);
    q5.push(2);
    assert(q5.get_capacity() == 2);

    // This should trigger automatic resizing
    q5.push(3);
    assert(q5.get_capacity() > 2);
    assert(q5.get_size() == 3);

    // Verify data integrity after resize operation (FIFO order maintained)
    assert(q5.pop() == 1);
    assert(q5.pop() == 2);
    assert(q5.pop() == 3);
    assert(q5.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 8: Queue with different data types
    std::cout << "Test 8: Different data types... ";
    Queue<double> doubleQueue(5);
    doubleQueue.push(3.14);
    doubleQueue.push(2.71);
    assert(doubleQueue.pop() == 3.14);
    assert(doubleQueue.pop() == 2.71);

    Queue<char> charQueue(3);
    charQueue.push('A');
    charQueue.push('B');
    assert(charQueue.pop() == 'A');
    assert(charQueue.pop() == 'B');
    std::cout << "PASSED" << std::endl;

    std::cout << "\n=== All Queue tests PASSED! ===" << std::endl;
}
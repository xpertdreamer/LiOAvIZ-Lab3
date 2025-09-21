//
// Created by IWOFLEUR on 20.09.2025.
//
#include "test_stack.h"
#include <cassert>
#include <iostream>
#include <string>
#include "stack/stack.h"

void run_demo_stack() {
    std::cout << "\n=== Stack Demo ====" << std::endl;

    // Create stack with initial capacity of 10
    Stack<int> s(10);

    // Add elements to the stack
    for (int i = 1; i <= 10; i++) {
        s.push(i);
    }

    std::cout << "Stack size: " << s.get_size() << std::endl;
    std::cout << "Capacity: " << s.get_capacity() << std::endl;
    std::cout << "Top element: " << s.peek() << std::endl;

    std::cout << "\nExtracting all elements (LIFO order):" << std::endl;
    while (!s.is_empty()) {
        std::cout << "Popped: " << s.pop() << std::endl;
    }
}

void run_tests_stack() {
    std::cout << "=== Running Stack Tests ===" << std::endl;

    // Test 1: Constructor and basic properties
    std::cout << "Test 1: Constructor and basic properties... ";
    Stack<int> s(5);
    assert(s.is_empty());
    assert(!s.is_full());
    assert(s.get_size() == 0);
    assert(s.get_capacity() == 5);
    std::cout << "PASSED" << std::endl;

    // Test 2: Push elements and peek at the top
    std::cout << "Test 2: Push and Peek... ";
    s.push(10);
    assert(!s.is_empty());
    assert(s.get_size() == 1);
    assert(s.peek() == 10);

    s.push(20);
    assert(s.peek() == 20);  // Stack is LIFO, so top should be the last pushed element
    assert(s.get_size() == 2);
    std::cout << "PASSED" << std::endl;

    // Test 3: Pop elements from the stack
    std::cout << "Test 3: Pop... ";
    assert(s.pop() == 20);
    assert(s.get_size() == 1);
    assert(s.pop() == 10);
    assert(s.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 4: Move semantics with string objects
    std::cout << "Test 4: Move semantics... ";
    Stack<std::string> s2(3);
    std::string str = "Hello";
    s2.push(str);           // Copy constructor
    s2.push(std::move(str)); // Move constructor
    s2.push("World");       // Temporary object (move)

    assert(s2.pop() == "World");
    assert(s2.pop() == "Hello");  // Moved version
    assert(s2.pop() == "Hello");  // Copied version
    std::cout << "PASSED" << std::endl;

    // Test 5: Edge cases and exception handling
    std::cout << "Test 5: Edge cases and exceptions... ";
    Stack<int> s3(3);

    // Test empty stack exceptions
    try {
        s3.peek();
        assert(false); // Should not reach this point
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack is empty");
    }

    try {
        s3.pop();
        assert(false); // Should not reach this point
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack is empty");
    }
    std::cout << "PASSED" << std::endl;

    // Test 6: Specific LIFO behavior example
    std::cout << "Test 6: Specific LIFO example... ";
    Stack<int> s4(10);

    // Fill stack with numbers 1 to 10
    for (int i = 1; i <= 10; i++) {
        s4.push(i);
    }

    assert(s4.get_capacity() == 10);
    assert(s4.get_size() == 10);
    assert(s4.peek() == 10);  // Last pushed element should be on top

    // Verify LIFO order (Last In, First Out)
    for (int i = 10; i >= 1; i--) {
        assert(s4.pop() == i);
    }

    assert(s4.is_empty());
    assert(s4.get_size() == 0);
    std::cout << "PASSED" << std::endl;

    // Test 7: Dynamic resizing functionality
    std::cout << "Test 7: Dynamic resizing... ";
    Stack<int> s5(2); // Small initial capacity to trigger resizing

    s5.push(1);
    s5.push(2);
    assert(s5.get_capacity() == 2);

    // This should trigger automatic resizing
    s5.push(3);
    assert(s5.get_capacity() > 2);
    assert(s5.get_size() == 3);

    // Verify data integrity after resize operation
    assert(s5.pop() == 3);
    assert(s5.pop() == 2);
    assert(s5.pop() == 1);
    assert(s5.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 8: Stack with different data types
    std::cout << "Test 8: Different data types... ";
    Stack<double> doubleStack(5);
    doubleStack.push(3.14);
    doubleStack.push(2.71);
    assert(doubleStack.pop() == 2.71);
    assert(doubleStack.pop() == 3.14);

    Stack<char> charStack(3);
    charStack.push('A');
    charStack.push('B');
    assert(charStack.pop() == 'B');
    assert(charStack.pop() == 'A');
    std::cout << "PASSED" << std::endl;

    std::cout << "\n=== All Stack tests PASSED! ===" << std::endl;
}
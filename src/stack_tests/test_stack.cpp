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

    Stack<int> s(10);

    // Add elements
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

    // Test 1: Constructor
    std::cout << "Test 1: Constructor... ";
    Stack<int> s(5);
    assert(s.is_empty());
    assert(!s.is_full());
    assert(s.get_size() == 0);
    assert(s.get_capacity() == 5);
    std::cout << "PASSED" << std::endl;

    // Test 2: Push and Peek
    std::cout << "Test 2: Push and Peek... ";
    s.push(10);
    assert(!s.is_empty());
    assert(s.get_size() == 1);
    assert(s.peek() == 10);

    s.push(20);
    assert(s.peek() == 20);  // Stack is LIFO, so top should be 20
    assert(s.get_size() == 2);
    std::cout << "PASSED" << std::endl;

    // Test 3: Pop
    std::cout << "Test 3: Pop... ";
    assert(s.pop() == 20);
    assert(s.get_size() == 1);
    assert(s.pop() == 10);
    assert(s.is_empty());
    std::cout << "PASSED" << std::endl;

    // Test 4: Move semantics
    std::cout << "Test 4: Move semantics... ";
    Stack<std::string> s2(3);
    std::string str = "Hello";
    s2.push(str);           // Copy
    s2.push(std::move(str)); // Move
    s2.push("World");       // Move temporary

    assert(s2.pop() == "World");
    assert(s2.pop() == "Hello");  // Moved version
    assert(s2.pop() == "Hello");  // Copied version
    std::cout << "PASSED" << std::endl;

    // Test 5: Edge cases
    std::cout << "Test 5: Edge cases... ";
    Stack<int> s3(3);

    // Test empty stack exceptions
    try {
        s3.peek();
        assert(false);
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack is empty");
    }

    try {
        s3.pop();
        assert(false);
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack is empty");
    }

    // Test full stack exception
    s3.push(1);
    s3.push(2);
    s3.push(3);

    try {
        s3.push(4);
        assert(false);
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Stack is full");
    }
    std::cout << "PASSED" << std::endl;

    // Test 6: Specific example
    std::cout << "Test 6: Specific example... ";
    Stack<int> s4(10);

    for (int i = 1; i <= 10; i++) {
        s4.push(i);
    }

    assert(s4.get_capacity() == 10);
    assert(s4.get_size() == 10);
    assert(s4.peek() == 10);  // Last element pushed should be on top

    // Check LIFO order
    for (int i = 10; i >= 1; i--) {
        assert(s4.pop() == i);
    }

    assert(s4.is_empty());
    assert(s4.get_size() == 0);
    std::cout << "PASSED" << std::endl;

    std::cout << "\n=== All Stack tests PASSED! ===" << std::endl;
}
//
// Created by IWOFLEUR on 20.09.2025.
//
#include "test_queue.h"
#include <cassert>
#include <iostream>
#include <string>
#include "queue/queue.h"

void run_demo_queue() {
    std::cout << "=== Queue Demo ====" << std::endl;

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


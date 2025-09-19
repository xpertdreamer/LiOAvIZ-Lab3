#include <iostream>

#include "priority_q/priority_q.h"

int main() {
    PriorityQueue<int> q(10);
    std::cout << "capacity: " << q.get_capacity() << std::endl;

    q.push(2, 2);
    q.push(3, 3);
    q.push(1, 1);
    q.push(4, 4);
    q.push(5, 5);
    q.push(2, 2);
    q.push(9, 9);
    q.push(3, 3);
    q.push(7, 7);
    q.push(6, 6);
    std::cout << "size: " << q.get_size() << std::endl;
    std::cout << "top: " << q.top() << std::endl;
    std::cout << "top prior: " << q.top_priority() << std::endl;

    while (!q.is_empty()) {
        std::cout << q.pop() << " ";
    }

    std::cout << "\nsize: " << q.get_size() << std::endl;

    return 0;
}
#include <iostream>

#include "priority_q/priority_q.h"

int main() {
    PriorityQueue<int> q(5);
    std::cout << "capacity: " << q.get_capacity() << std::endl;
    q.push(1, 1);
    std::cout << q.get_size() << std::endl;
    std::cout << "top: " << q.top() << std::endl;
    return 0;
}
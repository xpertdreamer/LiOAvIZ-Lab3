//
// Created by IWOFLEUR on 24.09.2025.
//

#ifndef UTILS_H
#define UTILS_H
#include <string>

namespace Utils {
    void clear_input_buffer();
    std::string to_lower(const std::string& str);
    bool is_valid_mode(const std::string& str);
    std::string get_valid_mode();
    bool get_confirm(const std::string& msg);
    void run_free_mode();
}

#endif //UTILS_H
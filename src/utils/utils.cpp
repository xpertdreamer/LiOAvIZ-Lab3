//
// Created by IWOFLEUR on 24.09.2025.
//

#include "utils.h"

#include <iostream>
#include <limits>

#include "playground.h"

namespace Utils {
    void clear_input_buffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string to_lower(const std::string &str) {
        std::string result = str;
        for (char& c : result) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return result;
    }

    bool is_valid_mode(const std::string &str) {
        const std::string lower = to_lower(str);
        return lower == "demo" || lower == "test" || lower == "free" || lower == "exit" || lower == "playground";
    }

    std::string get_valid_mode() {
        std::string mode;

        while (true) {
            std::cout << "\nSelect mode:" << std::endl;
            std::cout << "1. demo - automatic push and pop elements" << std::endl;
            std::cout << "2. test - run all tests" << std::endl;
            std::cout << "3. free - run your own code" << std::endl;
            std::cout << "4. playground - interactive mode" << std::endl;
            std::cout << "5. exit - stop the program" << std::endl;
            std::cout << "Enter 'demo', 'test', 'free' or 'exit': ";

            std::cin >> mode;

            if (is_valid_mode(mode)) {
                return to_lower(mode);
            }
            std::cout << "Invalid input '" << mode << "'. Please try again." << std::endl;
            clear_input_buffer();
        }
    }


    bool get_confirm(const std::string &msg) {
        std::string input;

        while (true) {
            std::cout << msg << " (y/n): ";
            std::cin >> input;
            input = to_lower(input);

            if (input == "y" || input == "yes") {
                clear_input_buffer();
                return true;
            }
            if (input == "n" || input == "no") {
                clear_input_buffer();
                return false;
            }
            std::cout << "Please enter 'y' or 'n'." << std::endl;
            clear_input_buffer();
        }
    }

    void run_playground_mode() {
        std::cout << "Select data type (int, double, string): ";
        std::string type;
        std::cin >> type;
        std::cin.ignore();

        if (type == "int") {
            Playground::PlaygroundManager<int> playground;
            playground.run();
        } else if (type == "double") {
            Playground::PlaygroundManager<double> playground;
            playground.run();
        } else if (type == "string") {
            Playground::PlaygroundManager<std::string> playground;
            playground.run();
        } else {
            std::cout << "Unsupported type! Using int by default." << std::endl;
            Playground::PlaygroundManager<int> playground;
            playground.run();
        }
    }

}

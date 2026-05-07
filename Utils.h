#pragma once
#include <iostream>
#include <string>
const int WIDTH = 80;

inline void printBorder() {
    std::cout << std::string(WIDTH, '=') << std::endl;
}

inline void printDivider() {
    std::cout << std::string(WIDTH, '-') << std::endl;
}

inline void printCentered(const std::string& text) {
    int padding = 0;
    if (text.length() < static_cast<std::string::size_type>(WIDTH)) {
        padding = (WIDTH - static_cast<int>(text.length())) / 2;
    }
    std::cout << std::string(padding, ' ') << text << std::endl;
}

inline void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

inline void pause() {
    std::cout << "\nPress enter to continue...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

inline void printWrapped(const std::string& text) {
    int lineWidth = WIDTH - 4; // account for 2 spaces padding on each side
    int start = 0;
    while (start < (int)text.length()) {
        if ((int)text.length() - start <= lineWidth) {
            std::cout << "  " << text.substr(start) << std::endl;
            break;
        }
        int end = start + lineWidth;
        while (end > start && text[end] != ' ') {
            end--;
        }
        if (end == start) end = start + lineWidth;
        std::cout << "  " << text.substr(start, end - start) << std::endl;
        start = end + 1;
    }
}

inline void displayError() {
    clearScreen();
    printBorder();
    printCentered("Invalid Command");
    printCentered("Type 'help' for a list of commands.");
    printBorder();
    pause();
}

inline void printTwoSided(const std::string& left, const std::string& right) {
    int leftPos = WIDTH / 4 - static_cast<int>(left.length()) / 2;
    int rightPos = (3 * WIDTH / 4) - static_cast<int>(right.length()) / 2;
    if (leftPos < 0) leftPos = 0;
    int gap = rightPos - leftPos - static_cast<int>(left.length());
    if (gap < 1) gap = 1;
    std::cout << std::string(leftPos, ' ') << left << std::string(gap, ' ') << right << std::endl;
}

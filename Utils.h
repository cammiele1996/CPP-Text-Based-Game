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
    int padding = (WIDTH - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << std::endl;
}

inline void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

inline void pause() {
    std::cout << "\nPress enter to continue...";
    std::cin.get();
}

inline void printWrapped(const std::string& text) {
    int lineWidth = WIDTH; // 2 spaces padding on each side
    int start = 0;
    while (start < text.length()) {
        if (text.length() - start <= lineWidth) {
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
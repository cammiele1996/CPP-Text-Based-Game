#pragma once
#include <iostream>
#include <string>

// Display utility functions used throughout the game.
// All functions are inline so they can be included in multiple translation units without linker errors.

const int WIDTH = 80; // Console display width — all formatting is relative to this

// Prints a full-width border using '='
inline void printBorder() {
    std::cout << std::string(WIDTH, '=') << std::endl;
}

// Prints a full-width divider using '-'
inline void printDivider() {
    std::cout << std::string(WIDTH, '-') << std::endl;
}

// Centers text within WIDTH. Truncates padding if text is wider than WIDTH.
inline void printCentered(const std::string& text) {
    int padding = 0;
    if (text.length() < static_cast<std::string::size_type>(WIDTH)) {
        padding = (WIDTH - static_cast<int>(text.length())) / 2;
    }
    std::cout << std::string(padding, ' ') << text << std::endl;
}

// Clears the terminal using ANSI escape codes. Works on Mac/Linux and Windows terminals.
// Does not work in Xcode's built-in console — run via terminal to see correct output.
inline void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

// Waits for the player to press enter before continuing
inline void pause() {
    std::cout << "\nPress enter to continue...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

// Word-wraps text to fit within WIDTH with 2-space left padding.
// Breaks on spaces — will force-break if a single word exceeds the line width.
inline void printWrapped(const std::string& text) {
    int lineWidth = WIDTH - 4;
    int start = 0;
    while (start < (int)text.length()) {
        if ((int)text.length() - start <= lineWidth) {
            std::cout << "  " << text.substr(start) << std::endl;
            break;
        }
        int end = start + lineWidth;
        while (end > start && text[end] != ' ') end--;
        if (end == start) end = start + lineWidth;
        std::cout << "  " << text.substr(start, end - start) << std::endl;
        start = end + 1;
    }
}

// Displays a generic invalid input screen with a help hint. Used for all input validation errors.
inline void displayError() {
    clearScreen();
    printBorder();
    printCentered("Invalid Command");
    printCentered("Type 'help' for a list of commands.");
    printBorder();
    pause();
}

// Prints two strings side by side — left at 1/4 width, right at 3/4 width.
// Used in combatStatus() to display player HP vs enemy HP.
inline void printTwoSided(const std::string& left, const std::string& right) {
    int leftPos = WIDTH / 4 - static_cast<int>(left.length()) / 2;
    int rightPos = (3 * WIDTH / 4) - static_cast<int>(right.length()) / 2;
    if (leftPos < 0) leftPos = 0;
    int gap = rightPos - leftPos - static_cast<int>(left.length());
    if (gap < 1) gap = 1;
    std::cout << std::string(leftPos, ' ') << left << std::string(gap, ' ') << right << std::endl;
}
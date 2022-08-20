//
//  main.cpp
//  maze
//
//  Created by Nate Webster on 8/31/21.
//

#include "Maze.h"

#include <iostream>
#include <stack>
#include <stdlib.h>
#include <time.h>
#include <limits>
using namespace std;

void ignoreLine();

int main(int argc, const char * argv[]) {

    while (true) {
        int rows, columns;
        std::string start, end, solve;
        std::cout << "Make a new maze!\n" << "\n";
        
        // Get number of rows
        while (true) {
            std::cout << "How many rows?: ";
            std::cin >> rows;
            if (!std::cin) { // non integer input
                std::cin.clear();
                ignoreLine();
                std::cerr << "Invalid input. Please try again.\n";
            } else if (rows < 1) {
                ignoreLine();
                std::cerr << "Invalid input. There must be at least one row. Please try again.\n";
            } else { // break when proper input found
                ignoreLine();
                break;
            }
        }
        
        // Get number of columns
        while (true) {
            std::cout << "How many columns?: ";
            std::cin >> columns;
            if (!std::cin) { // non integer input
                std::cin.clear();
                ignoreLine();
                std::cerr << "Invalid input. Please try again.\n";
            } else if (columns < 1) {
                ignoreLine();
                std::cerr << "Invalid input. There must be at least one column. Please try again.\n";
            } else { // break when proper input found
                ignoreLine();
                break;
            }
        }
       
        // Get starting location
        while (true) {
            std::cout << "Where should the maze start (top, bottom, left, or right)?: ";
            std::cin >> start;
            ignoreLine();
            if (start != "top"
                && start != "bottom"
                && start != "left"
                && start != "right") {
                std::cerr << "Invalid input. Must enter 'top', 'bottom', 'left', or 'right'. Please try again.\n";
            } else {
                break;
            }
        }
        
        // Get ending location
        while (true) {
            std::cout << "Where should the maze end (top, bottom, left, or right)?: ";
            std::cin >> end;
            ignoreLine();
            if (end == start) {
                std::cerr << "Invalid input. Maze must end at a different location than it starts. Please try again.\n";
            } else if (end != "top"
                && end != "bottom"
                && end != "left"
                && end != "right") {
                std::cerr << "Invalid input. Must enter 'top', 'bottom', 'left', or 'right'. Please try again.\n";
            } else {
                break;
            }
        }
        
        Maze M(rows, columns, start, end);
        M.display();
        
        // Ask if user wants to see solution
        while (true) {
            std::cout << "Show the solution (yes or no)?: ";
            std::cin >> solve;
            ignoreLine();
            if (solve == "yes") {
                M.display_solution();
                break;
            } else if (solve == "no") {
                break;
            } else {
                std::cerr << "Invalid input. Please enter 'yes' or 'no'.\n";
            }
        }
        
        std::cout << "\n";
    }
    return 0;
}



void ignoreLine() {  // used to ignore all buffered characters up to a newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

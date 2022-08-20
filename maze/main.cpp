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
using namespace std;

int main(int argc, const char * argv[]) {

    while (true) {
        int rows, columns;
        std::string start, end, solve;
        
        std::cout << "Make a new maze!\n" << "\n";
        std::cout << "How many rows?: ";
        std::cin >> rows;
        std::cout << "How many columns?: ";
        std::cin >> columns;
        std::cout << "Where should the maze start (top, bottom, left, or right)?: ";
        std::cin >> start;
        std::cout << "Where should the maze end (top, bottom, left, or right)?: ";
        std::cin >> end;
        
        Maze M(rows, columns, start, end);
        
        M.display();
        std::cout << "Show the solution (yes or no)?: ";
        std::cin >> solve;
        if (solve == "yes")
            M.display_solution();
        
        std::cout << "\n";
    }
    return 0;
}

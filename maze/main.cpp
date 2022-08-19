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
    Maze A(20,20,"bottom","top");
    A.display();
    A.display_solution();
    return 0;
}

//
//  Maze.cpp
//  maze
//
//  Created by Nate Webster on 8/31/21.
//

#include "Maze.h"
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

Maze::Maze(int rows, int columns, std::string start, std::string end, char wall_char, char soltn_char)
: m_rows(rows), m_columns(columns), m_startPoint(start), m_endPoint(end), m_beenSolved(false),
    m_wall_char(wall_char), m_soltn_char(soltn_char), m_wall_color(100), m_soltn_color(200),
m_space_color(0)
{
    m_horizontalWalls.resize(m_rows + 1);
    for (int i = 0; i < m_rows + 1; i++)
    {
        m_horizontalWalls[i].resize(m_columns);
        for (int k = 0; k < m_columns; k++)
            m_horizontalWalls[i][k] = 1;
    }
    
    m_verticalWalls.resize(m_columns + 1);
    for (int i = 0; i < m_columns + 1; i++)
    {
        m_verticalWalls[i].resize(m_rows);
        for (int k = 0; k < m_rows; k++)
            m_verticalWalls[i][k] = 1;
    }
    
    // remove walls on border for a start and end
    // assign coordinates to start and end cell members
    if (m_startPoint == "top") {
        m_horizontalWalls[0][m_columns/2] = 0;
        m_startCell.push_back(0);
        m_startCell.push_back(m_columns/2);
    } else if (m_startPoint == "bottom") {
        m_horizontalWalls[m_rows][m_columns/2] = 0;
        m_startCell.push_back(m_rows - 1);
        m_startCell.push_back(m_columns/2);
    } else if (m_startPoint == "left") {
        m_verticalWalls[0][m_rows/2] = 0;
        m_startCell.push_back(m_rows/2);
        m_startCell.push_back(0);
    } else if (m_startPoint == "right") {
        m_verticalWalls[m_columns][m_rows/2] = 0;
        m_startCell.push_back(m_rows/2);
        m_startCell.push_back(m_columns - 1);
    }
    
    if (m_endPoint == "top") {
        m_horizontalWalls[0][m_columns/2] = 0;
        m_endCell.push_back(0);
        m_endCell.push_back(m_columns/2);
    } else if (m_endPoint == "bottom") {
        m_horizontalWalls[m_rows][m_columns/2] = 0;
        m_endCell.push_back(m_rows - 1);
        m_endCell.push_back(m_columns/2);
    } else if (m_endPoint == "left") {
        m_verticalWalls[0][m_rows/2] = 0;
        m_endCell.push_back(m_rows/2);
        m_endCell.push_back(0);
    } else if (m_endPoint == "right") {
        m_verticalWalls[m_columns][m_rows/2] = 0;
        m_endCell.push_back(m_rows/2);
        m_endCell.push_back(m_columns - 1);
    }
    
    
    
    // set up a 2d vector representing each cell in the maze as unvisited
    std::vector<std::vector<bool>> cellsVisited;
    cellsVisited.resize(m_rows);
    for (int i = 0; i < m_rows; i++)
    {
        cellsVisited[i].resize(m_columns);
        for (int k = 0; k < m_columns; k++)
            cellsVisited[i][k] = false;
    }
    
    int curRow = m_rows/2, curCol = m_columns/2;
    cellsVisited[curRow][curCol] = true;
    int firstCell [2] = {curRow,curCol};
    std::stack<int*> visits;
    visits.push(firstCell);
    srand(time(0)); // used for random number generation in the while loop
    while (!visits.empty())
    {
        curRow = visits.top()[0];
        curCol = visits.top()[1];
        visits.pop();

        bool up, down, left, right;
        up = false; down = false; left = false; right = false;

        // check each neighboring cells to see if they've been visited
        // up
        if (curRow - 1 >= 0 && !cellsVisited[curRow - 1][curCol])
            up = true;
        // down
        if (curRow + 1 <= m_rows - 1 && !cellsVisited[curRow + 1][curCol])
            down = true;
        // left
        if(curCol - 1 >= 0 && !cellsVisited[curRow][curCol - 1])
            left = true;
        // right
        if(curCol + 1 <= m_columns - 1 && !cellsVisited[curRow][curCol + 1])
            right = true;

        if (up || down || left || right)
        {
            int *curCell = new int [2];
            curCell[0] = curRow;
            curCell[1] = curCol;
            visits.push(curCell);

        // select random unvisited neighboring cell and remove wall
        // * temporarily just try the directions in a predefined order for testing *
            
            int randDirection = 0; //random number between 1 and 4
            
            while (randDirection == 0)
            {
                randDirection = rand() % 4 + 1;
                if (randDirection == 1 && up)
                    break;
                else if (randDirection == 2 && down)
                    break;
                else if (randDirection == 3 && left)
                    break;
                else if (randDirection == 4 && right)
                    break;
                else
                    randDirection = 0;
            }
            
            int *nextCell = new int [2];

            switch (randDirection) {
                case 1: // up
                    m_horizontalWalls[curRow][curCol] = 0;
                    cellsVisited[curRow - 1][curCol] = true;
                    nextCell[0] = curRow - 1;
                    nextCell[1] = curCol;
                    break;
                case 2: // down
                    m_horizontalWalls[curRow + 1][curCol] = 0;
                    cellsVisited[curRow + 1][curCol] = true;
                    nextCell[0] = curRow + 1;
                    nextCell[1] = curCol;
                    break;
                case 3: // left
                    m_verticalWalls[curCol][curRow] = 0;
                    cellsVisited[curRow][curCol - 1] = true;
                    nextCell[0] = curRow;
                    nextCell[1] = curCol - 1;
                    break;
                case 4: // right
                    m_verticalWalls[curCol + 1][curRow] = 0;
                    cellsVisited[curRow][curCol + 1] = true;
                    nextCell[0] = curRow;
                    nextCell[1] = curCol + 1;
            }
            visits.push(nextCell);
            
        }

    }
}

void Maze::display_solution_ASCII()
{
    // If maze hasn't been solved yet, do that
    if (!m_beenSolved)
        solve();
    
    // Actual work of displaying solution is done in display, using m_solution
    display_ASCII(true);
}

void Maze::display_solution_image()
{
    // If maze hasn't been solved yet, do that
    if (!m_beenSolved)
        solve();
    
    // Actual work of displaying solution is done in display, using m_solution
    display_image(true);
}

void Maze::solve()
{
    m_solution.resize(m_rows);
    for (int i = 0; i < m_rows; i++)
    {
        m_solution[i].resize(m_columns);
        for (int k = 0; k < m_columns; k++)
            m_solution[i][k] = false;
    }
    
    // use depth first search to find path from start cell to end cell
    std::vector<std::vector<int>> solutionPath;
    // set up a 2d vector representing each cell in the maze as unvisited
    std::vector<std::vector<bool>> cellsVisited;
    cellsVisited.resize(m_rows);
    for (int i = 0; i < m_rows; i++)
    {
        cellsVisited[i].resize(m_columns);
        for (int k = 0; k < m_columns; k++)
            cellsVisited[i][k] = false;
    }
    
    solver(solutionPath,cellsVisited,m_startCell,m_endCell);
    solutionPath.push_back(m_endCell);
    
    // take cells from the solutionPath and mark them in 2d vector m_solution member
    for (int i = 0; i < solutionPath.size(); i++) {
        m_solution[solutionPath[i][0]][solutionPath[i][1]] = true;
    }
    m_beenSolved = true;
}

// helper function to solve3 because it uses recursion
bool Maze::solver(std::vector<std::vector<int>>& path, std::vector<std::vector<bool>> & cellsVisited, std::vector<int> start, std::vector<int> end)
{
    int row = start[0], col = start[1];
    cellsVisited[row][col] = true; // current cell visited
    if (start == end) // current cell is the end cell so path has been found
        return true;
    
    bool result = false;
    path.push_back(start); // add current cell to path
    
    // for each direction
    // if the cell exists, there is no blocking wall, and hasn't been visited, take that path
    // right
    if (col + 1 < m_columns && !m_verticalWalls[col + 1][row] && !cellsVisited[row][col + 1]) {
        std::vector<int> rightCell;
        rightCell.push_back(row);
        rightCell.push_back(col + 1);
        result = solver(path,cellsVisited, rightCell, end);
    }
    // left
    if (!result && col - 1 >= 0 && !m_verticalWalls[col][row] && !cellsVisited[row][col - 1]) {
        std::vector<int> leftCell;
        leftCell.push_back(row);
        leftCell.push_back(col - 1);
        result = solver(path,cellsVisited, leftCell, end);
    }
    // up
    if (!result && row - 1 >= 0 && !m_horizontalWalls[row][col] && !cellsVisited[row - 1][col]) {
        std::vector<int> upCell;
        upCell.push_back(row - 1);
        upCell.push_back(col);
        result = solver(path,cellsVisited, upCell, end);
    }
    // down
    if (!result && row + 1 < m_rows && !m_horizontalWalls[row + 1][col] && !cellsVisited[row + 1][col]) {
        std::vector<int> downCell;
        downCell.push_back(row + 1);
        downCell.push_back(col);
        result = solver(path,cellsVisited, downCell, end);
    }
    
    if (result) {
        return true;
    } else {
        path.pop_back(); // the current cell wasn't part of the solution
        return false;
    }
}

void Maze::display_ASCII(bool showSolution)
{
    std::cout << std::endl;
    for (int i = 0; i < 2 * m_rows + 1; i++)
    {
        if (i % 2 == 0)
        { // horizontal walls
            for (int k = 0; k < 2 * m_columns + 1; k++)
            {
                if (k % 2 == 0)
                    std::cout <<  m_wall_char;
                else {
                    switch (m_horizontalWalls[i/2][k/2]) {
                        case 0: // gap in the wall
                            if (showSolution)
                            {
                                if (i != 0 && i != 2 * m_rows)
                                {
                                    // check if cells above and below are part of solution
                                    if (m_solution[i/2][k/2] && m_solution[i/2 - 1][k/2])
                                        for (int s = 0; s < 3; s++)
                                            std::cout <<  m_soltn_char;
                                    else
                                        std::cout << "   ";
                                } else // top and bottom rows always part of solution if there's a gap
                                    for (int s = 0; s < 3; s++)
                                        std::cout <<  m_soltn_char;
                            } else
                                std::cout << "   ";
                            break;
                        case 1: // no gap in wall
                            std::cout << ' ' <<  m_wall_char << ' ';
                            break;
                    }
                }
            }
            std::cout << std::endl;
        } else
        { // vertical walls and inners of cell
            for (int n = 0; n < 2; n++) // two identical rows of characters must be printed
            {
                for (int j = 0; j < 2 * m_columns + 1; j++)
                {
                    if (j % 2 == 1) // prints the cells
                    {
                        if (showSolution && m_solution[i/2][j/2]) {
                            // cell is part of the solution path
                            for (int s = 0; s < 3; s++)
                                std::cout <<  m_soltn_char;
                        } else
                            std::cout << "   "; // blank space printed for all cells in maze
                    } else // prints vertical walls
                    {
                        switch (m_verticalWalls[j/2][i/2]) {
                            case 0: // gap in walls
                                if (showSolution)
                                {
                                    if (j != 0 && j != 2 * m_columns)
                                    {
                                        // check if cells left and right are part of solution
                                        if (m_solution[i/2][j/2] && m_solution[i/2][j/2 - 1])
                                            std::cout <<  m_soltn_char;
                                        else
                                            std::cout << " ";
                                    } else //gaps in far left and right walls of maze always part of solution
                                        std::cout << m_soltn_char;
                                } else
                                    std::cout << " ";
                                break;
                            case 1: // wall is there
                                std::cout <<  m_wall_char;
                                break;
                        }
                    }
                }
                std::cout << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

void Maze::display_image(bool showSolution)
{
    std::vector<uint8_t> image_vec;
    
    for (int i = 0; i < 2 * m_rows + 1; i++)
    {
        if (i % 2 == 0)
        { // horizontal walls
            for (int k = 0; k < 2 * m_columns + 1; k++)
            {
                if (k % 2 == 0)
                    image_vec.push_back(m_wall_color);
                else {
                    switch (m_horizontalWalls[i/2][k/2]) {
                        case 0: // gap in the wall
                            if (showSolution)
                            {
                                if (i != 0 && i != 2 * m_rows)
                                {
                                    // check if cells above and below are part of solution
                                    if (m_solution[i/2][k/2] && m_solution[i/2 - 1][k/2])
                                        image_vec.push_back(m_soltn_color);
                                    else
                                        image_vec.push_back(m_space_color);
                                } else // top and bottom rows always part of solution if there's a gap
                                    image_vec.push_back(m_soltn_color);
                            } else
                                image_vec.push_back(m_space_color);
                            break;
                        case 1: // no gap in wall
                            image_vec.push_back(m_wall_color);
                            break;
                    }
                }
            }
        } else
        { // vertical walls and inners of cell
            for (int j = 0; j < 2 * m_columns + 1; j++)
            {
                if (j % 2 == 1) // prints the cells
                {
                    if (showSolution && m_solution[i/2][j/2]) {
                        // cell is part of the solution path
                        image_vec.push_back(m_soltn_color);
                    } else
                        image_vec.push_back(m_space_color); // blank space printed for all cells in maze
                } else // prints vertical walls
                {
                    switch (m_verticalWalls[j/2][i/2]) {
                        case 0: // gap in walls
                            if (showSolution)
                            {
                                if (j != 0 && j != 2 * m_columns)
                                {
                                    // check if cells left and right are part of solution
                                    if (m_solution[i/2][j/2] && m_solution[i/2][j/2 - 1])
                                        image_vec.push_back(m_soltn_color);
                                    else
                                        image_vec.push_back(m_space_color);
                                } else //gaps in far left and right walls of maze always part of solution
                                    image_vec.push_back(m_soltn_color);
                            } else
                                image_vec.push_back(m_space_color);
                            break;
                        case 1: // wall is there
                            image_vec.push_back(m_wall_color);
                            break;
                    }
                }
            }
        }
    }
    
    cv::Mat imgVec(2 * m_rows + 1, 2 * m_columns + 1, CV_8U, image_vec.data());
    std::string windowName = "Maze image";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, imgVec);
    int k = cv::waitKey(0);
    if (k == 's') {
        cv::imwrite("/Users/natewebster/Desktop/maze_img.png", imgVec);
    }
    cv::destroyWindow(windowName);
    cv::waitKey(1);
}

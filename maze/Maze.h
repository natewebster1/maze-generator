//
//  Maze.h
//  maze
//
//  Created by Nate Webster on 8/31/21.
//

#ifndef Maze_h
#define Maze_h

#include <vector>
#include <string>

class Maze
{
public:
    Maze(int rows, int columns, std::string start, std::string end);
    void display(bool showSolution = false);
    bool solve(std::vector<std::vector<int>>& path, std::vector<std::vector<bool>> & cellsVisited, std::vector<int> start, std::vector<int> end);
    void display_solution();
private:
    int m_columns;
    int m_rows;
    std::vector<int> m_startCell;
    std::vector<int> m_endCell;
    
    std::string m_startPoint;
    std::string m_endPoint;
    
    std::vector<std::vector<int>> m_horizontalWalls; // [m_rows + 1][m_columns]
    std::vector<std::vector<int>> m_verticalWalls; // [m_columns + 1][m_rows]
    
    bool m_beenSolved;
    std::vector<std::vector<bool>> m_solution; // keeps track of which cells are part of solution path
};

#endif /* Maze_h */

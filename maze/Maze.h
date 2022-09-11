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
    Maze(int rows, int columns, std::string start, std::string end, char wall_char = 'X', char soltn_char = '`');
    void display(bool showSolution = false);
    void display_image(bool showSolution = false);
    void display_solution();
private:
    // Maze dimensions
    int m_columns;
    int m_rows;
        
    // Which characters the walls and solution path are drawn with
    char m_wall_char;
    char m_soltn_char;
    
    // Colors/Shades of the maze image
    uint8_t m_wall_color;
    uint8_t m_soltn_color;
    uint8_t m_space_color;
        
    // Used in generating the maze and solution
    std::vector<int> m_startCell;
    std::vector<int> m_endCell;
        
    // Where the maze starts/ends. Top, bottom, left, or right.
    std::string m_startPoint;
    std::string m_endPoint;
        
    // 0 if gap in wall, 1 if wall is there
    std::vector<std::vector<int>> m_horizontalWalls; // [m_rows + 1][m_columns]
    std::vector<std::vector<int>> m_verticalWalls; // [m_columns + 1][m_rows]
        
    bool m_beenSolved;
    std::vector<std::vector<bool>> m_solution; // keeps track of which cells are part of solution path
    void solve();
    bool solver(std::vector<std::vector<int>>& path, std::vector<std::vector<bool>> & cellsVisited, std::vector<int> start, std::vector<int> end);
};

#endif /* Maze_h */

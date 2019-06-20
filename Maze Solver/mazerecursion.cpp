//
//  mazerecursion.cpp
//  medium
//
//  Created by Ankush Bharadwaj on 5/10/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = 'H';     //H indicates where we've already been
    if (sr != 0 && maze[sr - 1][sc] != 'X' && maze[sr-1][sc] != 'H')   //NORTH
        if (pathExists(maze, sr -1, sc, er, ec))
            return true;
    if (sc != 9 && maze[sr][sc + 1] != 'X' && maze[sr][sc + 1] != 'H')   //EAST
        if (pathExists(maze, sr, sc + 1, er, ec))
            return true;
    if (sr != 9 && maze[sr + 1][sc] != 'X' && maze[sr+1][sc] != 'H')   //SOUTH
        if (pathExists(maze, sr +1, sc, er, ec))
            return true;
    if (sc != 0 && maze[sr][sc - 1] != 'X' && maze[sr][sc - 1] != 'H')   //WEST
        if (pathExists(maze, sr, sc - 1, er, ec))
            return true;
    return false;
}

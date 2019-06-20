//
//  mazequeue.cpp
//  hwk 2 part 1
//
//  Created by Ankush Bharadwaj on 4/30/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

//works

#include <iostream>
#include <queue>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise.

class Coord
{
public:
    Coord(int rr, int cc): m_r(rr), m_c(cc) {}
    int r() const { return m_r;}
    int c() const { return m_c;}
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue<Coord> coordqueue;
    Coord startpoint(sr,sc);
    coordqueue.push(startpoint);
    maze[sr][sc] = 'H';             // H marks that we've been there
    
    int r = sr;
    int c = sc;
    
    while(!coordqueue.empty())   // while queue is not empty
    {
        startpoint = coordqueue.front();
        r = startpoint.r();
        c = startpoint.c();
        coordqueue.pop();
        
        if(r == er && c == ec)
            return true;
        if(r != 9 && maze[r + 1][c] != 'X' && maze[r+1][c] != 'H') // move south
        {
            Coord move(r+1, c);
            coordqueue.push(move);
            maze[r+1][c] = 'H';     // we've visited the spot
        }
        if(r != 0 && maze[r][c-1] != 'X' && maze[r][c-1] != 'H') // move west
        {
            Coord move(r, c-1);
            coordqueue.push(move);
            maze[r][c-1] = 'H';     // we've visited the spot
        }
        if(r != 0 && maze[r-1][c] != 'X' && maze[r-1][c] != 'H') // move north
        {
            Coord move(r-1, c);
            coordqueue.push(move);
            maze[r-1][c] = 'H';     // we've visited the spot
        }
        if(c != 9 && maze[r][c+1] != 'X' && maze[r][c+1] != 'H') // move east
        {
            Coord move(r, c + 1);
            coordqueue.push(move);
            maze[r][c + 1] = 'H';   // we've visited the spot
        }
    }
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    if (pathExists(maze, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

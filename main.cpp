//Robert Miller and RJ Yarwood
#include <iostream>
#include "Sampler.h"
#include "DisjointSet.h"
#include "stack.h"
#include "pathfinder.h"


int encode(int r, int c, int d, int nr,int  nc) {
    return c + nc * (r + nr * d);
}

void decode(int e,int nr, int nc,int &d,int &row, int &col){

    col = e % nc;
    e /= nc;
    row = e % nr;
    d = e/nr;

}

int main() {

    Stack<int> S;

    int rows, columns, e, dir, cell, cellr, cellc, cell2r, cell2c, ext, wale;
    std::cin >> rows >> columns;

    uint8_t maze[50][50];


        for(int r=0; r < rows; r++){
            for(int c=0; c<columns; c++){
                maze[r][c] = 15;
            }
        }

    DisjointSet ds(rows*columns);
    Sampler sampler(4*rows*columns);

    int i=0;
    int sampleam = 0;


    while(i < (columns*rows) - 1){
        do {
            do {
                e = sampler.getSample();
                decode(e,rows,columns,dir,cellr,cellc);
                cell2r = cellr;
                cell2c = cellc;

                if((cellr == 0 && dir == 0) || ((cellr == rows-1) && dir ==2) || (cellc == 0 && dir == 3) || (cellc == columns -1 && dir == 1)) {
                    ext = 1;
                }
                else
                    ext = 0;

                if((maze[cellr][cellc] & (1 << dir)) != 0)
                    wale = 1;
                else
                    wale = 0;

                sampleam++;
            } while(ext == 1 || wale == 0);

            if(dir == 3){
                cell2c = cellc - 1;
            }
            else if (dir == 2){
                cell2r = cellr + 1;
            }
            else if(dir == 1){
                cell2c = cellc + 1;
            }
            else if(dir == 0) {
                cell2r = cellr - 1;
            }
        } while(ds.find(cellr * columns + cellc) == ds.find(cell2r * columns + cell2c));

        ds.join(cellr * columns + cellc, cell2r * columns + cell2c);


        if(dir == 0) {
            maze[cellr][cellc] &= ~WALL_UP;
            maze[cell2r][cell2c] &= ~WALL_DOWN;
        }
        else if (dir == 1){
            maze[cellr][cellc] &= ~WALL_RIGHT;
            maze[cell2r][cell2c] &= ~WALL_LEFT;
        }
        else if(dir == 2){
            maze[cellr][cellc] &= ~WALL_DOWN;
            maze[cell2r][cell2c] &= ~WALL_UP;
        }
        else if(dir == 3){
            maze[cellr][cellc] &= ~WALL_LEFT;
            maze[cell2r][cell2c] &= ~WALL_RIGHT;
        }

        i = i + 1;
    }


    S.push(encode(0,0,0,rows,columns));
    maze[0][0] |= VISITED;
    int c,r,d, cp, rp, count = 0;
    bool isVisited;
    while(true){
        e = S.peek();

        decode(e,rows,columns,d,r,c);

        cp = c;
        rp = r;

        if(r == rows-1 && c == columns-1){
            break;
        }

        if(d==4){
            maze[r][c] |= DEAD_END;
            S.pop();
        }
        else {
            if (d == 3) {
                cp = c - 1;
            } else if (d == 2) {
                rp = r + 1;
            } else if (d == 1) {
                cp = c + 1;
            } else if (d == 0) {
                rp = r - 1;
            }

            S.pop();
            e = encode(r,c,d+1,rows,columns);
            S.push(e);

            if ((maze[r][c] & (1<< d)) == 0 && (maze[rp][cp]&VISITED) == 0) {
                S.push(encode(rp, cp, 0,rows, columns));
                maze[rp][cp] |= VISITED;
            }
        }

        count++;

    }    int size;


    printMaze(maze,rows,columns);
}












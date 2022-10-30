// DFS maze solver
// Lab 07
// Namita Patel (z5309731@ad.unsw.edu.au), Date submitted: 30-10-2022

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"
typedef enum {
	NONE,
	VISITED,
	PATH,
	
 } State;
 
  bool isvalid(Maze m, Cell V) {
  	int Height = MazeHeight(m);
  	int Width = MazeWidth(m);
  	// if within bounds
  	if (V.row < Height && V.row >= 0 && V.col < Width && V.col >= 0 && MazeIsWall(m,V) == false) {
  		return true;
  		
  		}
  		else {
  			return false;
  		}
  		
  }
  bool adjacent (Maze m, Cell V, Cell W) {
  	Cell Left = {V.row, V.col-1};
  	Cell Right = {V.row, V.col+1};
  	Cell Up = {V.row+1, V.col};
  	Cell Down = {V.row-1, V.col};
  	if(isvalid(m,W) == true && isvalid(m,V)) {
  		if(isvalid(m,Left) == true) {
  			if(Left.row == W.row && Left.col == W.col) {
  			return true;
  		}
  	}
  	if(isvalid(m,Right) == true) {
  		if(Right.row == W.row && Right.col == W.col) {
  			return true;
  			
  			}
  			
  			
  	}
  	
  	
  	if(isvalid(m,Up) == true) {
  	   if(Up.row == W.row && Up.col == W.col) {
  	   return true;
  	   
  	   }
  	   
  }
  if (isvalid(m,Down) == true) {
  	if(Down.row == W.row && Down.col == W.col) {
  		return true;
  		
  	}
    }
}

	return false;
}

Cell ReturnCell(int row, int col) {
	Cell x = {.row = row, .col = col};
	return x;
	
  }

bool dfsPathCheck(Maze m, Cell V, Cell **predecessormatrix, bool **boolmatrix) {
	MazeVisit(m,V);
	boolmatrix[V.row][V.col] = VISITED;
	Cell W;
	
	for (int row = 0; row < MazeHeight(m); row++) {
		for(int col = 0; col < MazeWidth(m); col++) {
		
		W = ReturnCell(row,col);
		if (adjacent(m,V,W) == true) {
		
		// if reached destination
		if (MazeVisit(m,W) == true) {
			MazeMarkPath(m,W);
			predecessormatrix[W.row][W.col] = V;
			Cell Start = MazeGetStart(m);
			while(W.row != Start.row || W.col != Start.col) {
			MazeMarkPath(m,W);
			W = predecessormatrix[W.row][W.col];
			
		}
		
		MazeMarkPath(m,Start);
		return true;
		
	}
	
	// if not visited
	else if (boolmatrix[W.row][W.col] == NONE) {
		predecessormatrix[W.row][W.col] = V;
		if(dfsPathCheck(m,W,predecessormatrix, boolmatrix) == true) {
		return true;
		
		}
		
		}
	}

   }
   
}

return false;
}

bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    
    bool found = false;
    bool **boolmatrix = createBoolMatrix(MazeHeight(m), MazeWidth(m));
    
    Cell **predecessormatrix = createCellMatrix(MazeHeight(m), MazeWidth(m));
    Cell Start = MazeGetStart(m);
    
    found = dfsPathCheck(m, Start, predecessormatrix, boolmatrix);
    
    
    
    freeCellMatrix(predecessormatrix);
    freeBoolMatrix(boolmatrix);
    
    return found;
 }
    
    


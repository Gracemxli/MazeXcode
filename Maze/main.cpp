/*
maze.cpp
*/

#include <iostream>
#include "mazio.hpp"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// Add other prototypes here for any functions you wish to use

int mainX(int argc, char* argv[]) {
   // create some locations;
   Location three_one, two_two;
   three_one.row = 3; three_one.col = 1;
   two_two.row = 2; two_two.col = 2;

   // create an Queue with max capacity 5
   Queue q(5);

   cout << boolalpha;
   cout << q.is_empty() << endl;           // true
   q.add_to_back(three_one);
   cout << q.is_empty() << endl;           // false
   q.add_to_back(two_two);

   Location loc = q.remove_from_front();
   cout << loc.row << " " << loc.col << endl; // 3 1
   loc = q.remove_from_front();
   cout << loc.row << " " << loc.col << endl; // 2 2
   cout << q.is_empty() << endl;           // true
    return 0;
}


// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }

    mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1
    // Test
    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.



    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.
    maze_search(mymaze, rows, cols);
    print_maze(mymaze, rows, cols);
    

    //================================
    // ADD CODE BELOW
    // to delete all memory that read_maze allocated: CHECKPOINT 2

    for(int i = 0; i<rows; i++){
        delete [] mymaze[i];
    }
    delete [] mymaze;
    

    return 0;
}

void pred_print(Location* pred, int rows, int cols) {
    for (int r=0, i=0; r<rows; r++)
        for (int c=0; c<cols; c++, i++) {
            cout << " " << pred[i].row << ":" << pred[i].col;
        }  cout << endl;
    cout << endl;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
    // *** You complete **** CHECKPOINT 4
    int scount=0, fcount =0;
    Location sLoc, fLoc;
    for(int i = 0; i<rows; i++){
        for(int j =0; j<cols; j++){
            char m=  maze[i][j];
            if(m!='*'&&m!='S'&&m!='.'&&m!='F'&&m!='#'){
                return -1;
            }
            if(m=='S'){
                scount++;
                sLoc.row=i;
                sLoc.col=j;
            }
            if(m=='F'){
                fcount++;
                fLoc.row=i;
                fLoc.col=j;
            }
        }
    }
    
    if(scount!=1||fcount!=1){
        return -1;
    }
    
    Queue q(rows*cols);

    // precessor & visited
    // 5 x 5 0,0 <- (0,1)
    // processor = new Location[rows*cols] (3,2) => 3*cols+2
    // 5 row*10 col => 4th row 9th col => 4*10+9
    
    Location* pred = new Location[rows*cols];
    int* visited = new int[rows*cols];
    for(int i=0; i<rows*cols;i++){
        pred[i].row= -1;
        pred[i].col= -1;
        visited[i]=0;
    }
/*
 mark the start location as explored
 add start location to q

 while q is not empty do:
   set loc = extract the item from the front of q
   for each neighbor (i.e., N,W,S, and E) of loc do:
     if the neighbor is valid, open, and not yet explored do:
       mark the neighbor as explored
       add the neighbor to the back of q
       set predecessor of the neighbor = loc
 
 */
    visited[sLoc.row*cols+sLoc.col]=1;
    q.add_to_back(sLoc);

    while(!q.is_empty()){
        Location loc = q.remove_from_front();
        // N
        if(loc.row!=0){
            Location north = loc; north.row--;
            char find = maze[north.row][north.col];
            int vis = visited[north.row*cols + north.col];
            if (vis==0 && find!='#') {
                pred[north.row*cols+north.col]=loc;
                if(find=='.') {
                    q.add_to_back(north);
                } else if(find=='F'){
                    break;
                }
            }
        }
        // W
        if(loc.col!=0){
            Location west = loc; west.col--;
            char find = maze[west.row][west.col];
            int vis = visited[west.row*cols + west.col];
            if (vis==0 && find!='#') {
                pred[west.row*cols+west.col]=loc;
                if(find=='.') {
                    q.add_to_back(west);
                } else if(find=='F'){
                    break;
                }
            }
        }
        // S
        if(loc.row!=rows-1){
            Location south = loc; south.row++;
            char find = maze[south.row][south.col];
            int vis = visited[south.row*cols + south.col];
            if (vis==0 && find!='#') {
                pred[south.row*cols+south.col]=loc;
                if(find=='.') {
                    q.add_to_back(south);
                } else if(find=='F'){
                    break;
                }
            }
        }
        // E
        if(loc.col!=cols-1){
            Location east = loc; east.col++;
            char find = maze[east.row][east.col];
            int vis = visited[east.row*cols + east.col];
            if (vis==0 && find!='#') {
                pred[east.row*cols+east.col]=loc;
                if(find=='.') {
                    q.add_to_back(east);
                } else if(find=='F'){
                    break;
                }
            }
        }
    }
    int result= 0;

    if (pred[fLoc.row*cols+fLoc.col].row!=-1) {
        Location prev = pred[fLoc.row*cols+fLoc.col];
        while(prev.row!=sLoc.row&&prev.col!=sLoc.col){
            // '*'
            maze[prev.row][prev.col]='*';
            prev=pred[prev.row*cols+prev.col];
        }
        result=1;
    }
    
    delete [] pred;
    delete [] visited;
    return result; // DELETE this stub, it's just for Checkpoint 1 to compile.
}

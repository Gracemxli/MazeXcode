/*
 mazeio.cpp
 */

#include <iostream>
#include <fstream>
#include "mazio.hpp"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{
    
    // *** You complete **** CHECKPOINT 1
    int row, col;
    // *** You complete **** CHECKPOINT 1
    ifstream ifile(filename);
    
    if( ifile.fail() ){ // able to open file?
        return NULL;
    }
    ifile >> row >> col;
    if ( ifile.fail() ){
        return NULL;
    }
    //rows=&row;
    *rows=row;
    *cols=col;
    
    char** array = new char*[row];
    char buf[col+1];
    // skip the empty line
    ifile.getline(buf, col+1);
    if (buf[0]!='\0') {
        cout << "Bug?\n";
    }
    for(int i = 0; i<row; i++){
        array[i]=new char[col+1];
        ifile.getline(array[i], col+1);
    }

    ifile.close();

    return array;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{
    
    // *** You complete **** CHECKPOINT 1
    
    for(int i = 0; i<rows; i++){
        cout << maze[i] << endl;
    }
        
    
    
    
}


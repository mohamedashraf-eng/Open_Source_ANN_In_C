/*
    Author: Mohamed Wx
    Date: 6/13/2022
    Why : This c file contains the global general use functions.
*/
//=============================> .START
//=============================> .INC
#include "Global.h"
//=============================> .STRUCT

Privates_t private = {.range = 100, .factor = 0.1332, .randoming = true};

//=============================> .FUNC

// Function to make a vector in heap.
Type_t *create_vector(const uint16_t vector_len, bool init)
{
    // Check if the input length isn't valid.
    if(vector_len <= 0)
    {printf("\n GLOBAL.H|ERROR. VECTOR[LEN] invalid"); exit(-1);}

    // Check if input length is greater than the max allowed.
    if(vector_len > MAX_VECTOR_LEN)
    {printf("\n GLOBAL.H|ERROR. vector_len > MAX_VECTOR_LEN.\n"); exit(-1);}
   
    // Create vector in the heap.
    Type_t *new_vector = (Type_t *) malloc(sizeof(Type_t));

    // Modify the new vector parameters.
    // Vector length.
    new_vector->Vector_t.len = vector_len;
    // Vector array.
    new_vector->Vector_t.Vector = (float *) malloc(sizeof(float) * new_vector->Vector_t.len);

    // Initialize the new vector.
    init ? 
        vector_init(new_vector) : false;

    // Return the created vector.
    return new_vector; 
}//end create_vector.

//====================================> [MAIN FUNCTIONS]

// Function to create matrix in heap.
/*
- Heap visual view:
    nROWS
    [0]=>[0]->[1]->..[m] mCOLS
    [1]=>[0]->[1]->..[m] mCOLS
    [2]=>[0]->[1]->..[m] mCOLS
    .
    .
    [n]=>[0]->[1]->..[m] mCOLS
*/
Type_t *create_matrix(const uint16_t row, const uint16_t col, bool init)
{
    // Error Handler.
    // Check if row & col are valid.
    if( (row <= 0) || (col <= 0) )
    {printf("\n GLOBAL.C|ERROR. ROW_COL: Invalid\n"); exit(-1);}
    // assert(row > 0); assert(col > 0); // For strictly exit.

    // Check if row & col > MAX.
    if( (row > MAX_MATRIX_ROW) || (col > MAX_MATRIX_COL) )
    {printf("\n GLOBAL.C|ERROR. ROW_COL > MAX_LENGTH.\n"); exit(-1);}
    // assert(row < MAX_MATRIX_ROW); assert(col < MAX_MATRIX_COL); // For strictly exit.

    // Create the matrix struct
    Type_t *new_matrix = (Type_t *) malloc(sizeof(Type_t));

    // Set the matrix parameters.
    new_matrix->Matrix_t.row = row;
    new_matrix->Matrix_t.col = col;

    //printf("\n col: %d", new_matrix->Matrix_t.col);
    //printf("\n row: %d", new_matrix->Matrix_t.row);

    // Allocating the 2d array in heap (matrix)
    new_matrix->Matrix_t.Matrix = (float **) malloc(sizeof(float **) * new_matrix->Matrix_t.row);

    // Start creating the links.
    for(uint16_t i = 0; i < new_matrix->Matrix_t.row; i++)
    {   
        // Allocating N Links (N=col).
        new_matrix->Matrix_t.Matrix[i] = (float *) malloc(sizeof(float) * new_matrix->Matrix_t.col);
    }

    // Initalize the new matrix.
    init ? 
        matrix_init(new_matrix) : false;

    // Return the allocated matrix.
    return new_matrix;

}//end create_matrix.


// Function to initalzie an array.
void vector_init(Type_t *vector)
{
    // Error Handler.
    // Check if vector struct is valid.
    if(vector == NULL)
    {printf("\n GLOBAL.H|ERROR. Vector: NULL.\n"); exit(-1);}
    // assert(vector != NULL); // For strictly exit.

    // Check if vector data is valid.
    if(vector->Vector_t.Vector == NULL)
    {printf("\n GLOBAL.H|ERROR. Vector[LEN]: NULL.\n"); exit(-1);}
    // assert(vector->Vector_t.Vector != NULL); // For Strictly exit.

    // Check if vector length isn't valid.
    if(vector->Vector_t.len <= 0)
    {printf("\n GLOBAL.H|ERROR. Vector_LEN invalid.\n"); exit(-1);}
    // assert(vector->Vector_t.len > 0) // For strictly exit.

    // Init the array.
    if(private.randoming == true)
        srand(time(NULL));

    for(uint16_t i = 0; i < vector->Vector_t.len; i++)
    {
        vector->Vector_t.Vector[i] = rand()%private.range * private.factor;
    }
    
    return;
}//end vector_init.

// Function to init a matrix. (float)
void matrix_init(Type_t *matrix)
{
    // Error Handler.
    // Check if matrix struct isn't valid.
    if(matrix == NULL)
    {printf("\n GLOBAL.H|ERROR. Matrix: NULL.\n"); exit(-1);}
    // assert(matrix != NULL) // For strictly exit.

    // Check if matrix data is valid.
    if(matrix->Matrix_t.Matrix == NULL)
    {printf("\n GLOBAL.H|ERROR. Matrix[col][row]: NULL.\n"); exit(-1);}
    // assert(matrix->Matrix_t.Matrix != NULL) // For strictly exit.

    // Check matrix elements.
    if( (matrix->Matrix_t.row <= 0) || (matrix->Matrix_t.col <= 0) )
    {printf("\n GLOBAL.H|ERROR. Matrix_COL_ROW invalid.\n"); exit(-1);}
    // assert(matrix->Matrix_t.row > 0); assert(matrix->Matrix_t.col > 0);  // For strictly exit.

    // Init the matrix.
    if(private.randoming == true)
        srand(time(NULL));

    for(uint16_t i = 0; i < matrix->Matrix_t.row; i++)
    {
        for(uint16_t j = 0; j < matrix->Matrix_t.col ; j++)
        {
            matrix->Matrix_t.Matrix[i][j] = rand()%private.range * private.factor;
        }
    }

    return;
}//end matrix_init.

//====================================> [SUB FUNCTIONS]

// Function to print vector. (float)
void print_vector(Type_t *vector)
{
    // Error Handler.
    // Check if vector struct is valid.
    if(vector == NULL)
    {printf("\n GLOBAL.H|ERROR. Vector: NULL.\n"); exit(-1);}
    // assert(vector != NULL); // For strictly exit.

    // Check if vector data is valid.
    if(vector->Vector_t.Vector == NULL)
    {printf("\n GLOBAL.H|ERROR. Vector[LEN]: NULL.\n"); exit(-1);}
    // assert(vector->Vector_t.Vector != NULL); // For Strictly exit.

    // Check if vector length isn't valid.
    if(vector->Vector_t.len <= 0)
    {printf("\n GLOBAL.H|ERROR. Vector_LEN invalid.\n"); exit(-1);}
    // assert(vector->Vector_t.len > 0) // For strictly exit.

    // Print the vector.
    for(uint16_t i = 0; i < vector->Vector_t.len; i++)
    {
        printf("\n%.3f", vector->Vector_t.Vector[i]);
    }
    
    printf("\n");
    return;
}//end print_vector.

// Function to print matrix. (float)
void print_matrix(Type_t *matrix)
{
    // Error Handler.
    // Check if matrix struct isn't valid.
    if(matrix == NULL)
    {printf("\n GLOBAL.H|ERROR. Matrix: NULL.\n"); exit(-1);}
    // assert(matrix != NULL) // For strictly exit.

    // Check if matrix data is valid.
    if(matrix->Matrix_t.Matrix == NULL)
    {printf("\n GLOBAL.H|ERROR. Matrix[col][row]: NULL.\n"); exit(-1);}
    // assert(matrix->Matrix_t.Matrix != NULL) // For strictly exit.

    // Check matrix elements.
    if( (matrix->Matrix_t.row <= 0) || (matrix->Matrix_t.col <= 0) )
    {printf("\n GLOBAL.H|ERROR. Matrix_COL_ROW invalid.\n"); exit(-1);}
    // assert(matrix->Matrix_t.row > 0); assert(matrix->Matrix_t.col > 0);  // For strictly exit.

    // Init the matrix.
    if(private.randoming == true)
        srand(time(NULL));

    for(uint16_t i = 0; i < matrix->Matrix_t.row; i++)
    {
        for(uint16_t j = 0; j < matrix->Matrix_t.col ; j++)
        {
            printf("%.3f ", matrix->Matrix_t.Matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    return;
}//end print_matrix.

// Function to free heap vector.
void free_vector(Type_t *vector)
{
    // Error Handeling.
    // Check if vector struct is valid.
    if(vector == NULL)
    {printf("\n GLOBAL.C|ERROR. FREE_VEC: NULL\n"); exit(-1);}
    // assert(vector != NULL); // For strictly exit.

    // Check if vector data is valid.
    if(vector->Vector_t.Vector == NULL)
    {printf("\n GLOBAL.C|ERROR. FREE_VEC[LEN]: NULL\n"); exit(-1);}
    // assert(vector->Vector_t.Vector != NULL); // For strictly exit.

    // Check if length is valid.
    if(vector->Vector_t.len <= 0)
    {printf("\n GLOBAL.C|ERROR. FREE_VEC_LEN: Invalid\n"); exit(-1);}
    // assert(vector->Vector_t.len > 0); // For strictly exit.

    // Free the vector.
    free(vector->Vector_t.Vector);
    // Free the struct.
    free(vector);

    // Indicator message.
    //printf("\n VECTOR_FREE: SUCCESSFUL\n");
    
    return;
}//end free_vector.

// Function to free heap matrix.
void free_matrix(Type_t *matrix)
{
    // Error Handeling.
    // Check if matrix struct is valid.
    if(matrix == NULL)
    {printf("\n GLOBAL.C|ERROR. FREE_MATRIX: NULL\n"); exit(-1);}
    // assert(matrix != NULL); // For strictly exit.

    // Check the matrix data.
    if(matrix->Matrix_t.Matrix == NULL)
    {printf("\n GLOBAL.C|ERROR. FREE_MATRIX[row][col]: NULL\n"); exit(-1);}
    // assert(matrix->Matrix_t.Matrix != NULL); // For strictly exit.

    // Check the matrix parameters.
    if( (matrix->Matrix_t.row <= 0) || (matrix->Matrix_t.col <= 0) )
    {printf("\n GLOBAL.C|ERROR. FREE_MATRIX_COL_ROW: Invalid\n"); exit(-1);}
    // assert(matrix->Matrix_t.row > 0); assert(matrix->Matrix_t.col > 0); // For strictly exit.
    
    // Free the heap matrix.
    for(uint16_t i = 0; i < matrix->Matrix_t.row; i++) 
    {
        // Free the mCOLS pointers.
        free(matrix->Matrix_t.Matrix[i]);
    }
    // Free the nROWS double pointers.
    free(matrix->Matrix_t.Matrix);

    // Free the struct.
    free(matrix);

    // Indicator message.
    //printf("\n MATRIX_FREE: SUCCESSFUL\n");

    return;
}//end free_matrix.

//=============================> .END
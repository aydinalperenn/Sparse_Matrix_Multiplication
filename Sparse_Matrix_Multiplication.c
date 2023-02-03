/*
    Alperen Aydın

 */

 /*                         !!!!!!!!!!!!!!!!!!!  IMPORTANT NOTE  !!!!!!!!!!!!!!!!!!!!
                 IF YOU WANT TO CHANGE MATRICES, YOU HAVE TO CHANGE DEFINED K,L AND M; AND ALSO THE MATRICES
 */

 //  C program which multiplies two sparse matrices

#include <stdio.h>

#define MAX_TERM 101
#define K 4     // Rows Number of 2dMatrix1
#define L 4     // Columns Number of 2dMatrix1 && Rows Number of 2dMatrix2
#define M 4     // Columns Number of 2dMatrix2

//  ------------------- Defines that are above are taken from assignment.pdf----------------------------


struct matrix {
    int row;
    int column;
    int value;
};



//  Functions

void print(struct matrix sparseMatrix[MAX_TERM], int count) {       // print matrix to output
    printf("Sparse Matrix Multiplication:\nRow\tColumn\tValue\n");
    for (int i = 0; i <= count; i++) {

        // if-else is for output like pdf [For ex: (row,column) = (1,1) instead of (0,0); because array index starts from 0]
        if (i != 0) {
            printf("%d\t %d\t %d \n", sparseMatrix[i].row + 1, sparseMatrix[i].column + 1, sparseMatrix[i].value);
        }
        else {
            printf("%d\t %d\t %d \n", sparseMatrix[i].row, sparseMatrix[i].column, sparseMatrix[i].value);
        }

    }
}


// Sorting Function Blocks
void swap(struct matrix sparseMatrix[], int j) {

    int temp;

    //  For Rows
    temp = sparseMatrix[j].row;
    sparseMatrix[j].row = sparseMatrix[j - 1].row;
    sparseMatrix[j - 1].row = temp;

    //  For Columns
    temp = sparseMatrix[j].column;
    sparseMatrix[j].column = sparseMatrix[j - 1].column;
    sparseMatrix[j - 1].column = temp;

    //  For Values
    temp = sparseMatrix[j].value;
    sparseMatrix[j].value = sparseMatrix[j - 1].value;
    sparseMatrix[j - 1].value = temp;

}

void insertionSort(struct matrix sparseMatrix[], int size) {

    // Sorting algorithm called "Insertion Sort" working on transposed SparseMatrix according to row index

    /*
       Referenced from https://www.geeksforgeeks.org/insertion-sort/            For theoric Information
       Referenced from https://www.youtube.com/watch?v=XMSJuEPE_LM&list=PLOsYO8J5EH_txthUirEEYlCEowJDm70Hw&index=32     For Coding
    */


    for (int i = 2; i < size + 1; i++) {
        for (int j = i; j > 1; j--) {
            if ((sparseMatrix[j].row < sparseMatrix[j - 1].row) && sparseMatrix[j].value != 0) {      //  Swap according to Row index
                swap(sparseMatrix, j);
            }
            else if ((sparseMatrix[j].row == sparseMatrix[j - 1].row) && (sparseMatrix[j].value != 0)) {      // If row indexes are the same, then swap according to Col index
                if (sparseMatrix[j].column < sparseMatrix[j - 1].column) {
                    swap(sparseMatrix, j);
                }
            }
        }
    }



}

void setSparseMatrix(int row, int column, int twoDimensionalMatrix[][column], struct matrix sparseMatrix[]) {

    //  Making of SparseMatrix from twoDimensionalMatrix

    int numberOfValue = 0;                        // defined how many value contained
    sparseMatrix[0].row = row;                  // defined number of twoDimensionalMatrix's rows
    sparseMatrix[0].column = column;            // defined number of twoDimensionalMatrix's columns
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (twoDimensionalMatrix[i][j] != 0) {
                numberOfValue++;
                sparseMatrix[numberOfValue].row = i;
                sparseMatrix[numberOfValue].column = j;
                sparseMatrix[numberOfValue].value = twoDimensionalMatrix[i][j];
            }
        }
    }
    sparseMatrix[0].value = numberOfValue;
}

void transpose(struct matrix sparseMatrix[]) {


    // A function which make transpose of 2nd matrix came from multiply function
    struct matrix temp[MAX_TERM];


    for (int index = 0; sparseMatrix[index].value != 0; index++) {     // Copy matrix from sparseMatrix to temp
        temp[index].row = sparseMatrix[index].row;
        temp[index].column = sparseMatrix[index].column;
        temp[index].value = sparseMatrix[index].value;

        sparseMatrix[index].row = NULL;
        sparseMatrix[index].column = NULL;
        sparseMatrix[index].value = NULL;
    }


    // Make transpose

    for (int index = 0; temp[index].value != 0; index++) {
        ğ
            sparseMatrix[index].row = temp[index].column;
        sparseMatrix[index].column = temp[index].row;
        sparseMatrix[index].value = temp[index].value;
    }


    //Sorting according to row index
    insertionSort(sparseMatrix, sparseMatrix[0].value);


}


void multiply(struct matrix sparseMatrix1[], struct matrix sparseMatrix2[]) {

    // A function which Multiply two Sparse Matrix

    transpose(sparseMatrix2);


    struct matrix resultMatrix[MAX_TERM];   // defined result matrix

    resultMatrix[0].row = K;        //Assignment of Row number in resultMatrix
    resultMatrix[0].column = M;     //Assignment of Col number in resultMatrix



    // All of belows are for multiply 2 Sparse matrix

    int numberOfValue = 0;      // number of resultmatrix[0].value

    int rowResult = 0;
    int colResult = 0;
    int indexResult = 1;

    int total = 0;

    int indexForWhile = resultMatrix[0].row * resultMatrix[0].column;

    while (indexForWhile > 0) {    // For every i,j combinations

        for (int indexForSparse1 = 1; indexForSparse1 < sparseMatrix1[0].value + 1; indexForSparse1++) {

            if ((sparseMatrix1[indexForSparse1].row == rowResult) && (sparseMatrix1[indexForSparse1].value != 0)) {

                for (int indexForSparse2 = 1; indexForSparse2 < sparseMatrix2[0].value + 1; indexForSparse2++) {

                    if ((sparseMatrix2[indexForSparse2].value != 0) && (sparseMatrix1[indexForSparse1].column == sparseMatrix2[indexForSparse2].column) && (sparseMatrix2[indexForSparse2].row == colResult)) {
                        total += sparseMatrix1[indexForSparse1].value * sparseMatrix2[indexForSparse2].value;
                        break;
                    }

                }
            }

        }

        if (total != 0) {
            resultMatrix[indexResult].row = rowResult;
            resultMatrix[indexResult].column = colResult;
            resultMatrix[indexResult].value = total;

            total = 0;
            numberOfValue++;
            indexResult++;
        }



        colResult++;
        if (colResult == resultMatrix[0].column) {
            colResult = 0;
            rowResult++;
        }

        indexForWhile--;
    }

    resultMatrix[0].value = numberOfValue;

    print(resultMatrix, resultMatrix[0].value);

}



int main() {

    int twoDimensionalMatrix1[K][L] = {             // defined 2D Matrix1
            {0,10,0,5},
            {0,2,4,0},
            {0,0,0,0},
            {3,0,0,7}

    };
    struct matrix sparseMatrix1[MAX_TERM];          // defined Sparse Matrix1
    setSparseMatrix(K, L, twoDimensionalMatrix1, sparseMatrix1);       // Make sparseMatrix1 from 2dArray1


    int twoDimensionalMatrix2[L][M] = {             // defined 2D Matrix2
            {1,0,0,2,},
            {0,0,3,0},
            {0,8,0,0},
            {5,0,10,0}

    };
    struct matrix sparseMatrix2[MAX_TERM];          // defined Sparse Matrix2
    setSparseMatrix(L, M, twoDimensionalMatrix2, sparseMatrix2);       // Make SparseMatrix2 from 2dArray2

    multiply(sparseMatrix1, sparseMatrix2);


    return 0;
}

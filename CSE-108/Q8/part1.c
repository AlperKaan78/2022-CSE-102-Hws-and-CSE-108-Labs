#include <stdio.h>

typedef struct 
{
    double matrix[3][3];
    double determinant;
} matrix_t;


void print_matrix(matrix_t initial_matrix);

void inverse_matrix(matrix_t* initial_matrix, matrix_t* inverted_matrix);

void determinant_of_matrix(matrix_t* initial_matrix);



int main()
{
    matrix_t myMatrix = {
        {{1.0000, 0.9134, 0.2785},{0.9058, 0.6324, 0.5469 },{0.1270, 0.0975, 0.9575}},
        0.0
    };
    matrix_t invrsMatrix;
    print_matrix(myMatrix);
    inverse_matrix(&myMatrix,&invrsMatrix);

    return 0;
}

void print_matrix(matrix_t initial_matrix)
{
    for(int k = 0; k<3; k++)
    {
        for(int i = 0; i<3; i++)
        {
            printf("%.4lf ",initial_matrix.matrix[k][i]);
        }
        printf("\n");
    } 
}

void inverse_matrix(matrix_t* initial_matrix, matrix_t* inverted_matrix)
{
    determinant_of_matrix(initial_matrix);
    double det = initial_matrix->determinant;
    if(det == 0)
    {
        printf("your matrix can not be inverted\n");
    }
    else{
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                inverted_matrix->matrix[i][j] = (
                    (initial_matrix->matrix[(j+1)%3][(i+1)%3] * initial_matrix->matrix[(j+2)%3][(i+2)%3]) -
                    (initial_matrix->matrix[(j+1)%3][(i+2)%3] * initial_matrix->matrix[(j+2)%3][(i+1)%3])
                    ) / det;
            }
        }
        print_matrix(*inverted_matrix);
    }
}



void determinant_of_matrix(matrix_t* initial_matrix)
{
    initial_matrix->determinant = initial_matrix->matrix[0][0]*(initial_matrix->matrix[1][1]*initial_matrix->matrix[2][2] - initial_matrix->matrix[1][2]*initial_matrix->matrix[2][1])
                        - initial_matrix->matrix[0][1]*(initial_matrix->matrix[1][0]*initial_matrix->matrix[2][2] - initial_matrix->matrix[1][2]*initial_matrix->matrix[2][0])
                        + initial_matrix->matrix[0][2]*(initial_matrix->matrix[1][0]*initial_matrix->matrix[2][1] - initial_matrix->matrix[1][1]*initial_matrix->matrix[2][0]);
    printf("%lf\n", initial_matrix->determinant);                                
}

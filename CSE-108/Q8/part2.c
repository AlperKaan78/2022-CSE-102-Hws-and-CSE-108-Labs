#include<stdio.h>
#include<math.h>
#include<stdlib.h>


typedef struct 
{
    double x,y,z;
    
}vector_t;

double find_orthogonal(vector_t vec_1, vector_t vec_2, vector_t* output_vec);
double lenght_of_vector(vector_t vec);

int main()
{
    vector_t vec_1, vec_2,output_vec;

    vec_1.x = 2; vec_1.y = 3; vec_1.x = 5 ;
    vec_2.x = 6; vec_2.y = 5; vec_2.x = 6;

    
    double angle = find_orthogonal(vec_1,vec_2,&output_vec);
    printf("%.4lf",angle);



    return 0;
}

double find_orthogonal(vector_t vec_1, vector_t vec_2, vector_t* output_vec)
{
    double dotProduct; 
    double angle;
    double len1 = length_of_vector(vec_1);
    double len2 = length_of_vector(vec_2);

    if (len1 == 0 || len2 == 0) {
        printf("Error: One or both input vectors have zero length.\n");
        return 0;
    }

    dotProduct = (vec_1.x * vec_2.x) +(vec_1.y*vec_2.y) + (vec_1.z*vec_2.z);
    angle = dotProduct / (len1 * len2);
    angle = acos(angle);
    printf("%lf",angle);
    return angle;
}



double lenght_of_vector(vector_t vec)
{
    double lenght = sqrt(vec.x * vec.x + vec.y * vec.y +vec.z * vec.z);
    return lenght;
}
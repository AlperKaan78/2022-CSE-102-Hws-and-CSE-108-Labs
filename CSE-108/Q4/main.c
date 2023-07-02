#include<stdio.h>

void generateShapeFile();
void drawSquare(int);
void drawTriangle(int);


void main()
{
    char shape;
    int size;
    int selection;
    int isFirstSelected = 0;
    int terminateTheProgram = 0;

    while(!terminateTheProgram)
    {
        printf("Welcome to Shape Reader! Please make your choice to continue:\n");
        printf("1-Generate a shape file.\n");
        printf("2-Read and Draw a shape file.\n");
        printf("3-Terminate the program.\n");
        scanf(" %d",&selection);

        switch (selection)
        {
        case 1:
            generateShapeFile();
            isFirstSelected = 1;
            break;
        case 2:
            if(isFirstSelected)
            {
                FILE *shapes;
                shapes  = fopen("shapes.txt","r");
				while(fscanf(shapes,"%c,%d%*c",&shape,&size) == 2) {
                    if (shape == 't') {
                        drawTriangle(size);
                    }
                    else if(shape == 's'){
                        drawSquare(size);
                    }
                }
            }
			else
			{
				printf("First, you must generate the file and enter the shapes and sizes.\n");
			}
            break;
        case 3:
            terminateTheProgram = 1;
            break;
        default:
            printf("Invalid Selection! Try again.\n");
            break;
        }

    }
}

void generateShapeFile()
{
    char shape_type;
    int size;

    FILE *shapeFile;
    shapeFile = fopen("shapes.txt","w");

    printf("Enter shape and then enter size: \n");
    while(1) {
        printf("Enter shape type (s for square, t for triangle), or 'e' to end: ");
        scanf(" %c", &shape_type);

        if(shape_type == 'e') {
            break;
        }

        printf("Enter size (between 3 and 10): ");
        scanf("%d", &size);

        if(shape_type != 's' && shape_type != 't' || size < 3 || size > 10) {
            printf("Invalid input.\n");
            continue;
        }

        fprintf(shapeFile, "%c,%d\n", shape_type, size);
    }

    fclose(shapeFile);


}

void drawSquare(int size)
{
    for(int a = 1; a<=size; ++a)
    {
        for(int k =1; k<=size; ++k)
        {
            if(a == 1 || a ==size)
            {
                printf("* ");
            }
            else
            {
                if(k ==1 || k == size)
                {
                    printf("* ");
                }
                else
                    printf("  ");
            }
        }
        printf("\n");
    }

}
void drawTriangle(int size) {
    int row, col;

    for (row = 0; row < size; row++) {

        for (col = 0; col < (2*size-1); col++) {

            if (col >= (size-1)-row && col <= (size-1)+row) {

                if (col == (size-1)-row || col == (size-1)+row || row == size-1) {
                    printf("*");
                }
				else {
                    printf(" ");
                }
            } 
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

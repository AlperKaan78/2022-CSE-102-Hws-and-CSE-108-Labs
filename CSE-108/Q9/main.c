#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char name[15], color[15];
    char price[15];
    int serial_number,quantity;

}features_t;

int get_num_of_furniture(char *file_path)
{
    FILE *data_file;
    data_file = fopen(file_path,"r");

    if(data_file == NULL)
    {
        printf("There is an error while opening the file!\n");
    }

    int num_of_furnitures = 0;

    char b= '\0';
    while(b = getc(data_file) != EOF)
    {
        if(b == '\n')
        {
            num_of_furnitures++;
        }
    }
    return num_of_furnitures;
}

void add_new(char *file_path)
{
    FILE *data_file;
    data_file = fopen(file_path, "a");

    if (data_file == NULL)
    {
        printf("There is an error while opening the file!\n");
        return;
    }

    features_t **furnitures;

    int max_number = get_num_of_furniture(file_path);

    furnitures = (features_t **)malloc(max_number * sizeof(features_t *));

    for (int i = 0; i < max_number; i++)
    {
        furnitures[i] = (features_t *)malloc(sizeof(features_t));
    }

    features_t new_fur;
    printf("Enter the properties of the new feature: (name color price serial number (at most 6 digits) quantity):");
    scanf(" %s %s %s %6d %d", new_fur.name, new_fur.color, new_fur.price, &new_fur.serial_number, &new_fur.quantity);

    fprintf(data_file, "\n%s %s $%s %6d %d", new_fur.name, new_fur.color, new_fur.price, new_fur.serial_number, new_fur.quantity);

    fclose(data_file);

    // Free the allocated memory
    for (int i = 0; i < max_number; i++)
    {
        free(furnitures[i]);
    }
    free(furnitures);
}

void see_all(char *file_path)
{
    FILE *data_file;
    data_file = fopen(file_path,"r");

    features_t furniture;

    /*I am skipping the first line.*/
    fscanf(data_file,"%*[^\n]");
    getc(data_file);
    while(!feof(data_file))
    {
        fscanf(data_file," %s %s %s %6d %d", furniture.name, furniture.color, furniture.price, &furniture.serial_number, &furniture.quantity);
        printf("Name: %s\nColor: %s\nPrice: %s\nSerial Number: %d\nQuantity: %d\n\n",furniture.name, furniture.color, furniture.price, furniture.serial_number, furniture.quantity);
    }


}
void remove_furniture(char *file_path)
{
    FILE *data_file;
    data_file = fopen(file_path, "r");

    if (data_file == NULL)
    {
        printf("There is an error while opening the file!\n");
        return;
    }

    features_t **furnitures;

    int max_number = get_num_of_furniture(file_path);

    furnitures = (features_t **)malloc(max_number * sizeof(features_t *));
    for (int i = 0; i < max_number; i++)
    {
        furnitures[i] = (features_t *)malloc(sizeof(features_t));
    }

    int i = 0;
    furnitures[0]->quantity = 154;
    printf("%d\n", furnitures[0]->quantity);

    while (fscanf(data_file, " %s %s %s %6d %d", furnitures[i]->name, furnitures[i]->color, furnitures[i]->price, &furnitures[i]->serial_number, &furnitures[i]->quantity) == 5)
    {
        i++;
    }

    fclose(data_file);

    // Free memory
    for (int j = 0; j < i; j++)
    {
        free(furnitures[j]->name);
        free(furnitures[j]->color);
        free(furnitures[j]->price);
        free(furnitures[j]);
    }
    free(furnitures);
}


void search_furniture(char *file_path)
{
    FILE *data_file;
    data_file = fopen(file_path, "r");

    if (data_file == NULL)
    {
        printf("There is an error while opening the file!\n");
        return;
    }
    char selection;

    printf("Select a property to search:\n1-Name\n2-Color.\n\n");
    scanf(" %c",&selection);
    
    char colorName[15];
    char productName[15];
    features_t furniture;

    switch (selection)
    {
    case '1':
        printf("Enter the name for search:");
        scanf("%s",productName);

        fscanf(data_file,"%*[^\n]");
        getc(data_file);

        while(!feof(data_file))
        {
            fscanf(data_file," %s %s %s %6d %d", furniture.name, furniture.color, furniture.price, &furniture.serial_number, &furniture.quantity);
            
            if(strcmp(furniture.name,productName) == 0)
            {
                printf("Name: %s\nColor: %s\nPrice: %s\nSerial Number: %d\nQuantity: %d\n\n",furniture.name, furniture.color, furniture.price, furniture.serial_number, furniture.quantity);
            }
        }
        break;
    case '2':
        printf("Enter the color for search:");
        scanf("%s",colorName);

        fscanf(data_file,"%*[^\n]");
        getc(data_file);

        while(!feof(data_file))
        {
            fscanf(data_file," %s %s %s %6d %d", furniture.name, furniture.color, furniture.price, &furniture.serial_number, &furniture.quantity);
            
            if(strcmp(furniture.color,colorName) == 0)
            {
                printf("Name: %s\nColor: %s\nPrice: %s\nSerial Number: %d\nQuantity: %d\n\n",furniture.name, furniture.color, furniture.price, furniture.serial_number, furniture.quantity);
            }
        }
        break;
    default:
        printf("You entered invalid number for search property.\n");
        break;
    }



}


int main()
{
    char selection;

    char *file_path = "furniture_database.txt";
    FILE *data_file;
    data_file = fopen(file_path,"r");

    if(data_file == NULL)
    {
        printf("There is an error while opening the file!\n");
    }


    while(selection != '5')
    {
        printf("Welcome to the database furniture shop.\n1-See all furnitures.\n2-Add a new furniture.\n3-Remove furniture.\n4-Search furniture.\n5-Exit.\n");
        scanf(" %c",&selection);

        switch (selection)
        {
        case '1':
            see_all(file_path);
            break;
        case '2':
            add_new(file_path);
            break;
        case '3':
            remove_furniture(file_path);
            break;
        case '4':
            search_furniture(file_path);
            break;
        case '5':break;
        
        default:
            break;
        }
    } 
}


#include<stdio.h>
#include"util.h"

void menu()
{
	/* I define this varaiable as a character
	 since I want to avoid infinite loops that can occur when variable is integer but user enters a character.*/
	char selection;

	while(selection != '5')
	{
		printf("1- File Operations\n2- Query products\n3- Check stock status\
				\n4- Stock control by brand\n5- Export report\n");
	 	scanf(" %c",&selection);

		switch(selection)
		{
			case '1':fileOperations();break;
			case '2':searchProduct();break;
			case '3':checkStockStatus();break;
			case '4':brandStockControl();break;
			case '5':stockReport();break;
			default:printf("Invalid Selection.\n");break;
		}
	}
}

void fileOperations()
{    
	char option,branch[15];

	while (option != '8')
	{
		printf("\n1-Add a new product.\n2-Delete a product.\n3-Update a product.\
				\n4-Add feature to products.\n5-Add a new stock entry.\n6-Delete a stock entry.\
				\n7-Update a stock entry.\n8-Back to the main menu.\n");
		scanf(" %c",&option);
		switch (option)
		{
		case '1':addNewProduct(); break;
		case '2':deleteProduct(); break;
		case '3':updateProduct(); break;
		case '4':addFeature(); break;
		case '5':addNewStockEntry(); break;
		case '6':deleteStockEntry(); break;
		case '7':updateStockEntry(); break;
		case '8':printf("Quitting from the file operations...\n"); break;	
		default:printf("Invalid option is selected. Try again.\n"); break;
		}	
	}	
}


void addNewProduct(){
	FILE *productFile;

	int nameLength, brandLength,pID;
	double price;
	char type, option, name[9], brand[6]; // Increased size of name and brand arrays to account for null terminator

	pID = get_pID(); 
	pID++;

	productFile = fopen("products.txt","a+");
	do {
		printf("Enter the type: ");
		scanf(" %c", &type);	

		// Flush the input buffer
		while ((getchar()) != '\n') {}
	} while (type != 'o' && type != 'd' && type != 'f');


	printf("Enter the name (max 8 characters): ");
	scanf(" %8s", name);
	while (getchar() != '\n'){}
	

	printf("Enter the brand (max 5 characters): ");
	scanf(" %5s", brand);
	while (getchar() != '\n'){}	


	printf("Enter the price: ");
	scanf(" %lf", &price);

	fprintf(productFile, "\n%d,%c,%s,%s,%.2lf", pID, type, name, brand, price);

	fclose(productFile);
}


/* It returns the last pID number of the products.txt*/
int get_pID(){
	FILE *productFile;
	int numof_pID = 0;
	char character;

	productFile = fopen("products.txt","r");
	if(productFile == NULL)
	{
		printf("Something went wrong while opening the file. Try again !\n");
		return 0;
	}
	while(!feof(productFile))
	{
		character = getc(productFile);
		if(character == '\n')
			numof_pID++;
	}
	fclose(productFile);
	return numof_pID;
}

/* It returns the last sID number of the stocks.txt*/
int get_sID(){
	FILE *stockFile;
	int numof_sID = 0;
	char character;

	stockFile = fopen("stocks.txt","r");
	if(stockFile == NULL)
	{
		printf("Something went wrong while opening the file. Try again !\n");
		return 0;
	}
	while(!feof(stockFile))
	{
		character = getc(stockFile);
		if(character == '\n')
			numof_sID++;
	}
	fclose(stockFile);
	return numof_sID;
}


void deleteProduct() {
    FILE *productFile;
    productFile = fopen("products.txt", "r");

	/* If condition warns the user if the file entered does not exist.*/
    if (productFile == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    int lineNumber = get_pID() + 1;
    int counter = 0, trash_pID;
    char lines[lineNumber][100]; // Updated buffer size to accommodate long lines
	
	int number; // This number is used as a pID buffer. Actually this is not used anywhere after the while loop.

    while (counter < lineNumber && fgets(lines[counter], sizeof(lines[0]), productFile) != NULL) {
		if(counter != lineNumber -1)
			fscanf(productFile,"%d",&number);
		counter++;
    }
    fclose(productFile);

	do{
		printf("\nEnter the pID number of product that you want to delete: ");
	    scanf(" %d", &trash_pID);
	}while(trash_pID < 0 || trash_pID > get_pID());
    
    productFile = fopen("products.txt", "w");
    if (productFile == NULL) {
        printf("Failed to open file.\n");
        return;
    }

	/* First line is printed then other lines except the deleted line are printed to the file.*/
    int new_pID = 1;  
    fprintf(productFile, "%s", lines[0]);
    for (int k = 1; k < counter; k++) {
        if (k  != trash_pID) {
            fprintf(productFile, "%d%s", new_pID, lines[k]);
            new_pID++;
        }
    }

    fclose(productFile);
}

void updateProduct(){
	FILE *productFile;
	productFile = fopen("products.txt","r");
	int char_number_of_features = maxCharacter("products.txt");
	int pID,number,counter = 0;
	char old[26];
	char new[20];
	int new_price;
	int lineNumber = get_pID() + 1;
	char lines[lineNumber][char_number_of_features+2];
	char a,feature_buffer[20];

	// Coontents of products is copied into lines array.
    while (counter <= lineNumber && fgets(lines[counter], sizeof(lines[0]), productFile) != NULL) {
		counter++;
    }

	
	do{
		printf("Enter the pID number of the product that you want to update: ");
		scanf(" %d",&pID);
	}while(pID>get_pID() || pID<1);
	
	int flag = 0;
	do{
		counter = 0;
		printf("Enter the feature name of the product that you want to update (except pID): ");
		scanf(" %25s",old);
		while (getchar() != '\n'){}
		fseek(productFile,0,SEEK_SET);
		
		while((fscanf(productFile,"%[^,\n]",feature_buffer)) == 1 && a != '\n')
		{
			
			counter++;
			a = getc(productFile);
			if(compare_strings(old,feature_buffer)){flag = 1;break;}
		}
	}while((compare_strings("pID",old) || compare_strings("pid",old)) || flag == 0);
	
	printf("Enter the new value for the product that you want to update: ");
	scanf(" %19s",new);
	while (getchar() != '\n'){}

	int l = 0,m,n;
	char ff[20];
	int chars_proccessed = 0;
	int num_of_features = featureCount("products.txt");
	fclose(productFile);
	
	
	fopen("products.txt","w");
	
	/*I am writing the new values looking number of features (1->type, 2->name etc.)*/
	while(l<=lineNumber-1)
	{
		if(l == pID)
		{
			m = 0;
			n = 0;
			
			while(m != num_of_features)
			{
				m++;
				sscanf(lines[pID] + n," %[^,\n]%n",ff,&chars_proccessed);
				n += chars_proccessed +1;
				if(m == counter)
				{
					if(m == num_of_features)
						fprintf(productFile,"%s\n",new);
					else
						fprintf(productFile,"%s,",new);

				}
				else
					if(m == num_of_features)
						fprintf(productFile,"%s\n",ff);
					else
						fprintf(productFile,"%s,",ff);
			}

		}
		else{
			fprintf(productFile,"%s",lines[l]);
		}
		l++;
	}

	fclose(productFile);



}
/* The function calculates maximum character of each line in given txt file.*/
int maxCharacter(char file_path[])
{
	FILE *fp;
	fp = fopen(file_path,"r");
	
	int max_char = 0;
	
	while((getc(fp)) != '\n'){max_char++;}
	
	fclose(fp);
	return max_char;
}

/* Function compares two strings and if they are equals to each other returns 1.*/
int compare_strings(char str1[], char str2[]) 
{
	int a = 0, num_of_chars_str1 = 0, num_of_chars_str2 = 0;
	//printf("%s \n%s \n",str1,str2);

	while(str1[num_of_chars_str1++] != '\0'){}
	while(str1[num_of_chars_str2++] != '\0'){}

	if(num_of_chars_str1 != num_of_chars_str2)
		return 0;
	while(a < num_of_chars_str1){
		if(str1[a] != str2[a])
			return 0;
		a++;
	}
	return 1;

}
/*The function counts the number of feature.*/
int featureCount(char file_path[])
{
	FILE *file;
	file = fopen(file_path,"r");
	
	char feature[20],a;
	int counter = 1;

	while((a = getc(file)) != '\n')
	{
		if(a == ',')
			counter++;
	}
	fclose(file);

	return counter;
}


void addFeature(){

}


void addNewStockEntry(){ 
	FILE *stocksFile;
	stocksFile = fopen("stocks.txt","a");
	int sID,stock_pID,current_pID, currentStock;
	char branch[16];

	sID = get_sID();
	sID++;
	current_pID = get_pID();

	do{
		printf("Enter the pID for new stock:");
		scanf(" %d",&stock_pID);

	}while(stock_pID < 1 || stock_pID > current_pID);

	printf("Enter the branch (max 15 characters): ");
	scanf(" %15s", branch);
	while (getchar() != '\n'){}

	printf("Enter the stock:");
	scanf(" %d",&currentStock);

	fprintf(stocksFile,"\n%d,%d,%s,%d",sID,stock_pID,branch,currentStock);

	fclose(stocksFile);

	
}


void deleteStockEntry(){
    FILE *stocksFile;
    stocksFile = fopen("stocks.txt", "r");

	/* If condition warns the user if the file entered does not exist.*/
    if (stocksFile == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    int lineNumber = get_sID() + 1;
    int counter = 0, trash_sID;
    char lines[lineNumber][100]; // Updated buffer size to accommodate long lines
	
	int number; // This number is used as a pID buffer. Actually this is not used anywhere after the while loop.

    while (counter < lineNumber && fgets(lines[counter], sizeof(lines[0]), stocksFile) != NULL) {
		if(counter != lineNumber -1)
			fscanf(stocksFile,"%d",&number);
		counter++;
    }
    fclose(stocksFile);

	do{
		printf("\nEnter the sID number of stock that you want to delete: ");
	    scanf(" %d", &trash_sID);
	}while(trash_sID < 0 || trash_sID > get_sID());
    
    stocksFile = fopen("stocks.txt", "w");
    if (stocksFile == NULL) {
        printf("Failed to open file.\n");
        return;
    }

	/* First line is printed then other lines except the deleted line are printed to the file.*/
    int new_sID = 1;  
    fprintf(stocksFile, "%s", lines[0]);
    for (int k = 1; k < counter; k++) {
        if (k  != trash_sID) {
            fprintf(stocksFile, "%d%s", new_sID, lines[k]);
            new_sID++;
        }
    }

    fclose(stocksFile);
}
void updateStockEntry(){

	FILE *stocksFile;
	stocksFile = fopen("stocks.txt","r");
	int char_number_of_features = maxCharacter("stocks.txt");
	int sID,number,counter = 0;
	char old[20];
	char new[20];
	int new_price;
	int lineNumber = get_sID() + 1;
	char lines[lineNumber][char_number_of_features+2];
	char a,feature_buffer[20];

	/* I am getting all the lines to the lines array.*/
    while (counter <= lineNumber && fgets(lines[counter], sizeof(lines[0]), stocksFile) != NULL) {
		counter++;
    }

	
	do{
		printf("Enter the sID number of the stock that you want to update: ");
		scanf(" %d",&sID);
	}while(sID>get_sID() || sID<1);
	
	/*I am scanning the name from the terminal till the entry is valid.*/
	int flag = 0;
	do{
		counter = 0;
		printf("Enter the feature name of the product that you want to update (except sID): ");
		scanf(" %19s",old);
		while (getchar() != '\n'){}

		fseek(stocksFile,0,SEEK_SET);
		while((a = getc(stocksFile)) != '\n')
		{
			counter++;
			fscanf(stocksFile,"%[^,\n]",feature_buffer);
			if(compare_strings(old,feature_buffer)){flag = 1;break;}
		}
	}while((compare_strings("sID",old) || compare_strings("sid",old)) );
	
	printf("Enter the new value for the product that you want to update: ");
	scanf(" %19s",new);
	while (getchar() != '\n'){}
	printf("%s",new);

	int l = 0,m,n;
	char ff[20];
	int chars_proccessed = 0;

	int num_of_features = featureCount("stocks.txt");
	fclose(stocksFile);
	fopen("stocks.txt","w");

	/*I am writing the new values looking number of features (1->type, 2->name etc.)*/
	while(l<=lineNumber-1)
	{
		if(l == sID)
		{
			m = 0;
			n = 0;
			
			while(m != num_of_features)
			{
				m++;
				sscanf(lines[sID] + n," %[^,\n]%n",ff,&chars_proccessed);
				n += chars_proccessed +1;
				if(m == counter)
				{
					if(m == num_of_features)
						fprintf(stocksFile,"%s\n",new);
					else
						fprintf(stocksFile,"%s,",new);

				}
				else
					if(m == num_of_features)
						fprintf(stocksFile,"%s\n",ff);
					else
						fprintf(stocksFile,"%s,",ff);
			}

		}
		else{
			fprintf(stocksFile,"%s",lines[l]);
		}
		l++;
	}

	fclose(stocksFile);




}


void checkStockStatus()
{
	char choice;
	printf("Enter the selection: \
	    	\n1-Query of the product in specified branch and pID.\
			\n2-Query of the products in specified branch.\
			\n3-Query to list the out-of-stock products in a specified branch.\
			\n4-Back to the main menu.\n");
		scanf(" %c",&choice);
	switch (choice)
	{
	case '1':check_branch_pID();break;
	case '2':check_branch();break;
	case '3':check_out_of_stock();break;
	case '4':printf("Quitting..."); break;
	default:printf("Your enter is invalid");break;
	}
}

/* Receives the branch name and pID from the user then printing proper stock to the terminal. */
void check_branch_pID()
{
	FILE *stocksFile;
	stocksFile = fopen("stocks.txt","r");
	int total_sID = get_sID();
	char filtered_branches[total_sID][15];
	int filtered_stock[total_sID];

	char branch[15];
	int current_pID;

	int max_character = maxCharacter("stocks.txt");

	printf("Enter the branch of the product:");
	scanf("%s",branch);
	while (getchar() != '\n'){}

	printf("enter the pID:");
	scanf(" %d",&current_pID);

	int n = 0,index = 0;
	int pID,sID,current_stock = 0;
	char any_branch[15];

	/*I do not want to scan first line so that I am using fseek.*/
	fseek(stocksFile,max_character,SEEK_SET);

	/* If received pID equals to current scanned pID and 
		received branch and currenc scanned branch equal 
		then current_stock is added to the array.*/
	while(n<=total_sID)
	{
		fscanf(stocksFile," %d,%d,%[^,],%d",&sID,&pID,any_branch,&current_stock);
		if((pID == current_pID) && compare_strings(any_branch,branch))
		{
			my_strcpy(filtered_branches[index],any_branch);
			filtered_stock[index] = current_stock;
			index++;
		}
		n++;
	}
	printf("These are the branches and stocks:\n");
	int i = 0;
	while(i<index-1)
	{
		printf("%s    %d\n",filtered_branches[i],filtered_stock[i]);
		i++;
	}
	fclose(stocksFile);
}


void check_branch()
{
	FILE *stocksFile;
	stocksFile = fopen("stocks.txt","r");
	int total_sID = get_sID();
	int filtered_pID[total_sID];
	int filtered_stock[total_sID];

	char branch[15];
	int current_pID;

	int max_character = maxCharacter("stocks.txt");

	printf("Enter the branch of the product:");
	scanf("%s",branch);
	while (getchar() != '\n'){}


	int n = 0,index = 0;
	int pID,sID,current_stock = 0;
	char any_branch[15];
	/*I do not want to scan first line so that I am using fseek.*/
	fseek(stocksFile,max_character,SEEK_SET);
	while(n<=total_sID)
	{
		fscanf(stocksFile," %d,%d,%[^,],%d",&sID,&pID,any_branch,&current_stock);
		if(compare_strings(any_branch,branch))
		{
			filtered_pID[index] = pID ;
			filtered_stock[index] = current_stock;
			index++;
		}
		n++;
	}
	/*I am writing the pID's and stocks to the terminal below.*/
	printf("These are the pIDs and stocks:\n");
	int i = 0;
	while(i<index-1)
	{
		printf("%d    %d\n",filtered_pID[i],filtered_stock[i]);
		i++;
	}
}

/* I created my string copy function below.*/
void my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void check_out_of_stock()
{
	FILE *stocksFile;
	FILE *productFile;

	stocksFile = fopen("stocks.txt","r");
	int total_sID = get_sID();
	int filtered_pID[total_sID];

	char branch[15];
	int current_pID;

	int max_character = maxCharacter("stocks.txt");

	printf("Enter the branch of the product:");
	scanf("%s",branch);
	while (getchar() != '\n'){}

	int n = 0,index = 0;
	int pID,sID,current_stock = 0;
	char any_branch[15];
	
	/*I do not want to scan first line so that I am using fseek.*/
	fseek(stocksFile,max_character,SEEK_SET);
	while(n<total_sID)
	{
		fscanf(stocksFile," %d,%d,%[^,],%d",&sID,&pID,any_branch,&current_stock);
		if(!compare_strings(any_branch,branch))
		{
			filtered_pID[index] = pID ;
			index++;
		}
		n++;
	}

	fclose(stocksFile);
	productFile = fopen("products.txt","r");
	n = 0;
	double price;
	int total_pID = get_pID();
	char type;
	char brand[5];
	char any_name[8];
	char filtered_names[total_pID+1][8];
	int name_index = 0;
	max_character = maxCharacter("products.txt");

	fseek(productFile,max_character+1,SEEK_SET);

	while(n<total_pID)
	{
		fscanf(productFile,"%d,%c,%[^,],%[^,],%lf",&pID,&type,any_name,brand,&price);
		
		if(is_pID(pID,filtered_pID))
		{
			
			my_strcpy(filtered_names[name_index],any_name);
			printf("%s",any_name);
			// printf("\n%d",pID);
			name_index++;
		}
		n++;
	}
	printf("These are the pIDs and stocks:\n");
	int i = 0;
	while(i<name_index)
	{
		printf("%s\n",filtered_names[i]);
		i++;
	}

}
/* This function controls whether integer is in the integer array.*/
int is_pID(int x, int arr[]) {
    for (int i = 0; arr[i] != 0; i++) {
        if (arr[i] == x) {
            return 1;
        }
    }
    return 0;
}

void searchProduct()
{

}

void brandStockControl()
{

}
void stockReport()
{

}

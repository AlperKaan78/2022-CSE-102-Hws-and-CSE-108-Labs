#ifndef _UTIL_H
#define _UTIL_H_

void fileOperations();
void menu();
void searchProduct();
void checkStockStatus();
void brandStockControl();
void stockReport();

void addNewProduct();
void deleteProduct();
void updateProduct();
void addFeature();
void addNewStockEntry();
void deleteStockEntry();
void updateStockEntry();

int get_pID();
int get_sID();
int featureCount(char file_path[]);
int compare_strings(char str1[], char str2[]);
int maxCharacter(char file_path[]);
void my_strcpy(char *dest, const char *src);
int is_pID(int pID, int filtered_pID[]);
int contains(int num, int arr[], int len);

void check_branch_pID();
void check_branch();
void check_out_of_stock();


#endif
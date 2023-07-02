#include<stdio.h>
#include<stdlib.h>



typedef struct  Node {
    int value;
    struct Node* left_node;
    struct Node* right_node;
}Node;
 
typedef struct BST {
    struct Node* root;
}BST;

void addNode(struct BST* bst, int value);
void printTree(Node* node);
void printTreeInorder(BST* bst);
Node* searchNode(BST* bst, int value);
int countNodes(BST* bst);
int getMaxDepth(BST* bst);
int getMaxDepth2(Node* node);
int countLeafNodes(struct BST* bst);
int countLeafNodes2(Node* node);


BST* generateBST(const char* filename)
{
    BST* bst = (BST*)malloc(sizeof(BST));
    bst->root = NULL;

    FILE* inFile = fopen(filename, "r");

    int num;

    while (fscanf(inFile, " %d", &num) != EOF)
    {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->value = num;
        new_node->right_node = NULL;
        new_node->left_node = NULL;

        if (bst->root == NULL)
        {
            bst->root = new_node;
        }
        else
        {
            Node* current = bst->root;
            while (1)
            {
                if (current->value > num)
                {
                    if (current->left_node == NULL)
                    {
                        current->left_node = new_node;
                        break;
                    }
                    current = current->left_node;
                }
                else if (current->value < num)
                {
                    if (current->right_node == NULL)
                    {
                        current->right_node = new_node;
                        break;
                    }
                    current = current->right_node;
                }
            }
        }
    }
    fclose(inFile);
    return bst;
}




int main()
{
    char *file_name = "input.txt";
    BST *newBST;
    Node* foundNode;
    int number;
    newBST = generateBST(file_name);
    printTreeInorder(newBST);

    char selection;
    while(selection != '4')
    {
        printf("Select:\n1-Add Node.\n2-Search Node.\n3-Remove Node.\n4-Exit.\n");scanf(" %c",&selection);
        switch (selection)
        {
        case '1':
            printf("Enter the number to add Node:");scanf(" %d",&number);
            addNode(newBST,number);
            printf("The number %d is successfully added.\nNew ordered Tree: ",number);
            printTreeInorder(newBST);
            break;
        case '2':
            printf("Enter the number to search:");scanf(" %d",&number);
            foundNode = searchNode(newBST, number);

            if (foundNode != NULL)
            {
                printf("Node with value %d found in the BST.\n",number);
            }
            else
            {
                printf("Node with value %d not found in the BST.\n",number);
            }
            break;
        case '3':
            printf("There is no function here.\n\n");
            break;
        case'4':
            printf("Exitting..\n");
            break;
        default:
            printf("Invalid selection.\n");
            break;
        }
    }

    printf("Max depth is: %d\n",getMaxDepth(newBST));
    printf("The number of leaf Nodes: %d\n",countLeafNodes(newBST));
    printf("The number of Nodes: %d\n",countNodes(newBST));



}


void addNode(BST* bst, int value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->right_node = NULL;
    new_node->left_node = NULL;

    if (bst->root == NULL)
    {
        bst->root = new_node;
    }
    else
    {
        Node* current = bst->root;
        while (1)
        {
            if (current->value > value)
            {
                if (current->left_node == NULL)
                {
                    current->left_node = new_node;
                    break;
                }
                current = current->left_node;
            }
            else if (current->value < value)
            {
                if (current->right_node == NULL)
                {
                    current->right_node = new_node;
                    break;
                }
                current = current->right_node;
            }
            else
            {
                free(new_node);
                break;
            }
        }
    }    
}


void printTree(Node* node)
{
    if (node == NULL)
        return;

    printTree(node->left_node);

    printf("%d ", node->value);

    printTree(node->right_node);
}

void printTreeInorder(BST* bst)
{
    if (bst == NULL || bst->root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    printf("Ordered Tree: ");
    printTree(bst->root);
    printf("\n");
}

Node* searchNode(BST* bst, int value)
{
    if (bst == NULL || bst->root == NULL)
    {
        printf("Tree is empty.\n");
        return NULL;
    }

    Node* current = bst->root;
    while (current != NULL)
    {
        if (current->value == value)
        {
            return current;
        }
        else if (current->value > value)
        {
            current = current->left_node;
        }
        else
        {
            current = current->right_node;
        }
    }

    printf("Your value is not in the BST.\n");
    return NULL;
}



int countNodes2(Node* node)
{
    if (node == NULL)
        return 0;

    int leftCount = countNodes2(node->left_node);
    int rightCount = countNodes2(node->right_node);

    return 1 + leftCount + rightCount;
}

int countNodes(BST* bst)
{
    if (bst == NULL || bst->root == NULL)
        return 0;

    return countNodes2(bst->root);
}





int getMaxDepth2(Node* node)
{
    if (node == NULL)
        return 0;

    int leftDepth = getMaxDepth2(node->left_node);
    int rightDepth = getMaxDepth2(node->right_node);

    if(leftDepth>rightDepth)
    {
        return 1+leftDepth;
    }
    else
    {
        return 1+rightDepth;
    }
}

int getMaxDepth(BST* bst)
{
    if (bst == NULL || bst->root == NULL)
        return 0;

    return getMaxDepth2(bst->root);
}





int countLeafNodes2(Node* node)
{
    if (node == NULL)
        return 0;

    if (node->left_node == NULL && node->right_node == NULL)
        return 1;

    int leftCount = countLeafNodes2(node->left_node);
    int rightCount = countLeafNodes2(node->right_node);

    return leftCount + rightCount;
}

int countLeafNodes(BST* bst)
{
    if (bst == NULL || bst->root == NULL)
        return 0;

    return countLeafNodes2(bst->root);
}








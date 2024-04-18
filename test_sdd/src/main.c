#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

struct Project
{
    char *projectTitle;
    char *projectOwner;
    unsigned char noOfExecutants;
    float projectBudget;
};

typedef struct Project Project;

struct NodeD
{
    struct Project *data;
    struct NodeD *next, *prev;
};

typedef struct NodeD NodeD;

struct DoubleList
{
    struct NodeD *tail, *head;
};

typedef struct DoubleList DoubleList;

DoubleList insert_node_beggining(DoubleList list, Project *data)
{
    NodeD *newNode = (NodeD *)malloc(sizeof(NodeD));
    newNode->data = data;
    newNode->next = list.head;
    newNode->prev = NULL;

    if (list.head != NULL)
    {
        list.head->prev = newNode;
        list.head = newNode;
    }
    else
    {
        list.head = list.tail = newNode;
    }

    return list;
}

unsigned char count_of_executants(DoubleList dList, const char *projectOwner)
{
    char count = 0;

    NodeD *tempList = dList.head;

    while (tempList)
    {
        if (strcmp(tempList->data->projectOwner, projectOwner) == 0)
        {
            count += tempList->data->noOfExecutants;
        }

        tempList = tempList->next;
    }

    return count;
}

void increase_project_budget(DoubleList dList, unsigned char threshold, unsigned char percent)
{
    NodeD *tempList = dList.head;

    while (tempList)
    {
        if (tempList->data->noOfExecutants > threshold)
        {
            tempList->data->projectBudget = tempList->data->projectBudget + (tempList->data->projectBudget * (0.01 * percent));
        }
        tempList = tempList->next;
    }
}

void print_list(DoubleList dList)
{
    NodeD *tempList = dList.head;

    while (tempList)
    {
        printf("%s %s %d %.2f\n", tempList->data->projectTitle, tempList->data->projectOwner, tempList->data->noOfExecutants, tempList->data->projectBudget);

        tempList = tempList->next;
    }

    free(tempList);

    printf("\n");
}

char **array_of_project_titles(DoubleList dList, float budget_threshold)
{
    char **array_from_list;
    unsigned char list_size = 0;
    unsigned char array_size = 0;
    NodeD *tempList = dList.head;

    while (tempList)
    {
        if (tempList->data->projectBudget > budget_threshold)
        {
            array_size += 1;
        }

        list_size += 1;
        tempList = tempList->next;
    }

    array_from_list = (char **)malloc((sizeof(char *) * list_size) + 1);

    tempList = dList.head;

    unsigned char it = 0;

    for (unsigned char i = 0; i < list_size; i++)
    {
        if (tempList->data->projectBudget > budget_threshold)
        {
            array_from_list[it] = tempList->data->projectTitle;
            it += 1;
        }

        tempList = tempList->next;
    }

    return array_from_list;
}

unsigned char size_of_array_project_titles(DoubleList dList, float budget)
{
    unsigned char list_size = 0;
    unsigned char array_size = 0;
    NodeD *tempList = dList.head;

    while (tempList)
    {
        if (tempList->data->projectBudget > budget)
        {
            array_size += 1;
        }

        list_size += 1;
        tempList = tempList->next;
    }

    return array_size;
}

int main()
{
    FILE *file = fopen("Projects.txt", "r");
    char buffer[256];

    DoubleList dList;
    dList.head = dList.tail = NULL;

    while (fgets(buffer, sizeof(buffer), file)) // read project title char*
    {
        Project tProject, *pProject;

        tProject.projectTitle = (char *)malloc(strlen(buffer) - 1);
        strncpy(tProject.projectTitle, buffer, strlen(buffer) - 1);
        tProject.projectTitle[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file);
        tProject.projectOwner = (char *)malloc(strlen(buffer) - 1);
        strncpy(tProject.projectOwner, buffer, strlen(buffer) - 1);
        tProject.projectOwner[strlen(buffer) - 1] = 0;

        fgets(buffer, sizeof(buffer), file);
        tProject.noOfExecutants = (unsigned char)(atof(buffer));

        fgets(buffer, sizeof(buffer), file);
        tProject.projectBudget = atof(buffer);

        pProject = (Project *)malloc(sizeof(Project));
        *pProject = tProject;

        dList = insert_node_beggining(dList, pProject);
    }

    print_list(dList);

    unsigned char count = count_of_executants(dList, "Mihai");

    printf("The number of executants for projects owned by Mihai is: %d\n\n", count);

    increase_project_budget(dList, 9, 50);

    printf("The list after the project budget increase:\n");
    print_list(dList);

    printf("\n");

    printf("The array created from the double linked list:\n");
    char **array;
    array = array_of_project_titles(dList, 2000.00);

    for (unsigned char i = 0; i < size_of_array_project_titles(dList, 2000.00); i++)
    {
        printf("%s\n", array[i]);
    }
}

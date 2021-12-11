//
// Created by Michael Brown on 02/12/2021.
//

#include "searchEngine.h"

typedef struct HashTable HashTable;

double IDF_Score(char query[256]);

void add(struct listNode **pNode, char *url);

char *url;
int *max_hops;

//Create the main method
int main(int argc, char **argv) {
    //Check if the user has entered the correct number of arguments
    if (argc != 3) {
        printf("Usage: ./searchEngine <filename> <max_hops>\n");
        exit(1);
    }
    //Create the url variable
    url = argv[1];
    //Open the file and check if it exists
    FILE *fp = fopen(url, "r");
    if (fp == NULL) {
        printf("Error: File does not exist\n");
        exit(1);
    }
    //Create the max_hops variable
    max_hops = malloc(sizeof(int));
    *max_hops = atoi(argv[2]);
    struct TrieNode *root = indexPage(url);
    //Add 1 to the max_hops variable
    *max_hops = *max_hops + 1;
    //Create a variable to store the current hop
    int current_hop = 0;
    while (1) {
        //If the current hop is equal to the max_hops variable. Break the loop
        if (current_hop == *max_hops) {
            break;
        }
        struct listNode *list = crawl(3, (char **) (url + current_hop));
        //If the list is empty, break the loop
        if (list == NULL) {
            break;
        }
        if (contains((const struct listNode *) crawl, url)) {
            break;
        }
        //Add 1 to the current hop
        current_hop++;
        //Create a list of visited urls
        struct listNode *visited = NULL;
        //Create a list of unvisited urls, and populate it with the list of urls from the file
        struct listNode *unvisited = NULL;
        //For each line in the file, add it to the unvisited list
        while (fgets(url, 256, fp) != NULL) {
            url[strlen(url) - 1] = '\0';
            add(&unvisited, url);
        }
        //Using the current url, cycle through the unvisited list, and if the getLink function returns 1, add the url to the visited list
        while (unvisited != NULL) {
            if (getLink(root, unvisited->url) == 1) {
                add(&visited, unvisited->url);
            }
            unvisited = unvisited->next;
        }
        //If the current url isnt in the visited list, index the url
        if (!contains(visited, url)) {
            indexPage(url);
        }
        
    }
    //Close the file
    fclose(fp);
    //Free the memory
    free(max_hops);


//Ask the user to enter a search query
    char query[256];

    printf("Enter a search query: ");
    scanf("%s", query);

}

void add(struct listNode **pNode, char *url) {
    //Create a new node
    struct listNode *newNode = malloc(sizeof(struct listNode));
    //Set the url to the new node
    newNode->url = url;
    //Set the next node to NULL
    newNode->next = NULL;
    //If the list is empty, set the new node to the list
    if (*pNode == NULL) {
        *pNode = newNode;
    } else {
        //Set the current node to the list
        struct listNode *current = *pNode;
        //While the current node is not NULL
        while (current != NULL) {
            //If the current node's url is equal to the new node's url, break the loop
            if (strcmp(current->url, newNode->url) == 0) {
                break;
            }
            //Set the current node to the next node
            current = current->next;
        }
        //If the current node is NULL, set the new node to the list
        if (current == NULL) {
            newNode->next = *pNode;
            *pNode = newNode;
        }
    }
}

//Create a method to calculate a TF-IDF value, given a query
double IDF_Score(char query[256]) {
    //Create a variable to store the IDF value
    double IDF_value = 0;
    //Use the method addWordOccurrence to get the number of times the word appears in the document
    runIndexerOnPage(2, (char **) url);
    //Return the IDF value
    return IDF_value;
}


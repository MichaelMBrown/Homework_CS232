//
// Created by Michael Brown on 02/12/2021.
//

#include "searchEngine.h"

typedef struct HashTable HashTable;

double IDF_Score(char query[256]);

//Create the main method
int main(int argc, const char *argv[]) {
    //Ask the user to enter a web query
    printf("Enter a web query: ");
    //Create a string to store the query
    const int MAX_QUERY_LENGTH = 256;
    char query[MAX_QUERY_LENGTH];
    //Read the query into the string
    fgets(query, MAX_QUERY_LENGTH, stdin);
    //Remove the newline character from the end of the string
    query[strlen(query) - 1] = '\0';
    //Print the query
    printf("Query: %s\n", query);
    //Print the IDF values
    printf("IDF values:\n");


    //List web pages, and their scores
    printf("Web pages and their scores:\n");


}

//Create a method to calculate a TF-IDF value, given a query
double IDF_Score(char query[256]) {
    //Create a variable to store the IDF value
    double IDF_value = 0;
    //Use the method addWordOccurrence to get the number of times the word appears in the document
    int wordOccurences = addWordOccurrence(query);
    //Return the IDF value
    return IDF_value;
}


/* File : indexPage.c * /
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_CHAR 300000

/* TODO: structure definitions */
struct TrieNode {
    int isWord;
    int count;
    char letter;
    struct TrieNode *children[ALPHABET_SIZE];
};

// make new node with user input
struct TrieNode *getNode() {
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    newNode->isWord = 0;
    newNode->count = 0;
    newNode->letter = 0;

    for (int index = 0; index < ALPHABET_SIZE; index++) {
        newNode->children[index] = NULL;
    }
    return newNode;
}

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

// changed the return type to char* pointer
/* TODO: change this return type */
struct TrieNode *indexPage(const char *url);

// this needs another parameter node *tNode
int addWordOccurrence(const char *word, const int wordLength, struct TrieNode *root);

// this method needs node *trieNode parameter
void printTrieContents(struct TrieNode *root, char *str, int level);

// inserted struct trieNode
int freeTrieMemory(struct TrieNode *root);

int getText(const char *srcAddr, char *buffer, const int bufSize);

int main(int argc, char **argv) {
    // wrote the (simple) main function - Michael Brown

    if (argc <= 1) {
        fprintf(stderr, "Usage: indexPage <URL>");
        return 1;
    }
    struct TrieNode *root = indexPage(argv[1]);
    char word[MAX_CHAR];
    printTrieContents(root, word, 0);
    freeTrieMemory(root);

    return 0;
}

struct TrieNode *indexPage(const char *url) {
    struct TrieNode *root = getNode();

    char *buffer = (char *)malloc(sizeof(char) * MAX_CHAR);

    int parse = getText(url, buffer, MAX_CHAR);
    int isNewWord = 0;
    int startWord = 0;
    int endWord = 0;

    for (int i = 0; i < parse; i++) {
        if (isalpha(buffer[i])) {
            buffer[i] = tolower(buffer[i]);
        }
        if (isalpha(buffer[i]) && !isNewWord) {
            startWord = i;
            isNewWord = i;
        }
        if (isalpha(buffer[i]) && isNewWord) {
            endWord = i;
            addWordOccurrence(buffer + startWord, endWord - startWord, root);
            isNewWord = 0;
        }
    }
    free(buffer);
    return root;
}

// Completed Edward Esqueda
int addWordOccurrence(const char *word, const int wordLength, struct TrieNode *root) {
    int charCursor;
    struct TrieNode *nodeCursor = root;
    printf("\t");

    for (int i = 0; i < wordLength; i++) {
        charCursor = word[i] - 'a';
        if (nodeCursor->children[charCursor] == NULL) {
            nodeCursor->children[charCursor] = getNode();
            nodeCursor->children[charCursor]->letter = word[i];
        }
        nodeCursor = nodeCursor->children[charCursor];
        printf("%c", nodeCursor->letter);
    }
    nodeCursor->isWord = 1;
    nodeCursor->count++;
    printf("\t");
    return 0;
}

// Print Trie Node ~ DONE~
void printTrieContents(struct TrieNode *root, char *str, int level) {
    struct TrieNode *head = root;
    if (head->isWord == 1) {
        printf("%s: %d\n", str, head->count);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (head->children[i] != NULL) {
            str[level] = head->children[i]->letter;
            printTrieContents(head->children[i], str, level + 1);
            str[level] = 0;
        }
    }
}

// Completed freeTrieMemory - Edward Esqueda
int freeTrieMemory(struct TrieNode *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            freeTrieMemory(root->children[i]);
        }
    }
    free(root);

    return 0;
}

/* You should not need to modify this function */
int getText(const char *srcAddr, char *buffer, const int bufSize) {
    FILE *pipe;
    int bytesRead;

    snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

    pipe = fopen(buffer, "r");
    if (pipe == NULL) {
        fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
                buffer);
        return 0;
    }

    bytesRead = fread(buffer, sizeof(char), bufSize - 1, pipe);
    buffer[bytesRead] = '\0';

    fclose(pipe);

    return bytesRead;
}
/* File : indexPage.c * /
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_CHAR 300000

/* TODO: structure definitions */
struct TrieNode {
    int isWord;
    int count;
    char letter;
    struct TrieNode *children[ALPHABET_SIZE];
};

// make new node with user input
struct TrieNode *getNode() {
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    newNode->isWord = 0;
    newNode->count = 0;
    newNode->letter = 0;

    for (int index = 0; index < ALPHABET_SIZE; index++) {
        newNode->children[index] = NULL;
    }
    return newNode;
}

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

// changed the return type to char* pointer
/* TODO: change this return type */
struct TrieNode *indexPage(const char *url);

// this needs another parameter node *tNode
int addWordOccurrence(const char *word, const int wordLength, struct TrieNode *root);

// this method needs node *trieNode parameter
void printTrieContents(struct TrieNode *root, char *str, int level);

// inserted struct trieNode
int freeTrieMemory(struct TrieNode *root);

int getText(const char *srcAddr, char *buffer, const int bufSize);

int main(int argc, char **argv) {
    // wrote the (simple) main function - Michael Brown

    if (argc <= 1) {
        fprintf(stderr, "Usage: indexPage <URL>");
        return 1;
    }
    struct TrieNode *root = indexPage(argv[1]);
    char word[MAX_CHAR];
    printTrieContents(root, word, 0);
    freeTrieMemory(root);

    return 0;
}

struct TrieNode *indexPage(const char *url) {
    struct TrieNode *root = getNode();

    char *buffer = (char *)malloc(sizeof(char) * MAX_CHAR);

    int parse = getText(url, buffer, MAX_CHAR);
    int isNewWord = 0;
    int startWord = 0;
    int endWord = 0;

    for (int i = 0; i < parse; i++) {
        if (isalpha(buffer[i])) {
            buffer[i] = tolower(buffer[i]);
        }
        if (isalpha(buffer[i]) && !isNewWord) {
            startWord = i;
            isNewWord = i;
        }
        if (isalpha(buffer[i]) && isNewWord) {
            endWord = i;
            addWordOccurrence(buffer + startWord, endWord - startWord, root);
            isNewWord = 0;
        }
    }
    free(buffer);
    return root;
}

// Completed Edward Esqueda
int addWordOccurrence(const char *word, const int wordLength, struct TrieNode *root) {
    int charCursor;
    struct TrieNode *nodeCursor = root;
    printf("\t");

    for (int i = 0; i < wordLength; i++) {
        charCursor = word[i] - 'a';
        if (nodeCursor->children[charCursor] == NULL) {
            nodeCursor->children[charCursor] = getNode();
            nodeCursor->children[charCursor]->letter = word[i];
        }
        nodeCursor = nodeCursor->children[charCursor];
        printf("%c", nodeCursor->letter);
    }
    nodeCursor->isWord = 1;
    nodeCursor->count++;
    printf("\t");
    return 0;
}

// Print Trie Node ~ DONE~
void printTrieContents(struct TrieNode *root, char *str, int level) {
    struct TrieNode *head = root;
    if (head->isWord == 1) {
        printf("%s: %d\n", str, head->count);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (head->children[i] != NULL) {
            str[level] = head->children[i]->letter;
            printTrieContents(head->children[i], str, level + 1);
            str[level] = 0;
        }
    }
}

// Completed freeTrieMemory - Edward Esqueda
int freeTrieMemory(struct TrieNode *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            freeTrieMemory(root->children[i]);
        }
    }
    free(root);

    return 0;
}

/* You should not need to modify this function */
int getText(const char *srcAddr, char *buffer, const int bufSize) {
    FILE *pipe;
    int bytesRead;

    snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

    pipe = fopen(buffer, "r");
    if (pipe == NULL) {
        fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
                buffer);
        return 0;
    }

    bytesRead = fread(buffer, sizeof(char), bufSize - 1, pipe);
    buffer[bytesRead] = '\0';

    fclose(pipe);

    return bytesRead;
}

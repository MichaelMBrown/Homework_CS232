#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ADDR_LENGTH 1000

/*
 * a node in our linked-list of web addresses
 */
struct listNode{
  char addr[MAX_ADDR_LENGTH];

  struct listNode *next;
};


/*
 * returns 1 if the list starting at pNode contains the address addr,
 *    and returns 0 otherwise
 */
int contains(const struct listNode *pNode, const char *addr);

/*
 * inserts the address addr as a new listNode at the end of
 *    the list
 */
void insertBack(struct listNode *pNode, const char *addr);

/*
 * prints the addresses from pNode to the end of the list,
 *   one on each line
 */
void printAddresses(const struct listNode *pNode);

/*
 * frees the memory associated with this node and all subsequent nodes
 */
void destroyList(struct listNode *pNode);
  
/*
 * srcAddr should be a web address (e.g., http://www.yahoo.com).
 * link should point to an array of maxLinkLength characters.
 * getLink returns 1 if a link was found and 0 otherwise.
 * If a link was found, "link" will be filled in with the web address.
 */
int getLink(const char* srcAddr, char* link, int maxLinkLength);

int crawl(int argc, char** argv){
  
  long seed;
  char startAddr[MAX_ADDR_LENGTH];
  char destAddr[MAX_ADDR_LENGTH];
  
  int currentHop, hopLimit;

  struct listNode *listNodeHead;

  if(argc < 3 || argc > 4){
    fprintf(stderr, "USAGE: %s startAddr hopLimit [rand seed]", argv[0]);
    return -1;
  }
  
  /* initialization */
  if(argc >= 4){
    seed = atol(argv[3]);
  }
  else{
    seed = time(NULL);
  }

  printf("seed = %ld\n", seed);
  srand(seed);

  strncpy(startAddr, argv[1], MAX_ADDR_LENGTH);
  startAddr[MAX_ADDR_LENGTH - 1] = '\0';

    hopLimit = atoi(argv[2]);

    listNodeHead = malloc(sizeof(struct listNode));
  if(listNodeHead == NULL){
    fprintf(stderr, "ERROR: could not allocate memory\n");
    return -2;
  }
  strncpy(listNodeHead->addr, startAddr, MAX_ADDR_LENGTH);
    listNodeHead->next = NULL;

  /* start the crawling */
  for(currentHop=1; currentHop <= hopLimit; currentHop++){
    int res = getLink(startAddr, destAddr, MAX_ADDR_LENGTH);

    if(!res){
      printf("Dead end on hop %d: no outgoing links\n", currentHop);
      break;
    }

    if(contains(listNodeHead, destAddr)){
      printf("Cycle detected on hop %d: address %s\n", currentHop, destAddr);
      currentHop--; // try again for this hop in the next iteration
    }
    else{
      insertBack(listNodeHead, destAddr);
      strncpy(startAddr, destAddr, MAX_ADDR_LENGTH);
    }
  }

  printAddresses(listNodeHead);

  destroyList(listNodeHead);

  return 0;
}


/*
 * returns 1 if the list starting at pNode contains the address addr,
 *    and returns 0 otherwise
 */
int contains(const struct listNode *pNode, const char *addr){
    int i = 0;
    const struct listNode *tmpNode;
    tmpNode = pNode;
    do {
        if (tmpNode->addr == addr){
            printf("Found a match\n");
            return 1;
        }
        i++;
        tmpNode=tmpNode->next;
    }while ((tmpNode != NULL) && (tmpNode->addr != addr));
  return 0;
}
    

/*
 * inserts the address addr as a new listNode at the end of
 *    the list
 */
void insertBack(struct listNode *pNode, const char *addr){
  struct listNode *temp,*newNode;
    newNode=(struct listNode*) malloc(sizeof (struct listNode));
    if (newNode==NULL){
        fprintf(stderr,"ERROR: Cannot allocate memory\n");
        exit(EXIT_FAILURE);
    } else{
        strncpy(newNode->addr, addr, MAX_ADDR_LENGTH);
        newNode->next=NULL;
        temp=pNode;
        while (temp->next != NULL){
            temp=temp->next;
        }
        temp->next=newNode;
    }
}


/*
 * prints the addresses from pNode to the end of the list,
 *   one on each line
 */
void printAddresses(const struct listNode *pNode){
    const struct listNode *tmpNode;
    if (pNode==NULL){
        fprintf(stderr,"List is empty :(");
    } else{
         tmpNode=pNode;
        while (tmpNode != NULL){
            printf("%s,\n",tmpNode->addr);
            tmpNode=tmpNode->next;
        }
    }
}

/*
 * frees the memory associated with this node and all subsequent nodes
 */
void destroyList(struct listNode *pNode){
    free(pNode);
}
  


int getLink(const char* srcAddr, char* link, const int maxLinkLength){
  const int bufSize = 1000;
  char buffer[bufSize];

  int numLinks = 0;

  FILE *pipe;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getLinks.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n", buffer);
    return 0;
  }

  fscanf(pipe, "%d\n", &numLinks);

  if(numLinks > 0){
    int linkNum;
    double r = (double)rand() / ((double)RAND_MAX + 1.0);

    for(linkNum=0; linkNum<numLinks; linkNum++){
      fgets(buffer, bufSize, pipe);
      
      if(r < (linkNum + 1.0) / numLinks){
		    break;
      }
    }

    /* copy the address from buffer to link */
    strncpy(link, buffer, maxLinkLength);
    link[maxLinkLength-1] = '\0';
    
    /* get rid of the newline */
    {
      char* pNewline = strchr(link, '\n');
      if(pNewline != NULL){
		    *pNewline = '\0';
      }
    }
  }

  pclose(pipe);

  if(numLinks > 0){
    return 1;
  }
  else{
    return 0;
  }
}

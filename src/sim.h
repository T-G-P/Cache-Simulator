#ifndef CACHE_H
#define CACHE_H

int BLOCKSIZE;

void printHelp();


typedef struct cache_ {
  unsigned int cachesize; /* Total size of the cache */
  unsigned int blocksize; /* The number of bytes in a block */
  unsigned int setsize;   /* The number of blocks in a set */
  unsigned int num_sets;  /* The number of sets in the cache */
  int numHits;
  int numMisses;
  int numColdmisses;
  int numConflictmisses;
  int numCapacitymisses;
  int assoc; /* 0 means direct, 1 means fully associative, >1 assoc:n */

  unsigned long *array;
  //TODO add whatever else
} cache;


/* Determines the type of associativity for a cache */
unsigned int parseAssoc(char *);

/* Makes a new cache struct given strings */
cache *create_cache(char *cachesize, char *assoc, int blocksize);

/* Simulation of FIFO Replacement algorithm */
void fifo();

/* Prints basic cache info */
void printInfo(cache *);
#endif

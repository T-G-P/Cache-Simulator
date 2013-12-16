#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sim.h"

unsigned int parseAssoc(char *s) {
  char *sub;
  if (strcmp(s, "direct") == 0) {
    return 0;
  } else if (strcmp(s, "assoc") == 0) {

      return 1;
  } else if (strstr(s, "assoc:")) {
    return atoi(s + 7);
  } else {
    fprintf(stderr, "Invalid association type\n");
  }

}

/* Creates a cache struct, returns pointer */
/* cachesize: the total size of the cache */
/* assoc: the type of cache (direct, assoc, assoc:n) */
/* blocksize: the size of a block */
cache *create_cache(char *cachesize, char *assoc, int blocksize) {
  cache *ret = malloc(sizeof(cache));
  ret->cachesize = atoi(cachesize);
  ret->numMisses = 0;
  ret->numHits = 0;
  ret->numConflictmisses = 0;
  ret->numCapacitymisses = 0;
  ret->numColdmisses = 0;
  ret->blocksize = blocksize;
  //fprintf(stdout,"%d\n", blocksize);
  //fprintf(stdout,"%d\n", ret->blocksize);
  //ret->assoc = parseAssoc(assoc);
  //fprintf(stdout,"%d\n", ret->blocksize);
  /* Direct */
  if (ret->assoc == 0) {
    ret->setsize = 1;
  }
  /* Assoc */
  else if (ret->assoc == 1) {
    ret->setsize = 0;
  }
  /* Assoc:n */
  else if (ret->assoc > 1) {
    ret->setsize = ret->assoc;
  }
  //fprintf(stdout,"%d\n", ret->blocksize);
  ret->num_sets = (unsigned int)(ret->cachesize / (ret->setsize * ret->blocksize));
  //fprintf(stdout,"%d\n", ret->cachesize);
   //fprintf(stdout,"%d\n", ret->blocksize);
    //  fprintf(stdout,"%d\n", ret->setsize);
     // fprintf(stdout,"%d\n", ret->blocksize);
  ret->array = (unsigned long *)malloc(ret->num_sets * sizeof(unsigned long));
  memset(ret->array, 0, ret->num_sets * sizeof(unsigned long));
  return ret;
}


void printHelp() {
  printf("Usage: cache-sim [-h]\n"
         "\t-l1size <L1 size>\t-l1assoc <L1 assoc>\n"
         "\t-l2size <L2 size>\t-l2assoc <L2 assoc>\n"
         "\t-l3size <L3 size>\t-l3assoc <L3 assoc>\n"
         "\t<block size> <replace alg> <trace file>\n");
}

/* Simulation of FIFO Replacement algorithm */
void fifo() {
  return;
}

void printInfo(cache *c) {
  printf("CACHE INFO:\n  cachesize: %d\n  blocksize: %d\n"
         "  setsize: %d\n  number of sets: %d\n cache misses: %d\n cache hits: %d\n", c->cachesize, c->blocksize,
         c->setsize, c->num_sets, c->numMisses, c->numHits);
}

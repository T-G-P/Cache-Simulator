#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sim.h"


int main(int argc, char **argv) {
    unsigned int l1size, l2size, l3size, blocksize;
    FILE *tracefile;
    int replacementAlgorithm;
    cache *l1, *l2, *l3;



    if (argc <= 1 || strcmp(argv[1], "-h") == 0) {
        printHelp();
        return 0;
    }

    fprintf(stdout, "%s\n", argv[13]);
    blocksize = atoi(argv[13]);
    fprintf(stdout, "%d\n", blocksize);
    l1 = create_cache(argv[2], argv[4], blocksize);
    l2 = create_cache(argv[6], argv[8], blocksize);
    l3 = create_cache(argv[10], argv[12], blocksize);

    tracefile = fopen(argv[15], "r");
    if(tracefile == NULL){
        fprintf(stderr, "Can't Open File");
        exit(1);
    }
    char input[14];
    while ( fscanf(tracefile, "%s", input)!= EOF ) {
        fprintf(stdout, "%s\n", input);
        unsigned long current = strtoull(input,NULL,0);
        fprintf(stdout, "%llu\n", current);
        fprintf(stdout, "%d\n", l1->num_sets);
        int index = current&(l1->num_sets )-1;;
        fprintf(stdout, "index %d\n", index);
        // o not valid
        if(l1->array[index] == 0){
            l1->array[index] = current;//input;
            l1->numMisses++;
            fprintf(stdout, "empty\n");
        }
        else{
            int cacheNum = search(current, index, l1, l2, l3);
            if(cacheNum == 0){
                l1->numMisses++;
                l2->numMisses++;
                l3->numMisses++;
                l3->array[index] = l2->array[index];
                l2->array[index] = l1->array[index];
                l1->array[index] = current;
                fprintf(stdout, "miss\n");
            }
            else if(cacheNum == 1){
                l1->numHits++;
                fprintf(stdout, "hit in l1\n");
            }
            else if(cacheNum == 2){
                l1->numMisses++;
                l2->numHits++;
                fprintf(stdout, "hit in l2\n");
            }

            else if(cacheNum == 3){
                l1->numMisses++;
                l2->numMisses++;
                l3->numHits++;
                fprintf(stdout, "hit in l3\n");
            }


        }
    }
        printInfo(l1);
        printInfo(l2);
        printInfo(l3);



        return 0;
    }

    int search(unsigned long long value, int index, cache *l1, cache *l2, cache *l3){
        if(l1->array[index] == value){
            return 1;
        }
        else if(l2->array[index] == value){
            return 2;
        }
        else if(l3->array[index] ==value){
            return 3;
        }
        else{
            return 0;
        }
    }


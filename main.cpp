//
//  main.cpp
//  RandomList
//
//  Created by Richard Huang on 11/16/13.
//  Copyright (c) 2013 Huang Corp. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "time.h"


#define LIST_SIZE 500
#define SHORT_DURATION 15 //timeframe (in seconds) where random order will stay the same

int main(int argc, const char * argv[])
{
    if (argc <3 || argc > 3)
    {
        std::cout<< "Usage: RandomList <offset> <limit> \n";
        return 0;
    }
    int offset = atoi(argv[1]);
    if (offset <0)
    {
        std::cout<< "Offset must be a positive number\n";
        return -1;
    }
    if (offset >= LIST_SIZE)
    {
        std::cout<< "Offset must be less than " << LIST_SIZE << "\n";
        return -1;
    }
    int limit = atoi(argv[2]);
    if (limit <0)
    {
        std::cout<< "Limit must be a positive number\n";
        return -1;
    }
    if (offset > LIST_SIZE)
    {
        std::cout<< "Limit must be less than or equal to " << LIST_SIZE << "\n";
        return -1;
    }
    if (offset + limit > LIST_SIZE)
    {
        std::cout<< "Offset + Limit must be less than or equal to " << LIST_SIZE << "\n";
        return -1;
    }
    
    void randomizeList(int useridList [], int size);
    void printArray(int useridList [], int size);
    int * getTopUsers(int useridList [], int offset, int limit);
    
    int useridList[LIST_SIZE] = {};
    
    randomizeList(useridList, LIST_SIZE);
    
    int * subArray = getTopUsers(useridList, offset, limit);
    //printArray(useridList, LIST_SIZE); // this will print out the whole randomlized array of userid's
    printArray(subArray, limit); //this prints the subArrays as limited by the arguments Offset and Limit
    return 0;
}

void randomizeList(int useridList [], int size)
{
    // the idea is to random pick an index and call that the pivot, then start filling in the randomized array
    // starting with the pivot. The next number to get picked is based on the sampling value (also picked at
    // random) and will change everytime. We need to keep track of which userid's have been picked (so we use
    // the reference array for that). Can be further optimized by using a bit to denote each of the 500 user ids
    // instead of the wasteful 500 int's.
    
    unsigned int seed = (unsigned int) time(NULL);
    
    int collision = 0; //keep track of number of collisions during sampling
    seed = seed/SHORT_DURATION; //seed will remain the same for the duration of SHORT_DURATION
    
    //std::cout << "Seed = " << seed << "\n";
    srand(seed);
    
    int pivot = rand() % LIST_SIZE;
    std::cout << "The pivot is " << pivot << "\n";
    
    int sampling = rand() % LIST_SIZE;
    if (sampling % 25 == 0) // add this to avoid too many collisions
    {
        sampling ++;
    }
    std::cout << "The sampling is " << sampling << "\n";
    
    
    int reference[LIST_SIZE] = {};
    
    for (int i = 0; i < LIST_SIZE; i++)
    {
        while (reference[pivot])
        {
            if (pivot < LIST_SIZE - 1)
            {
                collision++;
                pivot++;
            }
            else {
                collision++;
                pivot = 0;
            }
        }
        useridList[i] = pivot;
        reference[pivot] = 1;
        pivot = (pivot + sampling) % LIST_SIZE;
    }
    std::cout << "Number of collisions: " <<collision << "\n";
    
}

int * getTopUsers(int useridList[], int offset, int limit)
{
    int * retArray = new int[limit];
    for (int i = 0; i< limit; i++)
    {
        retArray[i] = useridList[offset+i];
    }
    return retArray;
}

void printArray(int useridList [], int size)
{
    for (int i=0; i<size; i++)
    {
        std::cout << i << ": " << useridList[i] << "\n ";
    }
}
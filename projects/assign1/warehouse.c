#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <assert.h>

// I used a struct to store the current bin number and when it was last accessed
// for a least recently used algorithm. The workbench was defined to be an array of 5 bins.
// From there, functions were implemented to check if a bin is on the workbench and if not, 
// remove the least recently used bin and fetch a new bin.

#define WORKBENCH_SIZE 5

// Bin struct to keep track of bin number and when last accessed
struct Bin {
	int binNum;
	int lastAccessed; // Least recently used
};

struct Bin workbench[WORKBENCH_SIZE]; // init workbench with max 5 bins
int currentUse = 0; // incremented when a bin is accessed

// determine which bin was least recently used
int findBinToRemove() {
	int leastRecentlyUsed = currentUse;
	int binToRemove = 0;

	// iterate through workbench to find least recently used bin
	for(int i = 0; i < WORKBENCH_SIZE; i++) {
		if(workbench[i].lastAccessed < leastRecentlyUsed) {
			leastRecentlyUsed = workbench[i].lastAccessed;
			binToRemove = i;
		}
	}

	return binToRemove;
}

// fetch a bin and update when last accessed
void accessBin(int binNum) {
	int binToRemove = findBinToRemove();
	currentUse++; // increment current use

	// check if bin is on workbench, if so then update timeLastAccessed and return
	for(int i = 0; i < WORKBENCH_SIZE; i++) {
		if(workbench[i].binNum == binNum) {
			workbench[i].lastAccessed = currentUse;
			return;
		}
	}

	// if bin not on workbench, remove least recently used bin and fetch new bin
	fetchBin(binNum, binToRemove); // from bench.c

	// update workbench with new bin
	workbench[binToRemove].binNum = binNum;
	workbench[binToRemove].lastAccessed = currentUse;
}

int main(int argc, char **argv) {
	if (argc<2) { printf("Please invoke as %s <order_file>\n",argv[0]); 	return 1; }
	if (!openOrder(argv[1])) { return 1; }
	do {
		int pn=nextPartNumber();
		int bin=pn/10;
		/* Replace the following code with a better implementation */
		
		accessBin(bin);

		/* End of simple implementation */
	} while(fetchNextPart());
	closeOrder();
	return 0;
}


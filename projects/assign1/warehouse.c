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
	int timeLastAccessed; // Least recently used
};

struct Bin workbench[WORKBENCH_SIZE]; // init workbench
int currentUse = 0; // incremented when a bin is accessed

// determine which bin was least recently used
int findBinToEvict() {
	int leastRecentlyUsed = currentUse;
	int binToEvict = 0;

	// iterate through workbench to find least recently used bin
	for(int i = 0; i < WORKBENCH_SIZE; i++) {
		if(workbench[i].timeLastAccessed < leastRecentlyUsed) {
			leastRecentlyUsed = workbench[i].timeLastAccessed;
			binToEvict = i;
		}
	}

	return binToEvict;
}

// fetch a bin and update when last accessed
void accessBin(int binNum) {
	currentUse++; // increment current use

	// check if bin is on workbench, if so then update timeLastAccessed and return
	for(int i = 0; i < WORKBENCH_SIZE; i++) {
		if(workbench[i].binNum == binNum) {
			workbench[i].timeLastAccessed = currentUse;
			return;
		}
	}

	// if bin not on workbench, evict least recently used bin and fetch new bin
	int binToEvict = findBinToEvict();
	fetchBin(binNum, binToEvict);

	// update workbench with new bin
	workbench[binToEvict].binNum = binNum;
	workbench[binToEvict].timeLastAccessed = currentUse;
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


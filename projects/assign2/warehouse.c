#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <assert.h>

// Clock algorithm implementation. Each bin is given a reference bit
// which is set to 1 when bin is accessed. When a new bin needs to be fetched,
// the algorithm removes the first bin with a reference bit set to 0. While finding,
// if a bin with the reference bit set to 1 is found, the bit is reset to 0 and the clock
// pointer increments to the next workbench slot.

#define WORKBENCH_SIZE 5

struct WorkbenchSlot {
	int bin_num; // store bin number
	int ref_bit; // store reference bit for clock alg
};

struct WorkbenchSlot workbench[WORKBENCH_SIZE];
int clock_ptr = 0; // pointer to current pos in clock array

// init workbench
void initWorkbench() {
	for (int i = 0; i < WORKBENCH_SIZE; i++) {
		workbench[i].bin_num = -1; // set all slots to empty
		workbench[i].ref_bit = 0; // set ref bits to zero
	}
}

int isBinOnWorkbench(int bin_num) {
	for (int i = 0; i < WORKBENCH_SIZE; i++) {
		if (workbench[i].bin_num == bin_num) {
			return i; // return index of bin
		}
	}
	return -1; // bin not found on workbench
}

void fetchBinToBench(int bin_num) {
	int slot = isBinOnWorkbench(bin_num);

	if (slot != -1) {
		workbench[slot].ref_bit = 1; // set ref bit to 1
		return;
	}

	// clock alg to find victim bin to replace
	while(1) {
		if (workbench[clock_ptr].ref_bit == 0) {
			printf("Replacing bin %d with bin %d\n", workbench[clock_ptr].bin_num, bin_num); // print debug

			// fetch new bin
			fetchBin(bin_num, clock_ptr);
			workbench[clock_ptr].ref_bit = 1; // set ref bit to 1
			workbench[clock_ptr].bin_num = bin_num; // set bin number

			// increment clock pointer
			clock_ptr = (clock_ptr + 1) % WORKBENCH_SIZE;
			return;
		} 
		else {
			// reset ref bit and inc clock pointer
			workbench[clock_ptr].ref_bit = 0;
			clock_ptr = (clock_ptr + 1) % WORKBENCH_SIZE;
		}
	}
}

int main(int argc, char **argv) {
	if (argc<2) { printf("Please invoke as %s <order_file>\n",argv[0]); 	return 1; }
	if (!openOrder(argv[1])) { return 1; }

	// init workbench
	initWorkbench();

	do {
		int pn=nextPartNumber();
		int bin=pn/10;
		/* Replace the following code with a better implementation */
		
		fetchBinToBench(bin);

		/* End of simple implementation */
	} while(fetchNextPart());
	closeOrder();
	return 0;
}


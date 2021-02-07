#include "basic.h"

int main(int argc,char **argv)
{
	char outfilename[64] = {0};
	if(argc != 3)
	{
		printf("Input num err.\n");
		exit(1);
	}
	int ed = atoi(argv[2]);
	simulate_data_generation_equlen_1delins(argv[1],ed,outfilename);
	return 0;
}



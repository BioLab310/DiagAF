/*
 * vector_filterMain.c
 *
 *  Created on: Nov 12, 2013
 *      Author: hxin
 */

//#ifndef BOOST_PP_IS_ITERATING
//#include "print.h"
#include <string>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include "vector_filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BATCH_RUN 1000000 

using namespace std;

#include "mask.h"

//char read[128];
//char ref[128];

char init_all_NULL[128] = "";

char read_t[128] __aligned__;// = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
char ref_t[128] __aligned__;// = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

int main(int argc, char* argv[]) {
	
	string *read_strs = new string [BATCH_RUN];
	string *ref_strs = new string [BATCH_RUN];
	bool *valid_buffex = new bool [BATCH_RUN];
	bool *valid_buffshd = new bool [BATCH_RUN];
	bool *valid_buff = new bool [BATCH_RUN];

	if (argc != 4) {
		printf("Usage: $>bin error\n");
		exit(1);
	}

	char *readfile_path = argv[1];
	int error = atoi(argv[2]);
	int methodsel = atoi(argv[3]);

	size_t lineLength;	
	size_t length;
	size_t read_len,ref_len;
	char* tempstr = NULL;

	long long unsigned int passNum = 0;
	long long unsigned int totalNum = 0;

	long long read_size;
	long long read_idx;
	bool stop = false;

	clock_t start,end;
	double runtime = 0;
	FILE *fp = NULL;
	if( (0!=access(readfile_path,R_OK|F_OK)) || (NULL==(fp=fopen(readfile_path,"r"))) )
    {
        printf("open %s failed, errno=%d\n",readfile_path,errno);
        return -1;
    }
	
	do {
		
		for (read_size = 0; read_size < BATCH_RUN; read_size++) {
		
			//get read
			getline(&tempstr, &lineLength, fp);
			length = strlen(tempstr);
			//Get rid of the new line character
			tempstr[length - 1] = '\0';
			
			if (feof(fp)) {
				stop = true;
				break;
			}
			read_strs[read_size].assign(tempstr);

			//get ref
			getline(&tempstr, &lineLength, fp);
			length = strlen(tempstr);
			//Get rid of the new line character
			tempstr[length - 1] = '\0';
			ref_strs[read_size].assign(tempstr);
			valid_buffshd[read_size] = false;
			valid_buff[read_size] = false;
		}

		start = clock();

		for (read_idx = 0; read_idx < read_size; read_idx++) {
			
			strncpy(read_t, init_all_NULL, 128);
			strncpy(ref_t, init_all_NULL, 128);

			read_len = read_strs[read_idx].length();

			if (read_len > 128)
				read_len = 128;
			strncpy(read_t, read_strs[read_idx].c_str(),read_len);

			ref_len = ref_strs[read_idx].length();
			//Get rid of the new line character
			if (ref_len > 128)
				ref_len = 128;
			strncpy(ref_t, ref_strs[read_idx].c_str(), ref_len);
			if(methodsel == 1)
			{
				if ( bit_vec_filter_sse1(read_t, ref_t, length, error) == 1)
				{
					valid_buff[read_idx] = true;
				}				
			}
			else if(methodsel == 2)
			{
				if(bit_vec_filter_sse2(read_t, ref_t, length, error) == 1)
				{
					valid_buff[read_idx] = true;
				}
			}
			else if(methodsel == 3)
			{
				if(bit_vec_filter_sse1_ex(read_t, ref_t, read_len,ref_len, error) == 1)
				{
					valid_buff[read_idx] = true;
				}
			}
			else if(methodsel ==4)
				if(bit_vec_filter_sse1_ex2(read_t, ref_t, read_len,ref_len, error) == 1)
				{
					valid_buff[read_idx] = true;
				}

				
		}

		end = clock();

		for (read_idx = 0; read_idx < read_size; read_idx++) {

			if (valid_buff[read_idx]) {
				passNum++;
			}
			totalNum++;
		}

		
//		elp_time.tms_stime += end_time.tms_stime - start_time.tms_stime;
//		elp_time.tms_utime += end_time.tms_utime - start_time.tms_utime;
		runtime += end-start;

		if (stop)
			break;

	} while (1);

	//fprintf(stderr, "end_of_file\n");
	
	printf("passNum:\t%lld\n", passNum);
	printf("totalNum:\t%lld\n", totalNum);
	printf("FNErrRate:\t%f\n",(double)(totalNum-passNum)/totalNum * 100);
	printf("total_time: %f\n", (double) runtime / CLOCKS_PER_SEC ); 

	if(fp != NULL)
	{
	   fclose(fp);
	}
	delete [] read_strs;
	delete [] ref_strs;
	delete []  valid_buffex;
	delete []  valid_buffshd;
	delete []  valid_buff;

	return 0;

}

//#endif

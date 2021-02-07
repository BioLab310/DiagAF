/*
 * basic.h
 *
 *  Created on: Jan 17, 2019
 *      Author: bio
 */

#ifndef BASIC_H_
#define BASIC_H_


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <cstring>
#include <vector>
#include <xmmintrin.h>
#include <string>
#include <time.h>
//#include "method.h"
using namespace std;
#define BUFF_LEN 256

char rand_generate_char();
char replace_rule(char a);
void ed_operate(char * line,int len);
void ed_operate(char * line,int len,int *pos, int *type);
uint32_t rangeEd(char *a,char * b,int32_t x,int32_t y,int32_t ed);
int simulate_data_generation(char * readfile_path,int ed,int modelsel,char * outfile_path);

void operate_Substitude(char * line,int len);
void operate_DelandIns(char * line,int len);
int simulate_data_generation_shd(char * readfile_path,int ed,char * outfile_path);
int simulate_data_generation_equlen_1sub(char * readfile_path,int ed,char * outfile_path);
int simulate_data_generation_equlen_1delins(char * readfile_path,int ed,char * outfile_path);



#endif /* BASIC_H_ */

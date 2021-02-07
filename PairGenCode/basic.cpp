/*
 * basic.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: bio
 */
#include "basic.h"


char rand_generate_char()
{
	switch(rand()%4)
	{
		case 0:
			return 'C';
			break;
		case 1:
			return 'G';
			break;
		case 2:
			return 'T';
			break;
		case 3:
			return 'A';
			break;
		default:
			break;
	}
}

char replace_rule(char a)
{
	switch(a)
	{
		case 'A':
			return 'C';
			break;
		case 'C':
			return 'G';
			break;
		case 'G':
			return 'T';
			break;
		case 'T':
			return 'A';
			break;
		default:
			break;
	}
}

void ed_operate(char * line,int len)   //计划将函数修改为   void ed_operate(char * line,int len, int &pos, int &type)  其中pos为编辑操作位置  type为标记操作类型
{
	int pos_ed=rand()%len;
	int type_ed=rand()%3; //0:sub;1:del;2:insert

	switch(type_ed)
	{
		case 0:
			line[pos_ed]=replace_rule(line[pos_ed]);
			break;
		case 1:
			for(int k=pos_ed;k<len-1;k++)
			{
				line[k]=line[k+1];
			}
			line[len-1]='\0';
			len--;
			break;
		case 2:
			for(int k=len-1;k>=pos_ed;k--)
			{
				line[k+1]=line[k];
			}
			line[pos_ed]=rand_generate_char();
			len++;
			line[len]='\0';
			break;
		default:
			break;
	}
}

void ed_operate(char * line,int len,int *pos, int *type)
{
	int pos_ed=rand()%len;
	int type_ed=rand()%3; //0:sub;1:del;2:insert

	switch(type_ed)
	{
		case 0:
			line[pos_ed]=replace_rule(line[pos_ed]);
			break;
		case 1:
			for(int k=pos_ed;k<len-1;k++)
			{
				line[k]=line[k+1];
			}
			line[len-1]='\0';
			len--;
			break;
		case 2:
			for(int k=len-1;k>=pos_ed;k--)
			{
				line[k+1]=line[k];
			}
			line[pos_ed]=rand_generate_char();
			len++;
			line[len]='\0';
			break;
		default:
			break;
	}
	*pos = pos_ed;
	*type = type_ed;
}

uint32_t rangeEd(char *a,char * b,int32_t x,int32_t y,int32_t ed)
{
	if((x-y > ed) || (x-y < -ed))
	{
		return ed+1;
	}
	uint32_t r;
	uint32_t ** m;
	m=(uint32_t **)malloc(sizeof(uint32_t *)*(x+1));
	for(int32_t i=0;i<x+1;i++)
	{
		m[i]=(uint32_t *)malloc(sizeof(uint32_t)*(y+1));
	}

	for(int32_t i=0;i<x+1;i++)
	{
		m[i][0]=i;
	}
	for(int32_t i=0;i<y+1;i++)
	{
		m[0][i]=i;
	}

	int32_t y_start;
	int32_t y_end;
	int32_t mid_ed=ed/2;
	int32_t l_bound;
	int32_t r_bound;
	int32_t y1=1;
	if(x<=y)
	{
		l_bound=mid_ed;
		r_bound=(y-x)+mid_ed;
	}
	else
	{
		l_bound=(x-y)+mid_ed;
		r_bound=mid_ed;
	}
	for(int32_t i=1;i<x+1;i++)
	{
		y_start=max(y1,i-l_bound);
		y_end=min(i+r_bound,y);
		int32_t line_check = ed+1;
		for(int32_t j=y_start;j<=y_end;j++)
		{
			uint32_t tmp=0;
			if(j==i-l_bound && j==i+r_bound)
			{
				if(a[i-1]!=b[j-1])
				{
					tmp=1;
				}
				m[i][j]=m[i-1][j-1]+tmp;
			}
			else if(j==i-l_bound)
			{
				if(a[i-1]!=b[j-1])
				{
					tmp=1;
				}
				m[i][j]=min(m[i-1][j]+1,m[i-1][j-1]+tmp);
			}
			else if(j==i+r_bound)
			{
				if(a[i-1]!=b[j-1])
				{
					tmp=1;
				}
				m[i][j]=min(m[i][j-1]+1,m[i-1][j-1]+tmp);
			}
			else
			{
				if(a[i-1]!=b[j-1])
				{
					tmp=1;
				}
				m[i][j]=min(m[i][j-1]+1,m[i-1][j-1]+tmp);
				m[i][j]=min(m[i][j],m[i-1][j]+1);
			}
			if(m[i][j] < line_check)
			{
				line_check = m[i][j];
			}
		}
		if(line_check == (ed+1))
		{
			for(int32_t i=0;i<x+1;i++)
			{
				free(m[i]);
			}
			free(m);
			return ed+1;
		}
	}
	r = m[x][y];
	for(int32_t i=0;i<x+1;i++)
	{
		free(m[i]);
	}
	free(m);
	return r;
}

int simulate_data_generation(char * readfile_path,int ed,int modelsel,char * outfile_path)
{
	//modelsel == 1 generate the seq with editdis = 1~ed
	//modelsel == 0 generate the seq with editdis == ed
    FILE *fp = NULL;
    char *line = NULL;
    char *line_tmp = NULL;

    line = (char*)malloc(sizeof(char)*BUFF_LEN);
    line_tmp = (char*)malloc(sizeof(char)*BUFF_LEN);
    size_t line_len = BUFF_LEN;
    if( (0!=access(readfile_path,R_OK|F_OK)) || (NULL==(fp=fopen(readfile_path,"r"))) )
    {
        printf("open %s failed, errno=%d\n",readfile_path,errno);
        return -1;
    }

    ofstream outfile;
    char outname[64] = {0};
    char numstr[4];
    strcat(outname,readfile_path);
    strcat(outname,"_t2_");
    sprintf(numstr,"%d",ed);
    strcat(outname,numstr);
    outfile.open(outname,ios::out);
    strcat(outfile_path,outname);

    int len = 0;
    int count=0;
    int ra,edfinal;
    while( (len=getline(&line,&line_len,fp))>0 )
    {
    	if(count%4==1)
    	{
//			cout << len << "	" << line << endl;

			for(int j=0;j<len;j++)
			{
				if(line[j]>'a')
				{
					line[j]-=32;
				}
				if(line[j]!='A'&&line[j]!='C'&&line[j]!='G'&&line[j]!='T')
				{
					line[j]='A';
				}
			}
			outfile << line << endl;
			ra = rand() % ed + 1;
			edfinal = modelsel ? ra : ed;
			strcpy(line_tmp,line);
			while(strcmp(line_tmp,line) == 0)
			{
				for(int j=0; j<edfinal; j++)
				{
					ed_operate(line,strlen(line));
				}
			}
			outfile << line << endl;
    	}
    	count++;
    }

    cout << count << endl;
    if(fp != NULL)
    {
        fclose(fp);
    }

    free(line); //记得释放资源
    free(line_tmp);
    return count/4;
}

//shd_srs使用  调用一次编辑距离+1
void operate_Substitude(char * line,int len,int *pos)
{
	int pos_ed=rand()%len;
	line[pos_ed]=replace_rule(line[pos_ed]);
	*pos = pos_ed;
}
//shd_srs使用  调用一次编辑距离+2
void operate_DelandIns(char * line,int len ,int *del_pos,int *ins_pos)
{
	int len_tmp = len;
	int pos_del = rand() % len_tmp;
	for(int k=pos_del;k<len-1;k++)
	{
		line[k]=line[k+1];
	}
	line[len-1]='\0';
	len--;
	*del_pos = pos_del;
	int pos_ins = rand() % len_tmp;
	while(pos_del == pos_ins)
	{
		pos_ins = rand() % len_tmp;
	}
	for(int k=len-1;k>=pos_ins;k--)
	{
		line[k+1]=line[k];
	}
	line[pos_ins]=rand_generate_char();
	len++;
	line[len]='\0';
	*ins_pos = pos_ins;

}

int simulate_data_generation_shd(char * readfile_path,int ed,char * outfile_path)	//生成不等长数据集
{
    FILE *fp = NULL;
    char *line = NULL;
    char *line_tmp = NULL;
    uint32_t ed_record[3][BUFF_LEN] = {0};
    line = (char*)malloc(sizeof(char)*BUFF_LEN);
    line_tmp = (char*)malloc(sizeof(char)*BUFF_LEN);
    size_t line_len = BUFF_LEN;
    if( (0!=access(readfile_path,R_OK|F_OK)) || (NULL==(fp=fopen(readfile_path,"r"))) )
    {
        printf("open %s failed, errno=%d\n",readfile_path,errno);
        return -1;
    }

    ofstream outfile;
    char outname[64] = {0};
    char numstr[4];
    strcat(outname,readfile_path);
    strcat(outname,"_ed_");
    sprintf(numstr,"%d",ed);
    strcat(outname,numstr);
    outfile.open(outname,ios::out);
    strcat(outfile_path,outname);

    int len = 0;
    int count=0;
    int pos,type;
    while( (len=getline(&line,&line_len,fp))>0 )
    {
    	if(count%4==1)
    	{
			for(int j=0;j<len;j++)
			{
				if(line[j]>'a')
				{
					line[j]-=32;
				}
				if(line[j]!='A'&&line[j]!='C'&&line[j]!='G'&&line[j]!='T')
				{
					line[j]='A';
				}
			}
			outfile << line << endl;
			strcpy(line_tmp,line);
			while(rangeEd(line_tmp,line,strlen(line_tmp),strlen(line),ed+1) != ed)
			{
				ed_operate(line,strlen(line), &pos, &type);
				ed_record[type][pos]++;
			}
			outfile << line << endl;
    	}
    	count++;
    }

    cout << count << endl;
    if(fp != NULL)
    {
        fclose(fp);
    }
    printf("%s edit operation record : \n",outname);
    for(int i = 0; i < 3; i++)
    {
    	for(int j = 0; j < BUFF_LEN; j++)
    	{
    		printf("%d  ",ed_record[i][j]);
    	}
    	printf("\n");
    }

    free(line); //记得释放资源
    free(line_tmp);
    return count/4;
}

int simulate_data_generation_equlen_1sub(char * readfile_path,int ed,char * outfile_path) //生成等长数据集
{
    FILE *fp = NULL;
    char *line = NULL;
    char *line_tmp = NULL;
    uint32_t ed_record[3][BUFF_LEN] = {0};
    line = (char*)malloc(sizeof(char)*BUFF_LEN);
    line_tmp = (char*)malloc(sizeof(char)*BUFF_LEN);
    size_t line_len = BUFF_LEN;
    if( (0!=access(readfile_path,R_OK|F_OK)) || (NULL==(fp=fopen(readfile_path,"r"))) )
    {
        printf("open %s failed, errno=%d\n",readfile_path,errno);
        return -1;
    }

    ofstream outfile;
    char outname[64] = {0};
    char numstr[4];
    strcat(outname,readfile_path);
    strcat(outname,"_ed_");
    sprintf(numstr,"%d",ed);
    strcat(outname,numstr);
    outfile.open(outname,ios::out);
    strcat(outfile_path,outname);

    int len = 0;
    int count=0;
    int del_pos,ins_pos,sub_pos;
    while( (len=getline(&line,&line_len,fp))>0 )
    {
    	if(count%4==1)
    	{
			for(int j=0;j<len;j++)
			{
				if(line[j]>'a')
				{
					line[j]-=32;
				}
				if(line[j]!='A'&&line[j]!='C'&&line[j]!='G'&&line[j]!='T')
				{
					line[j]='A';
				}
			}
			outfile << line << endl;
			strcpy(line_tmp,line);

			while((ed - rangeEd(line_tmp,line,strlen(line_tmp),strlen(line),ed+1)) >= 2)
			{
				operate_DelandIns(line,strlen(line),&del_pos,&ins_pos);
				ed_record[1][del_pos]++;
				ed_record[2][ins_pos]++;
			}
			while( rangeEd(line_tmp,line,strlen(line_tmp),strlen(line),ed+1) != ed)
			{
				operate_Substitude(line,strlen(line),&sub_pos);
				ed_record[0][sub_pos]++;
			}
			outfile << line << endl;
    	}
    	count++;
    }

    if(fp != NULL)
    {
        fclose(fp);
    }
    for(int i = 0; i < 3; i++)
    {
    	for(int j = 0; j < BUFF_LEN; j++)
    	{
    		printf("%d  ",ed_record[i][j]);
    	}
    	printf("\n");
    }

    free(line); //记得释放资源
    free(line_tmp);
    return count/4;
}

int simulate_data_generation_equlen_1delins(char * readfile_path,int ed,char * outfile_path) //生成等长数据集
{
    FILE *fp = NULL;
    char *line = NULL;
    char *line_tmp = NULL;
    uint32_t ed_record[3][BUFF_LEN] = {0};
    line = (char*)malloc(sizeof(char)*BUFF_LEN);
    line_tmp = (char*)malloc(sizeof(char)*BUFF_LEN);
    size_t line_len = BUFF_LEN;
    if( (0!=access(readfile_path,R_OK|F_OK)) || (NULL==(fp=fopen(readfile_path,"r"))) )
    {
        printf("open %s failed, errno=%d\n",readfile_path,errno);
        return -1;
    }

    ofstream outfile;
    char outname[64] = {0};
    char numstr[4];
    strcat(outname,readfile_path);
    strcat(outname,"_ed_");
    sprintf(numstr,"%d",ed);
    strcat(outname,numstr);
    outfile.open(outname,ios::out);
    strcat(outfile_path,outname);

    int len = 0;
    int count=0;
    int del_pos,ins_pos,sub_pos;
    while( (len=getline(&line,&line_len,fp))>0 )
    {
    	if(count%4==1)
    	{
			for(int j=0;j<len;j++)
			{
				if(line[j]>'a')
				{
					line[j]-=32;
				}
				if(line[j]!='A'&&line[j]!='C'&&line[j]!='G'&&line[j]!='T')
				{
					line[j]='A';
				}
			}
			outfile << line << endl;
			strcpy(line_tmp,line);

			if((ed - rangeEd(line_tmp,line,strlen(line_tmp),strlen(line),ed+1)) >= 2)
			{
				operate_DelandIns(line,strlen(line),&del_pos,&ins_pos);
				ed_record[1][del_pos]++;
				ed_record[2][ins_pos]++;
			}
			while( rangeEd(line_tmp,line,strlen(line_tmp),strlen(line),ed+1) != ed)
			{
				operate_Substitude(line,strlen(line),&sub_pos);
				ed_record[0][sub_pos]++;
			}
			outfile << line << endl;
    	}
    	count++;
    }

    if(fp != NULL)
    {
        fclose(fp);
    }
    for(int i = 0; i < 3; i++)
    {
    	for(int j = 0; j < BUFF_LEN; j++)
    	{
    		printf("%d  ",ed_record[i][j]);
    	}
    	printf("\n");
    }

    free(line); //记得释放资源
    free(line_tmp);
    return count/4;
}

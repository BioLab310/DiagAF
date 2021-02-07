#include "basic.h"

int main(int argc,char **argv)   //test whether PairFile Edit Distance equal to
{
        size_t len_tmp = 128;
        char *read;
        char *ref;
        read = (char*)malloc(sizeof(char)*len_tmp);
        ref = (char*)malloc(sizeof(char)*len_tmp);
        char *readfile_path = NULL;
        uint32_t read_len = 0,ref_len = 0;
        int32_t edset;
        for(uint32_t i=1;i<argc;i=i+2)
        {
                if(argv[i][0]=='-'&&argv[i][1]=='r')//reference
                {
                        readfile_path = argv[i+1];
                }
                if(argv[i][0]=='-'&&argv[i][1]=='e')//reference
                {
                        edset = atoi(argv[i+1]);
                }
        }
        FILE *fp = NULL;
    if( (0!=access(readfile_path,R_OK|F_OK)) || (NULL==(fp=fopen(readfile_path,"r"))) )
    {
        printf("open %s failed, errno=%d\n",readfile_path,errno);
        return -1;
    }
    uint32_t ret = 0;
    while(1)
    {
        if(feof(fp))
        {
                break;
        }
                read_len = getline(&read,&len_tmp,fp);
                ref_len = getline(&ref,&len_tmp,fp);
                if(read_len != ref_len)
                {
                        printf("Sequence length wrong!\n");
                        exit(-1);
                }
                read[strlen(read)-1] = '\0';
                ref[strlen(ref)-1] = '\0';

                ret = rangeEd(read,ref,strlen(read),strlen(ref),edset+1);
                if(ret != edset)
                {
                        printf("Edit Distance Wrong!\n");
                        exit(-1);
                }
    }
    return 0;
}


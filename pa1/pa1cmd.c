#include "base/main/main.h"
#include "pa1.h"
#include <ctype.h>

ABC_NAMESPACE_IMPL_START

static int pa1_iterateCommand(Abc_Frame_t * pAbc, int argc, char ** argv);
static int pa1_andtreeCommand(Abc_Frame_t * pAbc, int argc, char ** argv);

void pa1_iterateInit(Abc_Frame_t * pAbc) 
{
    Cmd_CommandAdd( pAbc, "Various", "iteratentk", pa1_iterateCommand, 0);
}
void pa1_andtreeInit(Abc_Frame_t * pAbc) 
{
    Cmd_CommandAdd( pAbc, "Various", "andtree", pa1_andtreeCommand, 0);
}

int pa1_iterateCommand(Abc_Frame_t * pAbc, int argc, char ** argv) 
{
    int c, result;

    Extra_UtilGetoptReset();
    while ((c = Extra_UtilGetopt(argc, argv, "vh")) != EOF) {
        switch (c) 
	   {
            case 'h':
                 goto usage;
            default:
                 goto usage;
	   }
    }

    result = pa1_iterateAbc(pAbc);

    return 0;

usage:
    Abc_Print(-2, "usage: iteratentk [-h]\n");
    Abc_Print(-2, "\t iterate network command in pa1\n");
    Abc_Print(-2, "\t-h : print the command usage\n" );
    return 1;
}

int pa1_andtreeCommand(Abc_Frame_t * pAbc, int argc, char ** argv) 
{
    int result;
    int num = 5;


    if(argc == 2 || argc == 3)
    {
        if(strcmp( argv[0], "andtree" ) != 0)
            goto usage;
        if(strcmp( argv[1], "-S" ) != 0)
            goto usage;
        if(argc == 3)
        {
            num = atoi(argv[2]);
            if(num <= 0)
            {
                goto usage;
            }
        }
    }
    else
    {
        goto usage;
    }

    result = pa1_andtreeAbc(pAbc, num);

    return 0;

usage:
    Abc_Print(-2, "usage: andtree [-h] [-S num]\n");
    Abc_Print(-2, "\t identify the AND-TREE structures in the AIG network command in pa1\n");
    Abc_Print(-2, "\t-S num : a positive integer, which should be greater than or equal to 1, indentify the lower bound size of the AND trees(default 5).\n" );
    return 1;
}
#include "base/main/main.h"
#include "andtree.h"

ABC_NAMESPACE_IMPL_START

int pa1_iterate(Abc_Ntk_t * pNtk);
int pa1_andtree(Abc_Ntk_t * pNtk, int num);

int pa1_iterateAbc(Abc_Frame_t * pAbc)
{
	Abc_Ntk_t * pNtk;
	int result;

	pNtk = Abc_FrameReadNtk(pAbc);

	if(pNtk == NULL)
	{
		Abc_Print(-1, "Getting the target network has failed.\n");
		return 0;
	}

	result = pa1_iterate(pNtk);

	return result;
}

int pa1_andtreeAbc(Abc_Frame_t * pAbc, int num)
{
	Abc_Ntk_t * pNtk;
	int result;

	pNtk = Abc_FrameReadNtk(pAbc);

	if(pNtk == NULL)
	{
		Abc_Print(-1, "Getting the target network has failed.\n");
		return 0;
	}

	result = pa1_andtree(pNtk, num);

	return result;
}

int pa1_iterate(Abc_Ntk_t * pNtk) 
{
	if(!Abc_NtkIsStrash(pNtk))
	{
		Abc_Print(-1, "This command is only applicable to strashed networks.\n");
		return 0;
	}

	Abc_Obj_t * pObj;
	int i;
	Abc_NtkForEachObj(pNtk, pObj, i)
	{
		printf("Id:%5d,   Name:%10s,   NodeType:%3d,   NodeLevel:%3d", pObj->Id, Abc_ObjName(pObj), pObj->Type, pObj->Level);
		Vec_Ptr_t * vNodes = Abc_NodeGetFaninNames( pObj );
		int Fanin_size = Abc_ObjFaninNum(pObj);
		for(int j=0; j<Fanin_size; ++j)
		{
			printf(",   FiName:%10s", (char *) vNodes->pArray[j]);
			if(j == 0) printf(",   FaninPhase:  %d", pObj->fCompl0);
			else 	   printf(",   FaninPhase:  %d", pObj->fCompl1);
		}
		printf("\n");
	}
	return 1;
}

int pa1_andtree(Abc_Ntk_t * pNtk, int num) 
{
	if(!Abc_NtkIsStrash(pNtk))
	{
		Abc_Print(-1, "This command is only applicable to strashed networks.\n");
		return 0;
	}

	char * s = (char *)malloc(sizeof(char) * 100000);
	s[0] = '\0';
	Abc_Obj_t * pObj;
	int i;
	Abc_NtkForEachObj(pNtk, pObj, i)
	{
		sprintf(s + strlen(s), "%s %d", Abc_ObjName(pObj), pObj->Level);
		Vec_Ptr_t * vNodes = Abc_NodeGetFaninNames( pObj );
		int Fanin_size = Abc_ObjFaninNum(pObj);
		for(int j=0; j<Fanin_size; ++j)
		{
			sprintf(s + strlen(s), " %s ", (char *)vNodes->pArray[j]);
			if(j == 0) sprintf(s + strlen(s), "%d", pObj->fCompl0);
			else 	   sprintf(s + strlen(s), "%d", pObj->fCompl1);
		}
		sprintf(s + strlen(s), " ;\n");
	}

	ilovecplusplus(s, num);
	
	return 1;
}


ABC_NAMESPACE_IMPL_END

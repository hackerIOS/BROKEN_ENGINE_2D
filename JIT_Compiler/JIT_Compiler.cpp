//BEC Compiler

#include <iostream>
#include <Program_Plus.h>
#include <vector>
#include <stdio.h>
using namespace std;

int EXPLAINLINE=1;//EXPLAINLINE=1 FALSE
string ReadBECFile;
int AnalysisLoop=0;



vector<string>Data;
int DataLen=0;

vector<string>S_Func;
int S_FUNC_NUM=0;


vector<char>TempData;
int TempDataLen=0;

string T_STR="string";
string T_INT="int";
//vector<int>KW_INT;
struct KW_INT1{
	int INT_DATA;
	string INT_NAME;
};

vector<struct KW_INT1>KW_INT;
int KW_INT_NUM=0;



struct KW_STRING1{
	string STR_DATA;
	string STR_NAME;
};

vector<struct KW_STRING1>KW_STRING;
int KW_STRING_NUM=0;




struct KW_DATA1{
	string DATA_KW_NAME;
	int DATA_GLOBAL_LOCAL;//if =0 -> GLOBAL
	string DATA_LOCAL_FUNC;
	int DATA_INT;
	string DATA_STR;
	float DATA_FLOAT;
};

vector<struct KW_DATA1>KW_DATA;
int KW_DATA_NUM=0;
int KW_DATA_INFUNC=0;//0 not in function 1 in function


int AddFunc(){
	S_Func.resize(2);
	S_Func[0]="S_DebugLog";
	//S_Func[1]="S_Create
}





int GenerateLogic(){
	cout<<DataLen<<endl;
	for (int LoopRead=0;LoopRead!=DataLen-1;){
		if (Data[LoopRead]==T_INT){
			KW_INT.resize(KW_INT_NUM+1);
			
			KW_INT[KW_INT_NUM].INT_NAME=Data[LoopRead+1];
			
			KW_INT[KW_INT_NUM].INT_DATA=atoi(Data[LoopRead+2].c_str());
			
			
			
			KW_DATA.resize(KW_DATA_NUM+1);
			KW_DATA[KW_DATA_NUM].DATA_KW_NAME=Data[LoopRead+1];
			KW_DATA[KW_DATA_NUM].DATA_GLOBAL_LOCAL=0;
			KW_DATA[KW_DATA_NUM].DATA_INT=atoi(Data[LoopRead+2].c_str());
			KW_DATA_NUM++;
			
			
			LoopRead=LoopRead+2;
			KW_INT_NUM++;
			
			
			
		}else if (Data[LoopRead]==T_STR){
			KW_STRING.resize(KW_STRING_NUM+1);
			KW_STRING[KW_STRING_NUM].STR_DATA=Data[LoopRead+2];
			KW_STRING[KW_STRING_NUM].STR_NAME=Data[LoopRead+1];
			
			
			
			
			KW_DATA.resize(KW_DATA_NUM+1);
			KW_DATA[KW_DATA_NUM].DATA_KW_NAME=Data[LoopRead+1];
			KW_DATA[KW_DATA_NUM].DATA_GLOBAL_LOCAL=0;
			KW_DATA[KW_DATA_NUM].DATA_STR=Data[LoopRead+2];
			KW_DATA_NUM++;
			
			
			
			LoopRead=LoopRead+2;
			KW_STRING_NUM++;
		}
		LoopRead++;
		cout<<LoopRead<<endl;
	}
	cout<<"success"<<endl;
}








int AnalysisWord(){
	Data.resize(DataLen+1);
	//char* Temp1=TempData;
	string CopyData(TempData.begin(),TempData.end());
	
	Data[DataLen]=CopyData;
	cout<<CopyData<<endl;
	//Clear TempData
	TempData.clear();
	TempDataLen=0;
	DataLen++;
}


int CmpString(){
	
	TempData.resize(TempDataLen+1);
	TempData[TempDataLen]=ReadBECFile[AnalysisLoop];
	
	TempDataLen++;
}


int Analysis(){
	for (;ReadBECFile.length()!=AnalysisLoop;){
		if (ReadBECFile[AnalysisLoop]>=0x41 && ReadBECFile[AnalysisLoop]<=0x5a){
			//cout<<ReadBECFile[AnalysisLoop];
			CmpString();
		}else if (ReadBECFile[AnalysisLoop]>=0x61 &&ReadBECFile[AnalysisLoop]<=0x7a){
			CmpString();
		}else if (ReadBECFile[AnalysisLoop]==' '){
			AnalysisWord();
			//30 39
		}else if (ReadBECFile[AnalysisLoop]>=0x30 && ReadBECFile[AnalysisLoop]<=0x39){
			CmpString();
			
		}else if (ReadBECFile[AnalysisLoop]=='/'){
			if (ReadBECFile[AnalysisLoop+1]=='/'){
				AnalysisWord();
				EXPLAINLINE=0;
				AnalysisLoop=AnalysisLoop+2;
				
				for (;EXPLAINLINE!=1;){
					if (ReadBECFile[AnalysisLoop]=='\n' || ReadBECFile.length()==AnalysisLoop){
						AnalysisLoop--;
						EXPLAINLINE==1;
						break;
					}else {
						AnalysisLoop++;
					}
				}
			}else{
				CmpString();
			}
		}else if (ReadBECFile[AnalysisLoop]=='"'){
			for (;ReadBECFile[AnalysisLoop+1]!='"';){
				
				AnalysisLoop++;
			}
		}else if (ReadBECFile[AnalysisLoop]=='\n'){
			AnalysisWord();
		}
		AnalysisLoop++;
	}
    if (ReadBECFile.length()==AnalysisLoop){
		AnalysisWord();
	}
}
	

int main(int argc,char*argv[]){
	ReadBECFile=PP_ReadFile("NewScript2.bec");
	Analysis();
	GenerateLogic();
	cout<<KW_DATA[0].DATA_STR<<endl;
	return 0;
}
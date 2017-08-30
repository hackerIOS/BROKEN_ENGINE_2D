//BROKEN ENGINE Renderer
//v3.0

//Update Time 2017 4 27 13:07

//success 1000line in 2017.4.18

//Update inf:

//switch head file Path
//ready to Add Node Analysis
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>

#include "BE_FW/Program_Plus.h"

#include <iostream>
using namespace std;

#include "BE_FW/rapidxml.hpp"
#include "BE_FW/rapidxml_print.hpp"
#include "BE_FW/rapidxml_utils.hpp"

int EDITOR_MODE=0;//EDITOR MODE=0 GAME MODE =1
int LockFrameEnableORN=0;//0=disable 1=Enable
int LockFrameRate_GB=60;//LockFrameRate_GLOBAL

//BASIC EDITOR TOOLS
string BE_MAIN_VOICE="BE_MAIN_VOICE";
string BE_MAIN_CAMERA="BE_MAIN__CAMERA";
string BE_MAIN_OBJECT="BE_MAIN_OBJECT";
string BE_MAIN_SELECT="BE_MAIN_SELECT";
string BE_MAIN_TRANSLATE="BE_MAIN_TRANSLATE";
string BE_MAIN_ROTATION="BE_MAIN_ROTATION";
string BE_MAIN_ZOOM="BE_MAIN_ZOOM";



int TEX_PIC=0;//PICTURE
int TEX_DM=1;//DEBUG MESSAGE
int TEX_FONT=2;//SAMPLE FONT
int TEX_BSCLO=3;//BASIC COLOR


struct SelectoperaType{
	
	int SELECT_TYPE;
	int SELECT_TYPE_NOT=0;//NO SELECT
	int SELECT_TYPE_TSL=1;//TRANSLATE
	int SELECT_TYPE_ROT=2;//ROTATION
	int SELECT_TYPE_ZOOM=3;//ZOOM
}Select_Opera_Type;


SDL_Rect RECT_TSL;//TRANSLATE RECT
SDL_Rect RECT_ROT;//ROTATION RECT
SDL_Rect RECT_ZOOM;//ZOOM RECT

//INITIAL RENDER
SDL_Window*win=NULL;
SDL_Renderer*Rend=NULL;
SDL_Surface*Sur=NULL;
TTF_Font*fonts=NULL;
//*******


//NewThread
int InputThread(void *ptr);
SDL_Event InputEvent;

int TouchX,TouchY;//Get Touch  xy

int SCREEN_W,SCREEN_H;//GetScreenxy

//Texture Data INITIAL


struct ObjectInformation{
	int INF_OBJ_X;
	int INF_OBJ_Y;
	int INF_OBJ_W;
	int INF_OBJ_H;
	//SDL_Rect INF_OBJ_RECT;
	double INF_OBJ_ANGLE;
	int DisplayLayerNum;
	string TextureName;
	int INF_DisplayORN=0;//0 is Display 1 is hide
};

map<string,struct ObjectInformation>OBJ_INF;
map<string,struct ObjectInformation>::iterator OBJ_INF_POS;

int TexTotal=0;


//vector<SDL_Texture*>Tex;

/*vector<string>RendererOrder;
int RO_Data_Num=0;
*/

map<string,SDL_Texture*>Tex_Data;
//	string DisplayID;

vector<string>DisplayID;
int DisplayID_Num=0;

/*
map<string,int>DisplayLayer;
int DisplayLayerNum=0;
*/


//in Editor Mode min value >Basic Texture Num
//in Game Mode min value =0


//VOICE Data INITIAL
struct LoadVoice{
	//SDL_
	Mix_Chunk*VoiceData=NULL;
	int VoicePosX;
	int VoicePosY;
};
//****



//Analysis Init Part************
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
string T_FLOAT="float";



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
//***




xml_document<>AXS_DOC;

vector<string>GB_Variable;
int GB_Variable_Num=0;


vector<string>StartFunctionName;
int StartFunctionName_Num=0;

//Function Segment**************
int ChildINDataSet(xml_node<>*FatherNode){
	//FatherNode->value();
	StartFunctionName_Num++;
			StartFunctionName.resize(StartFunctionName_Num);
			
			StartFunctionName[StartFunctionName_Num-1]=FatherNode->value();
	return 0;
}


int ChildINFunctionSet(xml_node<>*FatherNode){
	
	
	return 0;
}



int AnalyseXMLSet(string RootPathFileName){
	file<>AXS_FDOC(RootPathFileName.c_str());
	
	AXS_DOC.parse<0>(AXS_FDOC.data());
	xml_node<>*MainNode;
	//*******VariableSet Part
	MainNode=AXS_DOC.first_node("VariableSet");
	ofstream Output("XML_Analysis_Result.XML");
	
	xml_node<>*LoopVariableNode;//=MainNode->first_node("Variable");
		
		xml_node<>*SNode;//=LoopVariableNode->first_node("Data");
	//Jump in VariableSet
	
	
	
	if (MainNode->first_node()!=NULL){
		//xml_node<>*VariableLocalData=MainNode
		
		
		
		//have something Done
		/*GB_Variable_Num++;
		GB_Variable.resize(GB_Variable_Num);
		GB_Variable[GB_Variable_Num-1]=SNode->value();
		*/
		//while (LoopVariableNode=LoopVariableNode->next_sibling()!=NULL){
			
		for (LoopVariableNode=MainNode->first_node("Variable");
		LoopVariableNode!=NULL;){
			
			GB_Variable_Num++;
			GB_Variable.resize(GB_Variable_Num);
			SNode=LoopVariableNode->first_node("Data");
			GB_Variable[GB_Variable_Num-1]=SNode->value();
			LoopVariableNode=LoopVariableNode->next_sibling();
		}
		/*string outfile;
		outfile=GB_Variable[0];*/
		
		Output<<GB_Variable[0]<<GB_Variable[1]<<GB_Variable[2]<<GB_Variable[3];
		
		//*switch to Start Node
	}
	
	MainNode=AXS_DOC.first_node("Start");
	if (MainNode->first_node()!=NULL){
		
		
		for (LoopVariableNode=MainNode->first_node("Function");LoopVariableNode!=NULL;){
			StartFunctionName_Num++;
			StartFunctionName.resize(StartFunctionName_Num);
			SNode=LoopVariableNode->first_node("FunctionName");
			
			StartFunctionName[StartFunctionName_Num-1]=SNode->value();
			
			for (xml_node<>*ReadINData=LoopVariableNode->first_node("IN");ReadINData!=NULL;){
				SNode=ReadINData->first_node();
				string TempSNodeName=SNode->name();
				if (TempSNodeName=="Data"){
				//if (ReadINData->first_node()->name()=="Data"){
					//SNode=ReadINData->first_node("Data");
					//ChildINDataSet(SNode);
				
					StartFunctionName_Num++;
			StartFunctionName.resize(StartFunctionName_Num);
			//SNode=LoopVariableNode->first_node("FunctionName");
			
			StartFunctionName[StartFunctionName_Num-1]=SNode->value();
			
				}else if (TempSNodeName=="Function"){
					
				}else if (TempSNodeName=="GBVariable"){
					
				}
				
				ReadINData=ReadINData->next_sibling();
			}
			
			
			
			LoopVariableNode=LoopVariableNode->next_sibling();
		}
	}
	Output<<StartFunctionName[0]<<StartFunctionName[1]<<StartFunctionName[2]<<StartFunctionName[3];
	
	
	return 0;
}


/*
int ReadChangeXML(){
	
	//PP_DOC.first_node("V");
	string GetData;
	xml_node<>*SearchNode;
	xml_node<>*VKC;
	SearchNode=doc.first_node("VariableSet");
	xml_node<>*VK;
	VK=SearchNode->first_node("Variable");
	VKC=VK->first_node();
	
	GetData=VKC->value();
	cout<<GetData<<endl;
	//VK->next_sibling();
	VKC=VK->first_node("Type");
	GetData=VKC->value();
	cout<<GetData<<endl;
	return 0;
}
int CreateT(){
	
	xml_node<>*rot=doc.allocate_node(node_element,"VariableSet",NULL);
	doc.append_node(rot);
	xml_node<>*newvariable=doc.allocate_node(node_element,"Variable",NULL);
	xml_node<>*newvariableid=doc.allocate_node(node_element,"ID","0");
	xml_node<>*newvariabletype=doc.allocate_node(node_element,"Type","int");
	
	xml_node<>*newvariabledata=doc.allocate_node(node_element,"Data","0");
	
	//xml_node<>*NewTypeData=doc.allocate_node(node_pi,doc.allocate_string("
	
	
	newvariable->append_node(newvariableid);
	newvariable->append_node(newvariabletype);
	
	rot->append_node(newvariable);
	string T;
	print(back_inserter(T),doc,0);
	cout<<T<<endl;
	//PP_DOC=doc;
}




*/

//XML Analysis




//Analysis Part



int GenerateLogic(){
	//cout<<DataLen<<endl;
	for (int LoopRead=0;LoopRead!=DataLen-1;){
		if (Data[LoopRead]==T_INT){
			KW_DATA.resize(KW_DATA_NUM+1);
			KW_DATA[KW_DATA_NUM].DATA_KW_NAME=Data[LoopRead+1];
			KW_DATA[KW_DATA_NUM].DATA_GLOBAL_LOCAL=0;
			KW_DATA[KW_DATA_NUM].DATA_INT=atoi(Data[LoopRead+2].c_str());
			KW_DATA_NUM++;
			LoopRead=LoopRead+2;

			
		}else if (Data[LoopRead]==T_STR){
			KW_DATA.resize(KW_DATA_NUM+1);
			KW_DATA[KW_DATA_NUM].DATA_KW_NAME=Data[LoopRead+1];
			KW_DATA[KW_DATA_NUM].DATA_GLOBAL_LOCAL=0;
			KW_DATA[KW_DATA_NUM].DATA_STR=Data[LoopRead+2];
			KW_DATA_NUM++;
			LoopRead=LoopRead+2;
			
		}
		LoopRead++;
		
	}
	
	
}


int AnalysisWord(){
	Data.resize(DataLen+1);
	//char* Temp1=TempData;
	string CopyData(TempData.begin(),TempData.end());
	
	Data[DataLen]=CopyData;
	//cout<<CopyData<<endl;
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
				//EXPLAINLINE=0;
				AnalysisLoop=AnalysisLoop+2;
				
				for (;;){
					if (ReadBECFile[AnalysisLoop]=='\n' || ReadBECFile.length()==AnalysisLoop){
						AnalysisLoop--;
						//EXPLAINLINE==1;
						break;
					}else {
						AnalysisLoop++;
					}
				}
			}else{
				CmpString();
			}
		}else if (ReadBECFile[AnalysisLoop]=='\n'){
			AnalysisWord();
		}
		AnalysisLoop++;
	}
    if (ReadBECFile.length()==AnalysisLoop){
		AnalysisWord();
	}
	GenerateLogic();
}


//****

//Node Part

int EnableGBLockFrameNode(int EnableOrN,int LockFrameRate){
	LockFrameEnableORN=EnableOrN;
	LockFrameRate_GB=LockFrameRate;
	return 0;
}



int MoveToTopLayerNode(string OBJ_NAME){
	
	int TempLayerNum=OBJ_INF[OBJ_NAME].DisplayLayerNum;
	OBJ_INF[OBJ_NAME].DisplayLayerNum=DisplayID_Num;
	
	DisplayID.erase(DisplayID.begin()+TempLayerNum-1);
	
	DisplayID.insert(DisplayID.end(),OBJ_NAME);
	
	//pos = mapTest.find(keyValue);
	/*OBJ_INF_POS=OBJ_INF.find(OBJ_NAME);
	if (OBJ_INF_POS!=OBJ_INF.end()){
		struct ObjectInformation Temp_OBJ_INF=OBJ_INF[OBJ_NAME];
		Temp_OBJ_INF.DisplayLayerNum=0;
		OBJ_INF.erase(OBJ_INF_POS);
		OBJ_INF.insert(OBJ_INF.begin(),Temp_OBJ_INF);
	}else{
		//error
	}
	
	//map<string,struct ObjectInformation>::iterator DisplayLayerPos;
	//DisplayLayerPos=OBJ_INF.begin()+(map<string,struct ObjectInformation>::iterator)OBJ_INF[OBJ_NAME].DisplayLayerNum;
	*/
	return 0;
}

int MoveToBottomLayerNode(string OBJ_NAME){
	int TempLayerNum=OBJ_INF[OBJ_NAME].DisplayLayerNum;
	OBJ_INF[OBJ_NAME].DisplayLayerNum=0;
	DisplayID.erase(DisplayID.begin()+TempLayerNum-1);
	
	DisplayID.insert(DisplayID.begin(),OBJ_NAME);
	
	return 0;
}

int UpLayerNode(string OBJ_NAME){
	int TempLayerNum=OBJ_INF[OBJ_NAME].DisplayLayerNum;
	OBJ_INF[OBJ_NAME].DisplayLayerNum++;
	DisplayID.erase(DisplayID.begin()+TempLayerNum-1);
	
	DisplayID.insert(DisplayID.begin()+TempLayerNum-1+1,OBJ_NAME);
	/*OBJ_INF_POS=OBJ_INF.find(OBJ_NAME);
	if (OBJ_INF_POS!=OBJ_INF.end()){
		struct ObjectInformation Temp_OBJ_INF=OBJ_INF[OBJ_NAME];
		Temp_OBJ_INF.DisplayLayerNum=0;
		OBJ_INF.erase(OBJ_INF_POS);
		OBJ_INF.insert(OBJ_INF_POS--,Temp_OBJ_INF);
	}else{
		//error
	}*/
	return 0;
}

int DownLayerNode(string OBJ_NAME){
	int TempLayerNum=OBJ_INF[OBJ_NAME].DisplayLayerNum;
	OBJ_INF[OBJ_NAME].DisplayLayerNum--;
	DisplayID.erase(DisplayID.begin()+TempLayerNum-1);
	
	DisplayID.insert(DisplayID.begin()+TempLayerNum-1-1,OBJ_NAME);
	
	/*OBJ_INF_POS=OBJ_INF.find(OBJ_NAME);
	if (OBJ_INF_POS!=OBJ_INF.end()){
		struct ObjectInformation Temp_OBJ_INF=OBJ_INF[OBJ_NAME];
		Temp_OBJ_INF.DisplayLayerNum=0;
		OBJ_INF.erase(OBJ_INF_POS);
		OBJ_INF.insert(OBJ_INF_POS++,Temp_OBJ_INF);
	}else{
		//error
	}*/
	return 0;
}



int ChangePlaneNode(string OBJ_NAME,int CP_Num){
	
	return 0;
}


int IF_Node(string IF_L_Value,string IF_judge,string IF_R_Value){
	
	return 0;
}


int DebugMessageNode(int DM_PosX,int DM_PosY,string DM_Msg){
	
	return 0;
}

int TranslateObjectLocalNode(string OBJ_NAME,double TON_TSL_X,double TON_TSL_Y){
	OBJ_INF[OBJ_NAME].INF_OBJ_X=OBJ_INF[OBJ_NAME].INF_OBJ_X+TON_TSL_X;
	OBJ_INF[OBJ_NAME].INF_OBJ_Y=OBJ_INF[OBJ_NAME].INF_OBJ_Y+TON_TSL_Y;
	
	SDL_Rect TSL_OBJ_RECT;
	TSL_OBJ_RECT.x=OBJ_INF[OBJ_NAME].INF_OBJ_X;
	TSL_OBJ_RECT.y=OBJ_INF[OBJ_NAME].INF_OBJ_Y;
	TSL_OBJ_RECT.w=OBJ_INF[OBJ_NAME].INF_OBJ_W;
	TSL_OBJ_RECT.h=OBJ_INF[OBJ_NAME].INF_OBJ_H;
	
	//SDL_RenderCopy(Rend,Tex_Data[OBJ_NAME],NULL,&TSL_OBJ_RECT);
	
	return 0;
}

int TranslateObjectGlobalNode(string OBJ_NAME,double TON_TSL_X,double TON_TSL_Y){
	
	return 0;
}

int RotationObjectNode(string OBJ_NAME,double RO_SPEED){
	OBJ_INF[OBJ_NAME].INF_OBJ_ANGLE=OBJ_INF[OBJ_NAME].INF_OBJ_ANGLE+RO_SPEED;
	
	SDL_Rect ROT_OBJ_RECT;
	ROT_OBJ_RECT.x=OBJ_INF[OBJ_NAME].INF_OBJ_X;
	ROT_OBJ_RECT.y=OBJ_INF[OBJ_NAME].INF_OBJ_Y;
	ROT_OBJ_RECT.w=OBJ_INF[OBJ_NAME].INF_OBJ_W;
	ROT_OBJ_RECT.h=OBJ_INF[OBJ_NAME].INF_OBJ_H;
	
	SDL_RenderCopyEx(Rend,Tex_Data[OBJ_NAME],NULL,&ROT_OBJ_RECT,OBJ_INF[OBJ_NAME].INF_OBJ_ANGLE,NULL,SDL_FLIP_NONE);
	return 0;
}


int RotationObjectToNode(string OBJ_NAME,double ROT_ANGLE){
	
	OBJ_INF[OBJ_NAME].INF_OBJ_ANGLE=ROT_ANGLE;
	
	SDL_Rect ROT_OBJ_RECT;
	ROT_OBJ_RECT.x=OBJ_INF[OBJ_NAME].INF_OBJ_X;
	ROT_OBJ_RECT.y=OBJ_INF[OBJ_NAME].INF_OBJ_Y;
	ROT_OBJ_RECT.w=OBJ_INF[OBJ_NAME].INF_OBJ_W;
	ROT_OBJ_RECT.h=OBJ_INF[OBJ_NAME].INF_OBJ_H;
	
	
	SDL_RenderCopyEx(Rend,Tex_Data[OBJ_NAME],NULL,&ROT_OBJ_RECT,ROT_ANGLE,NULL,SDL_FLIP_NONE);
	
	
	return 0;
}


int ReSizeObjectNode(string OBJ_NAME,int RSON_POS_X,int RSON_POS_Y,int RSON_POS_W,int RSON_POS_H){
	SDL_Rect RSON_RESET;
	RSON_RESET.x=RSON_POS_X;
	RSON_RESET.y=RSON_POS_Y;
	RSON_RESET.w=RSON_POS_W;
	RSON_RESET.h=RSON_POS_H;
	
	OBJ_INF[OBJ_NAME].INF_OBJ_X=RSON_POS_X;
	OBJ_INF[OBJ_NAME].INF_OBJ_Y=RSON_POS_Y;
	OBJ_INF[OBJ_NAME].INF_OBJ_W=RSON_POS_W;
	OBJ_INF[OBJ_NAME].INF_OBJ_H=RSON_POS_H;
	
	SDL_RenderCopy(Rend,Tex_Data[OBJ_NAME],NULL,&RSON_RESET);
	
	
	return 0;
}


int SetObjectPosNode(string OBJ_NAME,int SOPN_X,int SOPN_Y){
	
	return 0;
}


int RandomNode(int RN_F_NUM,int RN_L_NUM){
	int RN_RandomResult=PP_RandomRange(RN_F_NUM,RN_L_NUM);
	
	return RN_RandomResult;
}

int ObjectNode(string OBJ_NAME,int ON_ENABLE){
	return 0;
}

int DeleteObjectNode(string OBJ_NAME){
	
	return 0;
}


int ExitGameNode(){
	
	/*while (TexTotal!=0){
		SDL_DestroyTexture(Tex_Data[TexTotal]);
		TexTotal=TexTotal-1;
	}*/
	
	SDL_DestroyRenderer(Rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return 0;
}


//*****

int UpDataIntoXML(){
	return 0;
}




/*int Display(){
	
	
	SDL_Rect rect1;
	rect1.x=0;
	rect1.y=0;
	rect1.w=150;
	rect1.h=50;
	//RotationObjectToNode(BE_MAIN_CAMERA,90);
	
	
	
	while (1){
		
		rect1.y=rect1.y+5;
		
		SDL_RenderClear(Rend);
		
		SDL_RenderCopy(Rend,Tex[1],NULL,NULL);
		SDL_RenderCopy(Rend,Tex[3],NULL,&rect1);
		if (SELECT_TYPE==1){
			SDL_RenderCopy(Rend,Tex[0],NULL,&RECT_TSL);
		}
		SDL_RenderPresent(Rend);
		
		}
		return 0;
}*/


int GameMode(){
	
	while(1){
		
	}
}




//map 
int CreateTexture(int Res_Type,string Tex_Name,string TexPOStr){
	if (Res_Type==TEX_PIC){
		SDL_FreeSurface(Sur);
		Sur=IMG_Load(TexPOStr.c_str());
		//RO_Data_Num++;
		//Tex_Name="Texture"+to_string(Tex_Data_Num);
		Tex_Data[Tex_Name]=SDL_CreateTextureFromSurface(Rend,Sur);
		//SDL_FreeSurface(Sur);
		
	}else if (Res_Type==TEX_DM){
		
		SDL_FreeSurface(Sur);
					fonts=TTF_OpenFont("/sdcard/Programming/BROKEN ENGINE/Fonts.ttf",20);
			SDL_Color DM_CLO;
			DM_CLO.r=255;
			DM_CLO.g=255;
			DM_CLO.b=255;
			DM_CLO.a=0;
			SDL_FreeSurface(Sur);
			Sur=TTF_RenderUTF8_Blended(fonts,TexPOStr.c_str(),DM_CLO);
			
	Tex_Data[Tex_Name]=SDL_CreateTextureFromSurface(Rend,Sur);
	//SDL_FreeSurface(Sur);
	}
	
	
	/*RO_Data_Num++;
	RendererOrder.resize(RO_Data_Num);
	RendererOrder[RO_Data_Num-1]=Tex_Name;
	*/
	return 0;
}


//vector
/*int NewTex(int Res_Type,string TexPOStr){
	TexTotal=TexTotal+1;
	
	//TexTotal++;
    Tex.resize(TexTotal);
	
	if (Res_Type==TEX_PIC){
		SDL_FreeSurface(Sur);
		Sur=IMG_Load(TexPOStr.c_str());
		Tex[TexTotal-1]=SDL_CreateTextureFromSurface(Rend,Sur);
	//Tex[TexTotal-1]=IMG_LoadTexture(Rend,TexPOStr.c_str());
	
	}else if (Res_Type==TEX_DM){
			fonts=TTF_OpenFont("/sdcard/Programming/BROKEN ENGINE/Fonts.ttf",20);
			SDL_Color DM_CLO;
			DM_CLO.r=255;
			DM_CLO.g=255;
			DM_CLO.b=255;
			DM_CLO.a=0;
			SDL_FreeSurface(Sur);
			Sur=TTF_RenderUTF8_Blended(fonts,TexPOStr.c_str(),DM_CLO);
			Tex[TexTotal-1]=NULL;
	Tex[TexTotal-1]=SDL_CreateTextureFromSurface(Rend,Sur);
	SDL_FreeSurface(Sur);
	}else if (Res_Type==TEX_BSCLO){
		SDL_FreeSurface(Sur);
		
		SDL_Surface*TempR1=SDL_CreateRGBSurface(0,SCREEN_W,SCREEN_H,32,0,0,0,0);
		
		SDL_FillRect(TempR1,NULL,0xffacbd);
		
		Tex[TexTotal-1]=SDL_CreateTextureFromSurface(Rend,TempR1);
		SDL_FreeSurface(TempR1);
	}
	
	return 0;
}*/






int CreateObject(string Tex_Name){
	OBJ_INF[Tex_Name];
	OBJ_INF[Tex_Name].INF_OBJ_X=100;
	OBJ_INF[Tex_Name].INF_OBJ_Y=100;
	OBJ_INF[Tex_Name].INF_OBJ_W=100;
	OBJ_INF[Tex_Name].INF_OBJ_H=100;
	OBJ_INF[Tex_Name].INF_OBJ_ANGLE=0;
	OBJ_INF[Tex_Name].TextureName=Tex_Name;
	OBJ_INF[Tex_Name].INF_DisplayORN=0;
	DisplayID_Num++;
	//DisplayID.resize(DisplayID_Num);
	DisplayID.insert(DisplayID.end(),Tex_Name);
	OBJ_INF[Tex_Name].DisplayLayerNum=DisplayID_Num;
	
	return 0;
}



int SetObject(string OBJ_Name,int CO_Pos_X,int CO_Pos_Y,int CO_Size_W,int CO_Size_H,double CO_ROT){
	OBJ_INF[OBJ_Name].INF_OBJ_X=CO_Pos_X;
	OBJ_INF[OBJ_Name].INF_OBJ_Y=CO_Pos_Y;
	OBJ_INF[OBJ_Name].INF_OBJ_W=CO_Size_W;
	OBJ_INF[OBJ_Name].INF_OBJ_H=CO_Size_H;
	OBJ_INF[OBJ_Name].INF_OBJ_ANGLE=CO_ROT;
	return 0;
}





int INITIAL_BASE_DATA(){
	win=SDL_CreateWindow("BE",0,0,480,800,0);
	Rend=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	TTF_Init();
	
	
	SDL_GetWindowSize(win,&SCREEN_W,&SCREEN_H);
	
	PP_RandomSeed();
	
	
	//CONTROL SELECT OBJECTS INIT
	//NewTex(TEX_PIC,"/sdcard/BE_RENDERER_CONTROL/CAMERA.png");
	
	CreateTexture(TEX_PIC,BE_MAIN_CAMERA,"/sdcard/BE_RENDERER_CONTROL/CAMERA.png");
	
	//NewTex(TEX_PIC,"/sdcard/BE_RENDERER_CONTROL/VOICE.png");
	
	CreateTexture(TEX_PIC,BE_MAIN_VOICE,"/sdcard/BE_RENDERER_CONTROL/VOICE.png");
	//NewTex(TEX_PIC,"/sdcard/BE_RENDERER_CONTROL/OBJECT.png");
	
	CreateTexture(TEX_PIC,BE_MAIN_OBJECT,"/sdcard/BE_RENDERER_CONTROL/OBJECT.png");
	
	//NewTex(TEX_PIC,"/sdcard/BE_RENDERER_CONTROL/SELECT.png");
	
	CreateTexture(TEX_PIC,BE_MAIN_SELECT,"/sdcard/BE_RENDERER_CONTROL/SELECT.png");
	
	//NewTex(TEX_PIC,"/sdcard/BE_RENDERER_CONTROL/TRANSLATE.png");
	
	CreateTexture(TEX_PIC,BE_MAIN_TRANSLATE,"/sdcard/BE_RENDERER_CONTROL/TRANSLATE.png");
	
	//NewTex(TEX_PIC,"/sdcard/BE_RENDERER_CONTROL/ROTATION.png");
	
	CreateTexture(TEX_PIC,BE_MAIN_ROTATION,"/sdcard/BE_RENDERER_CONTROL/ROTATION.png");
	
	//NewTex(TEX_PIC,"/sdcard/BE_RENDERER_CONTROL/ZOOM.png");
	
	
	CreateTexture(TEX_PIC,BE_MAIN_ZOOM,"/sdcard/BE_RENDERER_CONTROL/ZOOM.png");
	
	return 0;
}



//Input Thread :check the Input Data
int InputThread(void *ptr){
	int fz=0;
	int NewLooper=0;
	while (1){
		
		
		while (SDL_PollEvent(&InputEvent)){
			if (InputEvent.type==SDL_FINGERDOWN || InputEvent.type==SDL_FINGERMOTION){
				TouchX=InputEvent.tfinger.x*SCREEN_W;
				TouchY=InputEvent.tfinger.y*SCREEN_H;
				
				Select_Opera_Type.SELECT_TYPE=1;
			}
		}
		
		
		if (EDITOR_MODE==0){
			
				if (NewLooper==100){
				if (fz==0){
					MoveToBottomLayerNode("TS1");
					NewLooper=0;
					fz=1;
					}else{
						MoveToTopLayerNode("TS1");
						NewLooper=0;
						fz=0;
					}
					
				}else{
			NewLooper++;
		}
		}else if (EDITOR_MODE==1){
			
			
		}
		
		if (Select_Opera_Type.SELECT_TYPE==1){
			RECT_TSL.x=TouchX;
	        RECT_TSL.y=TouchY-200;
	        RECT_TSL.w=200;
	        RECT_TSL.h=200;
		}
	}
}



//Test
int GameLooper(){
	//int NewLooper=0;
	
	//vector<string>::iterator ITER;
	while (1){
	//	if (LockFrameORN==1){
		int LF_TimeStart=SDL_GetTicks();
			SDL_RenderClear(Rend);
			//SDL_RenderCopy(Rend,Tex_Data[
			
		
			
			
		int Looper=0;
		for (int Looper=0;Looper!=DisplayID_Num;){
			
			SDL_RenderCopy(Rend,Tex_Data[DisplayID[Looper]],NULL,NULL);
			
			Looper++;
		}
		/*SDL_RenderCopy(Rend,Tex_Data[DisplayID[0]],NULL,NULL);
		SDL_RenderCopy(Rend,Tex_Data[DisplayID[1]],NULL,NULL);*/
		SDL_RenderPresent(Rend);
		
		if (LockFrameEnableORN==1){
			int LF_TimeEnd=SDL_GetTicks();
			if ((LF_TimeEnd-LF_TimeStart)<(1000/LockFrameRate_GB)){
				SDL_Delay((1000/LockFrameRate_GB)-(LF_TimeEnd-LF_TimeStart));
				
			}
		}
		
	
	}
	return 0;
}


int AnalysisTestDisplay(){
	int RenderNUM=0;
	int NewLooper=0;
	while (RenderNUM!=1000000){
		TranslateObjectLocalNode("HL1",0,5);
		SDL_RenderClear(Rend);
		SDL_RenderCopy(Rend,Tex_Data["TS1"],NULL,NULL);
		if (NewLooper==100){
			MoveToBottomLayerNode("HL2");
		}else{
			NewLooper++;
		}
		for (int LoopID=0;LoopID!=DisplayID_Num;){
			
			SDL_Rect TempRect;
			TempRect.x=OBJ_INF[DisplayID[LoopID]].INF_OBJ_X;
			TempRect.y=OBJ_INF[DisplayID[LoopID]].INF_OBJ_Y;
		
		TempRect.w=OBJ_INF[DisplayID[LoopID]].INF_OBJ_W;
		
		TempRect.h=OBJ_INF[DisplayID[LoopID]].INF_OBJ_H;
		
		
				//SDL_RenderCopyEx(Rend,Tex_Data[DisplayID[LoopID]],NULL,&TempRect,OBJ_INF[DisplayID[LoopID]].INF_OBJ_ANGLE,NULL,SDL_FLIP_NONE);
				SDL_RenderCopy(Rend,Tex_Data[DisplayID[LoopID]],NULL,&TempRect);
				
				LoopID++;
				
			//++;
		}
		
		SDL_RenderPresent(Rend);
		RenderNUM++;
	}
	return 0;
}



int main(int argc,char *argv[]){
	INITIAL_BASE_DATA();
	
	ReadBECFile=PP_ReadFile("NewScript2.bec");
	Analysis();
	//NewTex(TEX_PIC,"/sdcard/HL1.bmp");
	//NewTex(TEX_DM,"hackerIOS");
	CreateTexture(TEX_PIC,"TS1","/sdcard/HL1.bmp");
	
	CreateTexture(TEX_PIC,"HL1","/sdcard/HL2.jpg");
	AnalyseXMLSet("XML_Analysis1.xml");
	
	
	CreateObject("HL1");
	OBJ_INF["HL1"];
	SetObject("HL1",0,0,1000,1000,20);
	CreateObject("TS1");
	OBJ_INF["TS1"];
	SetObject("TS1",50,500,200,200,0);
	
	ReSizeObjectNode("HL1",0,0,900,1000);
	
	SDL_Thread *IPThread;
	IPThread=SDL_CreateThread(InputThread,"InputThread",(void*)NULL);
	GameLooper();
	//AnalysisTestDisplay();
	//Display();
	//SDL_Delay(1000);
	ExitGameNode();
	return 0;
}
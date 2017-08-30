//BROKEN ENGINE Main Render
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

#include "IRapidXml/rapidxml.hpp"
#include "IRapidXml/rapidxml_print.hpp"
#include "IRapidXml/rapidxml_utils.hpp"

int TEX_PIC=0;

int TEX_DM=1;
int TEX_FONT=2;
SDL_Window*win=NULL;
SDL_Renderer*Rend=NULL;
SDL_Surface*Sur=NULL;
TTF_Font*fonts=NULL;
//int Running=1;


int TexTotal=-1;

struct LoadVoice{
	//SDL_
	Mix_Chunk*VoiceData=NULL;
	int VoicePosX;
	int VoicePosY;
};


struct LoadTextureToRender{
	SDL_Texture*LTex=NULL;
	int TexPosX;
	int TexPosY;
	int TexPosW;
	int TexPosH;
	float TexRot;
};
struct LoadTextureToRender*LTexToRender;




int DebugMessage(int DM_PosX,int DM_PosY,int DM_Time,string DM_Msg){
	
	return 0;
}



int ExitGameNode(){
	
	while (TexTotal!=0){
		SDL_DestroyTexture(LTexToRender[TexTotal].LTex);
		TexTotal=TexTotal-1;
	}
	delete LTexToRender;
	SDL_DestroyRenderer(Rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return 0;
}



int UpDataIntoXML(){
	
}


int InitTex(){
	LTexToRender=new LoadTextureToRender[0];
	
}

int Display(){
	while (1){
		//if (TexTotal==0){
			
		//}
				SDL_RenderCopy(Rend,LTexToRender[0].LTex,NULL,NULL);
	    SDL_RenderPresent(Rend);
	    SDL_RenderClear(Rend);
	    
	    
	}
	return 0;
}




int NewTex(int Res_Type,string TexPOStr){
	//TexTotal=TexTotal+1;
	if (TexTotal>-1){
	//LTexToRender[TexTotal].LTex=NULL;
	struct LoadTextureToRender*CopyLTex=new struct LoadTextureToRender[TexTotal+1];
	
	CopyLTex=LTexToRender;
	delete LTexToRender;
	
	//LTexToRender=new struct LoadTextureToRender[TexTotal+1];
	
	LTexToRender=CopyLTex;
	
	delete CopyLTex;
	
	}else if (TexTotal==-1){
		InitTex();
	}
	TexTotal++;
	
	if (Res_Type==TEX_PIC){
		//SDL_FreeSurface(Sur);
	LTexToRender[TexTotal].LTex=IMG_LoadTexture(Rend,TexPOStr.c_str());
		//Sur=IMG_Load(TexPOStr.c_str());
			//LTexToRender[TexTotal].LTex=SDL_CreateTextureFromSurface(Rend,Sur);
	}else if (Res_Type==TEX_DM){
			fonts=TTF_OpenFont("/sdcard/Programming/BROKEN ENGINE/Fonts.ttf",20);
			SDL_Color DM_CLO;
			DM_CLO.r=255;
			DM_CLO.g=255;
			DM_CLO.b=255;
			DM_CLO.a=0;
			Sur=TTF_RenderUTF8_Blended(fonts,"/sdcard/Programming/BROKEN ENGINE/Fonts.ttf",DM_CLO);
			LTexToRender[TexTotal].LTex=NULL;
	LTexToRender[TexTotal].LTex=SDL_CreateTextureFromSurface(Rend,Sur);
	SDL_FreeSurface(Sur);
		
	}
	//LTexToRender[TexTotal].LTex=SDL_CreateTextureFromSurface(
	
	
	return 0;
}



int main(int argc,char* argv[]){
	win=SDL_CreateWindow("BE",0,0,480,800,0);
	Rend=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	//InitTex();
	TTF_Init();

	
	NewTex(TEX_PIC,"/sdcard/HL2.jpg");
	//NewTex(TEX_PIC,"/sdcard/HL1.bmp");
	//NewTex(TEX_DM,"hackerIOS");
	
	SDL_RenderClear(Rend);
	//SDL_RenderCopy(Rend,LTexToRender[0].LTex,NULL,NULL);
	Display();
	
	//SDL_Delay(10000);
	return 0;
}
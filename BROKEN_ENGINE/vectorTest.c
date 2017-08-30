#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;
SDL_Window*win=NULL;
SDL_Renderer*Rend=NULL;
SDL_Surface*Sur=NULL;
vector<SDL_Texture*>T;
int a=0,b=0;
int Display(){
        while (1){
        	SDL_RenderClear(Rend);
	
	
	
	if (a==60){
		b=1;
	}else if (a==0){
		b=0;
	}
		if (b==0){
			SDL_RenderCopy(Rend,T[0],NULL,NULL);
		a++;
		
		}else if (b==1){
			SDL_RenderCopy(Rend,T[1],NULL,NULL);
			a--;
		}
	
	SDL_RenderPresent(Rend);
        }
	    //SDL_RenderClear(Rend);
	return 0;
}

int main(int argc,char*argv[]){

	win=SDL_CreateWindow("BE",0,0,480,800,0);
	Rend=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	//b=new struct a[AllNum];
	//SDL_RenderClear(Rend);
	Sur=IMG_Load("/sdcard/HL.jpg");
	T.resize(1);
	T[0]=SDL_CreateTextureFromSurface(Rend,Sur);
	//T[0]=IMG_LoadTexture(Rend,"/sdcard/HL.jpg");
	T.resize(2);
	SDL_FreeSurface(Sur);
	Sur=IMG_Load("/sdcard/HL1.bmp");
	//T.insert(T.end(),);
	T[1]=SDL_CreateTextureFromSurface(Rend,Sur);
	Display();
	
	SDL_Delay(10000);
	return 0;
	
}
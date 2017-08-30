//struct test
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;
SDL_Window*win=NULL;
SDL_Renderer*Rend=NULL;
SDL_Surface*Sur=NULL;

struct a{
	int a1;
	//SDL_Texture*T=NULL;
	char *a3;
};
struct a*b;

SDL_Texture*T[]=NULL;
int AllNum=0;

int newstruct(){
	struct a*cp=new struct a[AllNum+1];
	
	SDL_Texture*cpt[]=new SDL_Texture*[AllNum+1];
	cpt=T;
	delete T;
	T=cpt;
	
	cp=b;
	delete b;
	//b=new struct a[AllNum+1];
	b=cp;
	delete cp;
}

int Display(){
	while (1){
        SDL_RenderCopy(Rend,T,NULL,NULL);
	    SDL_RenderPresent(Rend);
	    SDL_RenderClear(Rend);
	}
	return 0;
}

int main(int argc,char* argv[]){
	win=SDL_CreateWindow("BE",0,0,480,800,0);
	Rend=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	b=new struct a[AllNum];
	T[0]=IMG_LoadTexture(Rend,"/sdcard/HL.jpg");
	newstruct();
	T[1]=IMG_LoadTexture(Rend,"/sdcard/HL2.jpg");
	SDL_RenderClear(Rend);
	
	Display();
	return 0;
}
//ROTATION Test

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
SDL_Window*win=NULL;
SDL_Renderer*Rend=NULL;
SDL_Surface*Sur=NULL;
SDL_Texture*Tex=NULL;

int main(int argc,char*argv){
	win=SDL_CreateWindow("BE",0,0,480,800,0);
	Rend=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	SDL_FreeSurface(Sur);
	Sur=IMG_Load("/sdcard/HL1.bmp");
		//Tex_Data_Num++;
		//Tex_Name="Texture"+to_string(Tex_Data_Num);
		Tex=SDL_CreateTextureFromSurface(Rend,Sur);
	double angle=0;
	while (angle!=360){
		angle++;
		//SDL_RenderClear(Rend);
		SDL_RenderCopyEx(Rend,Tex,NULL,NULL,angle,NULL,SDL_FLIP_NONE);
	
	SDL_RenderPresent(Rend);
	}
	SDL_Quit();
	//SDL_Delay(1000);
	return 0;
}
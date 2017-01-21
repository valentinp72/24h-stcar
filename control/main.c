#include "../tools/tools.h"
#include "../tools/easySdl2.h"

#define HEIGHT 800
#define WIDTH  400

#define SCREEN_NAME "37411.ttys000.MBP-Valentin-2"


void execCommand(char * cmd){
	char exec[1000];
	sprintf(exec, "screen -S %s -p 0 -X stuff \"%s`echo -ne '\015'`\"", SCREEN_NAME, cmd);
	system(exec);
}

int main(){

	SDL_Event event;
    int quit = FALSE;

	initSdl(HEIGHT, WIDTH, "Télécommande");

	while(quit == FALSE){
      if(SDL_WaitEvent(&event) != 0){

   	 switch(event.type){
   	   case SDL_KEYDOWN:
   		 switch(event.key.keysym.sym){
   		   case SDLK_q:     quit = TRUE;        break;
   		 }
   		 break;

   	   case SDL_QUIT: quit = TRUE; break;
   	   default: break;

   	 }

      }
    }

	quitSdl();
}

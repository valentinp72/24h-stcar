#include "../tools/tools.h"
#include "../tools/easySdl2.h"
#include "commands.h"
#include "display.h"



int main(){

	SDL_Event event;

    int quit = FALSE;
	int i, found = FALSE, data = 0;
	int isLampOn = FALSE, isTaillampOn = FALSE, isWindscreenOn = FALSE;

	initSdl(HEIGHT, WIDTH, "Télécommande");

	SDL_Color counterColor = {0, 0, 0};
	TTF_Font * roboto = loadFont("media/Roboto-Light.ttf");
	//displayText("Compte-tour :", roboto, counterColor, 500, 20, 1);

	t_texture speedTextures[N_SPEED_TEXTURES];
	t_texture dirTextures[N_DIR_TEXTURES];

	t_texture selectionSpeed = {TOP_SHIFT + 3 * IMG_H, LEFT_SHIFT - 20, loadTexture("media/selection_left.png")};
	t_texture selectionClearSpeed = {TOP_SHIFT, LEFT_SHIFT - 20, loadTexture("media/selection_left_clear.png")};
	t_texture selectionDir = {HEIGHT - (3 * IMG_H) - 20, LEFT_SHIFT + 3*IMG_W, loadTexture("media/selection_dir.png")};
	t_texture selectionClearDir = {HEIGHT - (3 * IMG_H) - 20, LEFT_SHIFT + 3*IMG_W, loadTexture("media/selection_dir_clear.png")};


	t_texture lampOn = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 2 * IMG_W, loadTexture("media/lamp_on.jpg")};
	t_texture lampOff = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 2 * IMG_W, loadTexture("media/lamp_off.jpg")};

	t_texture taillampOn = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 3 * IMG_W, loadTexture("media/taillamp_on.jpg")};
	t_texture taillampOff = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 3 * IMG_W, loadTexture("media/taillamp_off.jpg")};

	t_texture windscreenOn = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 4 * IMG_W, loadTexture("media/windscreen_on.jpg")};
	t_texture windscreenOff = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 4 * IMG_W, loadTexture("media/windscreen_off.jpg")};


	loadSpeedTextures(speedTextures);
	loadDirTextures(dirTextures);

	draw(selectionSpeed, IMG_W + 40, IMG_H);
	draw(selectionDir, IMG_W, IMG_H + 40);

	draw(lampOff, IMG_W, IMG_H);
	draw(taillampOff, IMG_W, IMG_H);
	draw(windscreenOff, IMG_W, IMG_H);
	drawAllTextures(speedTextures, N_SPEED_TEXTURES);
	drawAllTextures(dirTextures, N_DIR_TEXTURES);


	render();

	int lastTime = 0, currentTime;

	while(quit == FALSE){
      	if(SDL_PollEvent(&event) != 0){
			switch(event.type){
		   		case SDL_KEYDOWN:
		   			switch(event.key.keysym.sym){
						case SDLK_q: quit = TRUE; break;
					}
		   			break;

				//En cas de click gauche
				case SDL_MOUSEBUTTONDOWN:
					//render();
					if(event.button.button == SDL_BUTTON_LEFT){

						int x = event.motion.x;
						int y = event.motion.y;

						// ** VITESSE ** //

						// Si on est sur la colonne de la vitesse
						if(x > LEFT_SHIFT && x < LEFT_SHIFT + IMG_W){

							// Si on est sur une ligne valide
							for(i = 0 ; i < N_SPEED_TEXTURES ; i++){
								if(y > TOP_SHIFT + (i) * (IMG_H) && y < TOP_SHIFT + (i + 1) * (IMG_H)){

									selectionClearSpeed.line = selectionSpeed.line;
									selectionSpeed.line = TOP_SHIFT + i * IMG_H;

									draw(selectionClearSpeed, IMG_W + 40, IMG_H);
									draw(selectionSpeed, IMG_W + 40, IMG_H);
									render();

									changeSpeed((N_SPEED_TEXTURES - 1) - (i+1));
								}
							}
						}

						// ** VOLANT ** //
						if(y > dirTextures[0].line && y < dirTextures[N_DIR_TEXTURES - 1].line + IMG_H){
							for(i = 0 ; i < N_DIR_TEXTURES ; i++){
								if(x > dirTextures[i].col && x < dirTextures[i].col + IMG_W){
									selectionClearDir.col = selectionDir.col;
									selectionDir.col = dirTextures[i].col;

									draw(selectionClearDir, IMG_W, IMG_H + 40);
									draw(selectionDir, IMG_W, IMG_H + 40);
									render();

									turn((i == 0) ? 1 : (i == 1) ? 0 : 2);
								}
							}
						}

						// ** Phare ** //
						if(clickedOnTexture(lampOn, x, y)){
							// On a appuyé sur le phare
							if(isLampOn){
								draw(lampOff, IMG_W, IMG_H);
								execCommand("feuAv 0");
							} else {
								draw(lampOn, IMG_W, IMG_H);
								execCommand("feuAv 1");
							}
							isLampOn = !isLampOn;
							render();
						}

						// ** Feu arrière ** //
						if(clickedOnTexture(taillampOn, x, y)){
							if(isTaillampOn){
								draw(taillampOff, IMG_W, IMG_H);
								execCommand("feuArr 0");
							} else {
								draw(taillampOn, IMG_W, IMG_H);
								execCommand("feuArr 1");
							}
							isTaillampOn = !isTaillampOn;
							render();
						}

						// ** Essui glace ** //
						if(clickedOnTexture(windscreenOn, x, y)){
							// On a appuyé sur l'essui glace
							if(isWindscreenOn){
								draw(windscreenOff, IMG_W, IMG_H);
								execCommand("suieGlace 0");
							} else {
								draw(windscreenOn, IMG_W, IMG_H);
								execCommand("suieGlace 1");
							}
							isWindscreenOn = !isWindscreenOn;
							render();
						}

					}
					break;
				case SDL_QUIT: quit = TRUE; break;
				default: break;
		   	 }
	 	}

		/*currentTime = SDL_GetTicks();
		if(currentTime > lastTime + 30) {
        	//printf("ffsdf\n");
			initRandom();
			if(didItHappen(50)){
				data = readData();
				char counter[100];
				sprintf(counter, "Compte-tour : %i  ", data * 1000);
				displayText(counter, roboto, counterColor, 500, 20, 1);
			}
			render();

        	lastTime = currentTime;

    	} else {
			SDL_Delay(30 - (currentTime - lastTime));
		}*/
	}


	unloadAllTextures(speedTextures, N_SPEED_TEXTURES);
	unloadAllTextures(dirTextures, N_DIR_TEXTURES);

	SDL_DestroyTexture(lampOn.texture);
	SDL_DestroyTexture(lampOff.texture);
	SDL_DestroyTexture(taillampOn.texture);
	SDL_DestroyTexture(taillampOff.texture);
	SDL_DestroyTexture(windscreenOn.texture);
	SDL_DestroyTexture(windscreenOff.texture);
	SDL_DestroyTexture(selectionSpeed.texture);
	SDL_DestroyTexture(selectionDir.texture);
	SDL_DestroyTexture(selectionClearSpeed.texture);
	SDL_DestroyTexture(selectionClearDir.texture);

	TTF_CloseFont(roboto);

	quitSdl();
}

#include "../tools/tools.h"
#include "../tools/easySdl2.h"

#define HEIGHT 350
#define WIDTH  800

#define LEFT_SHIFT 50
#define TOP_SHIFT  50

#define IMG_W 70
#define IMG_H 50

#define N_SPEED_TEXTURES 5
#define N_DIR_TEXTURES 3

#define SCREEN_NAME "37411.ttys000.MBP-Valentin-2"

typedef struct {
	int line, col;
	SDL_Texture * texture;
} t_texture;

void execCommand(char * cmd){
	char exec[1000];
	sprintf(exec, "screen -S %s -L -p 0 -X stuff \"%s`echo -ne '\015'`\"", SCREEN_NAME, cmd);
	system(exec);
}

void loadSpeedTextures(t_texture speedTextures[]){
	speedTextures[0].texture  = loadTexture("media/speed_3.jpg");
	speedTextures[1].texture  = loadTexture("media/speed_2.jpg");
	speedTextures[2].texture  = loadTexture("media/speed_1.jpg");
	speedTextures[3].texture  = loadTexture("media/speed_0.jpg");
	speedTextures[4].texture  = loadTexture("media/speed_-1.jpg");

	int i;
	for(i = 0 ; i < N_SPEED_TEXTURES ; i++){
		speedTextures[i].line = TOP_SHIFT + IMG_H * i;
		speedTextures[i].col  = LEFT_SHIFT;
	}
}

void loadDirTextures(t_texture dirTextures[]){
	dirTextures[0].texture  = loadTexture("media/dir_left.jpg");
	dirTextures[1].texture  = loadTexture("media/dir_middle.jpg");
	dirTextures[2].texture  = loadTexture("media/dir_right.jpg");

	int i;
	for(i = 0 ; i < N_DIR_TEXTURES ; i++){
		dirTextures[i].line = HEIGHT - (3 * IMG_H);
		dirTextures[i].col  = LEFT_SHIFT + (i + 2)* IMG_W;
	}
}



void unloadAllTextures(t_texture textures[], int size){
	int i;
	for(i = 0 ; i < size ; i++) SDL_DestroyTexture(textures[i].texture);
}

void draw(t_texture texture, int w, int h){
	drawTexture(texture.texture, texture.line, texture.col, w, h);
}

void drawAllTextures(t_texture textures[], int size){
	int i;
	for(i = 0 ; i < size ; i++) drawTexture(textures[i].texture , textures[i].line, textures[i].col, IMG_W, IMG_H);
}

void changeSpeed(int speed){
	if(speed >= -1 && speed <= 3){
		char cmd[100];
		sprintf(cmd, "rouler %i", speed);
		execCommand(cmd);
	}
}

void turn(int dir){
	if(dir >= 0 && dir <= 2){
		char cmd[100];
		sprintf(cmd, "turn %i", dir);
		execCommand(cmd);
	}
}

int main(){

	SDL_Event event;

    int quit = FALSE;
	int i, found = FALSE;

	initSdl(HEIGHT, WIDTH, "Télécommande");

	t_texture speedTextures[N_SPEED_TEXTURES];
	t_texture dirTextures[N_DIR_TEXTURES];

	t_texture selectionSpeed = {TOP_SHIFT + 3 * IMG_H, LEFT_SHIFT - 20, loadTexture("media/selection_left.png")};
	t_texture selectionClearSpeed = {TOP_SHIFT, LEFT_SHIFT - 20, loadTexture("media/selection_left_clear.png")};
	t_texture selectionDir = {HEIGHT - (3 * IMG_H) - 20, LEFT_SHIFT + 3*IMG_W, loadTexture("media/selection_dir.png")};
	t_texture selectionClearDir = {HEIGHT - (3 * IMG_H) - 20, LEFT_SHIFT + 3*IMG_W, loadTexture("media/selection_dir_clear.png")};


	t_texture lampOn = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 2 * IMG_W, loadTexture("media/lamp_on.jpg")};
	t_texture lampOff = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 2 * IMG_W, loadTexture("media/lamp_off.jpg")};

	t_texture windscreenOn = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 4 * IMG_W, loadTexture("media/windscreen_on.jpg")};
	t_texture windscreenOff = {TOP_SHIFT + IMG_H, LEFT_SHIFT + 4 * IMG_W, loadTexture("media/windscreen_off.jpg")};

	loadSpeedTextures(speedTextures);
	loadDirTextures(dirTextures);

	draw(selectionSpeed, IMG_W + 40, IMG_H);
	draw(selectionDir, IMG_W, IMG_H + 40);

	draw(lampOn, IMG_W, IMG_H);
	draw(windscreenOff, IMG_W, IMG_H);
	drawAllTextures(speedTextures, N_SPEED_TEXTURES);
	drawAllTextures(dirTextures, N_DIR_TEXTURES);

	render();

	while(quit == FALSE){
      	if(SDL_WaitEvent(&event) != 0){
			switch(event.type){
		   		case SDL_KEYDOWN:
		   			switch(event.key.keysym.sym){
						case SDLK_q: quit = TRUE; break;
					}
		   			break;

				//En cas de click gauche
				case SDL_MOUSEBUTTONDOWN:
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


						printf("x : %i ; y : %i\n", x, y);
					}
					break;
				case SDL_QUIT: quit = TRUE; break;
				default: break;
		   	 }
	 	}
	}

	unloadAllTextures(speedTextures, N_SPEED_TEXTURES);
	unloadAllTextures(dirTextures, N_DIR_TEXTURES);

	SDL_DestroyTexture(lampOn.texture);
	SDL_DestroyTexture(lampOff.texture);
	SDL_DestroyTexture(windscreenOn.texture);
	SDL_DestroyTexture(windscreenOff.texture);
	SDL_DestroyTexture(selectionSpeed.texture);
	SDL_DestroyTexture(selectionDir.texture);
	SDL_DestroyTexture(selectionClearSpeed.texture);
	SDL_DestroyTexture(selectionClearDir.texture);


	quitSdl();
}

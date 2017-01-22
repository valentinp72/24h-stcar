#include "../tools/easySdl2.h"
#include "../tools/tools.h"

#include "display.h"

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

int clickedOnTexture(t_texture texture, int x, int y){
	return (y > texture.line && y < texture.line + IMG_H && x > texture.col && x < texture.col + IMG_W);
}

#ifndef DISPLAY
#define DISPLAY

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

	typedef struct {
		int line, col;
		SDL_Texture * texture;
	} t_texture;


	void loadSpeedTextures(t_texture speedTextures[]);
	void loadDirTextures(t_texture dirTextures[]);
	void unloadAllTextures(t_texture textures[], int size);
	void draw(t_texture texture, int w, int h);
	void drawAllTextures(t_texture textures[], int size);
	int clickedOnTexture(t_texture texture, int x, int y);


#endif

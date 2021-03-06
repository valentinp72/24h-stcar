#include "easySdl2.h"

static t_window gMainWindow;


const t_color DEFAULT_COLOR = {236, 240, 241, 255};


// todo: event, drawFunction, texte, texture rotation, draw to texture

void delay (int timeMs) {
	SDL_Delay (timeMs);
}

/*********************************/
/* Initialistion and termination */
/*********************************/

int initSdl(int height, int width, char * wName) {
	Uint32 wflags = 0;
	Uint32 rflags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
	int indexDriver = -1;
	SDL_Surface *icone = NULL;

	if (SDL_Init (SDL_INIT_VIDEO) != 0) {
		fprintf (stderr, " Failure: unable to load the SDL\n %s", SDL_GetError());
		return -1;
	}
	TTF_Init();


	gMainWindow.window = SDL_CreateWindow (wName, SDL_WINDOWPOS_CENTERED/*col*/, SDL_WINDOWPOS_CENTERED/*line*/, width, height, wflags);

	if (gMainWindow.window == NULL) {
		fprintf (stderr, " Failure: unable to create the window (w:%d, h:%d)\n %s", width, height, SDL_GetError());
		return -1;
	}

	gMainWindow.renderer = SDL_CreateRenderer (gMainWindow.window, indexDriver, wflags);

	if (gMainWindow.renderer == NULL) {
		fprintf (stderr, " Failure: unable to create the renderer\n %s", SDL_GetError());
		return -1;
	}

	icone = IMG_Load("icone.png");
	if (icone != NULL) {
		SDL_SetWindowIcon (gMainWindow.window, icone);
		SDL_FreeSurface (icone);
	}
	clear();
	render();
	return 0;
}

void quitSdl () {
	TTF_Quit();
	SDL_DestroyRenderer(gMainWindow.renderer);
	SDL_DestroyWindow(gMainWindow.window);
	SDL_Quit();
}


/***************/
/* drawTexture */
/***************/

void drawTexture (SDL_Texture *texture, int line, int col, int width, int height) {
	SDL_Rect dstRect = {col, line, width, height};
	SDL_RenderCopy (gMainWindow.renderer, texture, /*src rect*/ NULL, &dstRect);
}

void drawPartOfTexture (SDL_Texture *texture, int srcL, int srcC, int srcW, int srcH, int dstL, int dstC, int dstW, int dstH) {
	SDL_Rect dstR = {dstC, dstL, dstW, dstH},
	         srcR = {srcC, srcL, srcW, srcH};
	SDL_RenderCopy (gMainWindow.renderer, texture, &srcR, &dstR);
}


/****************/
/*    Render    */
/****************/

void render () {
	SDL_RenderPresent (gMainWindow.renderer);
}

void wrender (t_window win) {
	SDL_RenderPresent (win.renderer);
}


/****************/
/*     Clear    */
/****************/

void clear () {
	SDL_SetRenderDrawColor(gMainWindow.renderer, DEFAULT_COLOR.r, DEFAULT_COLOR.g, DEFAULT_COLOR.b, DEFAULT_COLOR.a);
	SDL_RenderClear(gMainWindow.renderer); // nettoie
}

void clearColor (t_color color) {
	SDL_SetRenderDrawColor(gMainWindow.renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(gMainWindow.renderer); // nettoie
}

void wclear (t_window win) {
	SDL_SetRenderDrawColor(win.renderer, DEFAULT_COLOR.r, DEFAULT_COLOR.g, DEFAULT_COLOR.b, DEFAULT_COLOR.a);
	SDL_RenderClear(win.renderer); // nettoie
}

void wclearColor (t_window win, t_color color) {
	SDL_SetRenderDrawColor(win.renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(win.renderer); // nettoie
}


/***************/
/* loadTexture */
/***************/

/* return a pointer on a texture, containing the image "name", attached to the main window renderer
   or NULL if "name" is not a valid image */
SDL_Texture * loadTexture (char name[100]) {
	SDL_Texture * texture = NULL;
	texture = IMG_LoadTexture (gMainWindow.renderer, name);
	if (texture == NULL) {
		fprintf (stderr, " Failure: loadTexture (%s)\n Error: %s", name, SDL_GetError());
	}
	return texture;
}

/* return a pointer on a texture, containing the image "name", attached to the window win renderer
   or NULL if "name" is not a valid image */
SDL_Texture * wloadTexture (t_window win, char name[100]) {
	SDL_Texture * texture = NULL;
	texture = IMG_LoadTexture (win.renderer, name);
	if (texture == NULL) {
		printf(" Failure: loadTexture (%s)\n Error: %s", name, SDL_GetError());
	}
	return texture;
}

TTF_Font * loadFont(char * font){
	return TTF_OpenFont(font, 30);
}

void displayText(char * msg, TTF_Font *font, SDL_Color color, int x, int y, float size){

	int texW = 0;
	int texH = 0;

	SDL_Color BG_COLOR = {236, 240, 241};
	SDL_Surface * surface = TTF_RenderText_Shaded(font, msg, color, BG_COLOR);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(gMainWindow.renderer, surface);

	if(surface == NULL) printf("sdfsdffsdsdfsdfs\n");

	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = {x, y, texW*size, texH*size};

	SDL_RenderCopy(gMainWindow.renderer, texture, NULL, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

}

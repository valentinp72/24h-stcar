#ifndef EASY_SDL2_H
#define EASY_SDL2_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} t_window;

void delay (int timeMs);

void quitSdl ();
int initSdl(int height, int width);

void drawTexture (SDL_Texture *texture, int line, int col, int width, int height);
void drawPartOfTexture (SDL_Texture *texture, int srcL, int srcC, int srcW, int srcH, int dstL, int dstC, int dstW, int dstH);

void render ();
void wrender (t_window win);

void clear ();
void clearColor (int red, int green, int blue, int alpha);
void wclear (t_window win);
void wclearColor (t_window win, int red, int green, int blue, int alpha);

SDL_Texture * loadTexture (char name[100]);
SDL_Texture * wloadTexture (t_window win, char name[100]);

#endif /* end of include guard: EASY_SDL2_H */

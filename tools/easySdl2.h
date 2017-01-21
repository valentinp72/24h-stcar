#ifndef EASY_SDL2_H
#define EASY_SDL2_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} t_window;

typedef struct {int r, g, b, a;} t_color;


void delay (int timeMs);

void quitSdl ();
int initSdl(int height, int width, char * wName);

void drawTexture (SDL_Texture *texture, int line, int col, int width, int height);
void drawPartOfTexture (SDL_Texture *texture, int srcL, int srcC, int srcW, int srcH, int dstL, int dstC, int dstW, int dstH);

void render ();
void wrender (t_window win);

void clear ();
void clearColor (t_color color);
void wclear (t_window win);
void wclearColor (t_window win, t_color color);

SDL_Texture * loadTexture (char name[100]);
SDL_Texture * wloadTexture (t_window win, char name[100]);

#endif /* end of include guard: EASY_SDL2_H */

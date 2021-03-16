#ifdef DREAMCAST
#include<kos.h>
#endif

#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SFont.h>

#ifdef DREAMCAST
#include <SDL_dreamcast.h>
#endif

/* cursor and font PNGs image files */
#include "cursor.h"
#include "font.h"

#define WIDTH 640
#define HEIGHT 480

SDL_Surface *screen=NULL,*font_surface,*cursor_surface;
SFont_FontInfo font;
unsigned posx=0, posy=0;


void clearevents(void)
{
	SDL_Event event;
	SDL_Delay(100);
	while(SDL_PollEvent(&event))
		SDL_Delay(20);
}

int getpos(void)
{
	SDL_Event event;
	int ret=0;
	
	while(SDL_PollEvent(&event))
		switch(event.type){
/* If press ESCAPE or mouse button or window close then exit application */
			case SDL_KEYDOWN:
				if (event.key.keysym.sym!=SDLK_ESCAPE)
					break;
			case SDL_QUIT:
			case SDL_MOUSEBUTTONUP:
				ret=-1;
			case SDL_MOUSEMOTION:
				posx=event.motion.x;
				posy=event.motion.y;
				break;
		}
	return ret;
}

int main(int narg,char**arg)
{
	puts("\n-----------------\n| DIRECT DRIVER |\n-----------------");
        SDL_DC_SetVideoDriver(SDL_DC_DIRECT_VIDEO);
	Uint32 flags=SDL_HWSURFACE|SDL_DOUBLEBUF;
	char *msg=calloc(1,1024);
	SDL_Surface *tmp;
	unsigned col;
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);
#ifdef DREAMCAST
	SDL_DC_ShowAskHz(SDL_FALSE);
/* Map all START buttons as ESCAPE key */
	SDL_DC_MapKey(0, SDL_DC_START, SDLK_ESCAPE);
	SDL_DC_MapKey(1, SDL_DC_START, SDLK_ESCAPE);
	SDL_DC_MapKey(2, SDL_DC_START, SDLK_ESCAPE);
	SDL_DC_MapKey(3, SDL_DC_START, SDLK_ESCAPE);
	flags|=SDL_FULLSCREEN;
#endif
	screen=SDL_SetVideoMode(WIDTH,HEIGHT,0,flags);
/* Enable joystick/pad 0 for keyboard and mouse emulation */
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_JoystickOpen(0);
	SDL_ShowCursor(0);
	col=SDL_MapRGB(screen->format,16,16,32);
	tmp=IMG_Load_RW(SDL_RWFromMem((void *)&cursor_png,CURSOR_LEN),0);
	cursor_surface=SDL_DisplayFormat(tmp);
	SDL_FreeSurface(tmp);
	tmp=IMG_Load_RW(SDL_RWFromMem((void*)&font_png, FONT_PNG_SIZE),0);
	font_surface=SDL_DisplayFormat(tmp);
	SDL_FreeSurface(tmp);
	font.Surface=font_surface;
	SFont_InitFontInfo(&font);
	clearevents();
	while(!getpos())
	{
		SDL_Rect r;
		SDL_FillRect(screen,NULL,col);
		r.x=posx; r.y=posy; r.w=cursor_surface->w; r.h=cursor_surface->h;
		SDL_BlitSurface(cursor_surface,NULL,screen,&r);
		sprintf(msg,"(%i,%i)",posx,posy);
		SFont_XCenteredStringInfo(screen,&font,(screen->h+font_surface->h)>>1,msg);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	SDL_FreeSurface(font_surface);
	SDL_Quit();
	free(msg);
	return 0;
}

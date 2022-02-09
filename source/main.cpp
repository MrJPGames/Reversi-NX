#include <switch.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GFX.h"
#include "TextureManager.h"
#include "AudioPlayer.h"
#include "Game/Game.h"
#include "main.h"

HidTouchScreenState state={0};
u32 kDown;
PadState pad;

SDL_Window *    window;
SDL_Renderer *  renderer;

Game game;

TextureManager texManager;
AudioPlayer ap;

void draw(){
    // Set off-white default background colour:
    SDL_SetRenderDrawColor(renderer, 235, 232, 227, 255);
    // Clear screen (with off-white colour set before)
    SDL_RenderClear(renderer);
	game.draw();
	SDL_RenderPresent(renderer);
}

void update(){
	padUpdate(&pad);
	kDown = padGetButtonsDown(&pad);
	hidGetTouchScreenStates(&state, 1);

	game.update();
}


int main(int argc, char **argv)
{
	padConfigureInput(8, HidNpadStyleSet_NpadStandard);
	padInitializeDefault(&pad);

    // Initialize
	hidInitializeTouchScreen();
	romfsInit();
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(MIX_INIT_MP3);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	window = SDL_CreateWindow("Main-Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Set blend mode
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	texManager.init(renderer);

	game.init(renderer, &texManager, &ap, &pad);

	// Game loop:
	while (true)
	{
		update();
		draw();
		if (kDown & HidNpadButton_Plus)
			break;
	}

	//On detruit la fenètre
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	romfsExit();

	return EXIT_SUCCESS;
}

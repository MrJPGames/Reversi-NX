#ifndef CLASS_GAME
#define CLASS_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GFX.h"
#include "TextureManager.h"
#include "AudioPlayer.h"
#include "Game/Board.h"

using namespace std;

class Game{
	public:
		Game();
		void init(SDL_Renderer* r, TextureManager* t, AudioPlayer* mp, PadState* padPtr);
        void startGame(int againstCPU);
		void update();
		void draw();
	private:
        void updateCursor(u32 kDown);

		SDL_Renderer* renderer;
		PadState* pad;
		TextureManager* textureManager;
		AudioPlayer* audioPlayer;
        Board board;
        // Indicates which player's turn it is (only used when not playing against CPU)
        int currentPlayer = 1;
        // Cursor X,Y position on board
        int cX,cY;
        image* cursorTex;
};

#endif

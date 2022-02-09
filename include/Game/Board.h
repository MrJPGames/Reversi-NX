#ifndef REVERSI_NX_BOARD_H
#define REVERSI_NX_BOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GFX.h"
#include "TextureManager.h"
#include "Game/BaseBoard.h"

class Board : public BaseBoard{
    public:
        void init(SDL_Renderer* r, TextureManager* t);
        void updatePossibilitySpace(int col);
        void draw();
    private:
        bool possSpace[8][8];
        SDL_Renderer* renderer;
        TextureManager* textureManager;
        image* boardTex;
        image* blackTileTex;
        image* whiteTileTex;
        image* possTileTex;
};

#endif //REVERSI_NX_BOARD_H
